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
      Serial.printf("RES GET_INFO %d;%d;%d;%d;%d;%d\n",ldrGetValue(),dhtGetTempValue(), dhtGetHumValue(), bmpGetPaValue(), bmpGetAltValue(), bmpGetTempValue());
    
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

int ldrGetValue() {
    int ldrAnalog = analogRead(ldrPin);
    int ldrValue = 100*ldrAnalog/ldrMax;

    // Serial.printf("DBG LDR_MAX=%d, LDR_ANALOG=%d, LDR_VALUE=%d\n", ldrMax, ldrAnalog, ldrValue);

    return ldrValue > 100 ? 100 : ldrValue;
}


int bmpGetPaValue(){
    return int(bmp.readPressure());
}
int bmpGetAltValue(){
    return int(bmp.readAltitude());
}
int bmpGetTempValue(){
    return int(bmp.readTemperature());
}
int dhtGetTempValue(){
    return int(dht.readTemperature());
}
int dhtGetHumValue(){
    return int(dht.readHumidity());
}
