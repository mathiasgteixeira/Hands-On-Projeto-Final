#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <DHT.h>

#define MODE_MANUAL 0
#define MODE_AUTO   1
#define DHTPIN 15       
#define DHTTYPE DHT11

Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
int ledPin = 25;
int ledChannel = 0;
int ledValue = 10;
int ledMode = MODE_MANUAL;

int ldrPin = 34;
int ldrMax = 4000;

int thresholdValue = 50;

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    for (int i=9; i>=0; i--) {
        digitalWrite(LED_BUILTIN, i % 2 ? HIGH : LOW);
        delay(50);
    }
    if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
    while (1) {}
    }
    ledcSetup(1, 5000, 8);
    ledcAttachPin(LED_BUILTIN, 1); // Led Builtin aceita PWM no ESP32
    
    pinMode(ledPin, OUTPUT);
    ledcSetup(ledChannel, 5000, 8);
    ledcAttachPin(ledPin, ledChannel);
    
    Serial.printf("DBG DevWeather Initialized.\n");
}

 

void loop() {
    String serialCommand;

    while (Serial.available() > 0) {
        char serialChar = Serial.read();
        serialCommand += serialChar; 

        if (serialChar == '\n') {
            processCommand(serialCommand);
            serialCommand = "";
        }
    }

    ledUpdate();
    delay(100);
}


void processCommand(String command) {
    command.trim();
    command.toUpperCase();

    // Serial.println("DBG Received command: " + command);

    if (command.startsWith("SET_LED ")) {
        int ledTmp = command.substring(8).toInt();
        if (ledTmp >= 0 && ledTmp <= 100) {
            ledValue = ledTmp;
            ledMode  = MODE_MANUAL;
            ledUpdate();
            Serial.printf("RES SET_LED 1\n");
        }
        else {
            Serial.printf("RES SET_LED -1\n");
        }
    }
    else if (command.startsWith("SET_THRESHOLD ")) {
        int thresholdTmp = command.substring(14).toInt();
        if (thresholdTmp >= 0 && thresholdTmp <= 100) {
            thresholdValue = thresholdTmp;
            ledMode = MODE_AUTO;
            ledUpdate();
            Serial.printf("RES SET_THRESHOLD 1\n");
        }
        else {
            Serial.printf("RES SET_THRESHOLD -1\n");
        }
    }

    else if (command == "GET_LDR")
      Serial.printf("RES GET_LDR %d\n", ldrGetValue());

    else if (command == "GET_LED")
      Serial.printf("RES GET_LED %d\n", ledValue);
    
    else if (command == "GET_THRESHOLD")
      Serial.printf("RES GET_THRESHOLD %d\n", thresholdValue);

    else if (command == "GET_PA")
      Serial.printf("RES GET_PA %d\n",  bmpGetPaValue());

    else if (command == "GET_ALT")
      Serial.printf("RES GET_ALT %d\n", bmpGetAltValue());

    else if (command == "GET_TBMP")
      Serial.printf("RES GET_TBMP %d\n", bmpGetTempValue());

    else if (command == "GET_TEMP")
      Serial.printf("RES GET_TEMP %d\n", dhtGetTempValue());

    else if (command == "GET_HUM")
      Serial.printf("RES GET_HUM %d\n", dhtGetHumValue());

    else if (command == "GET_INFO")
      Serial.printf("RES GET_INFO %.2f ;%.2f ;%.2f ;%.2f ;%.2f ;%.2f; %.2f; %.2f\n",dhtGetHumValue() ,dhtGetTempValue() ,ldrGetValue() ,bmpGetTempValue() , bmpGetPaValue(), bmpGetAltValue(), avgTemp(), heatIndex());
    
    else
      Serial.println("ERR Unknown command.");
      
}
void ledUpdate() {
    if (ledMode == MODE_MANUAL || (ledMode == MODE_AUTO && ldrGetValue() < thresholdValue)) {
        ledcWrite(ledChannel, 255.0*(ledValue/100.0));
        ledcWrite(1, 255.0*(ledValue/100.0));
    }
    else {
        ledcWrite(ledChannel, 0);
        ledcWrite(1, 0);
    }
}

float ldrGetValue() {
    float ldrAnalog = analogRead(ldrPin);
    float ldrValue = 100*ldrAnalog/ldrMax;

    // Serial.printf("DBG LDR_MAX=%d, LDR_ANALOG=%d, LDR_VALUE=%d\n", ldrMax, ldrAnalog, ldrValue);

    return ldrValue > 100 ? 100 : ldrValue;
}


float bmpGetPaValue(){
    return (bmp.readPressure());
}
float bmpGetAltValue(){
    return (bmp.readAltitude());
}
float bmpGetTempValue(){
    return (bmp.readTemperature());
}
float dhtGetTempValue(){
    return (dht.readTemperature());
}
float dhtGetHumValue(){
    return (dht.readHumidity());
}
float avgTemp(){
    return (bmpGetTempValue() + dhtGetTempValue())/2.0;
}
float heatIndex(){
    float T = avgTemp();  // Temperatura em °C
    float H = dhtGetHumValue();   // Umidade relativa em %

    float HI = -8.78469475505616 + 1.61139411 * T + 2.33854883889091 * H - 0.14611605 * T * H
               - 0.012308094 * T * T - 0.016424828 * H * H + 0.002211732 * T * T * H
               + 0.00072546 * T * H * H - 0.000003582 * T * T * H * H;

    // Limita o valor do Heat Index para não ficar negativo
    if (HI < T) {
        HI = T; // O Heat Index não pode ser menor que a temperatura
    }

    return HI;
}
