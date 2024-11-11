package devtitans.devweatherapp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.graphics.Color;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.*;

import java.util.List;
import java.util.Locale;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "DevTITANS.DevweatherAppv2";

    private SensorManager sensorManager;
    private TextView textStatus, textTemperature, textHumidity, textHeatIndex, textLuminosity, textPressure, textAltitude;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textStatus =      findViewById(R.id.textStatus);
        textTemperature = findViewById(R.id.textTemperature);
        textHumidity =    findViewById(R.id.textHumidity);
        textHeatIndex =   findViewById(R.id.textHeatIndex);
        textPressure =    findViewById(R.id.textPressure);
        textLuminosity =  findViewById(R.id.textLuminosity);
        textAltitude =    findViewById(R.id.textAltitude);

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        List<Sensor> sensorList = sensorManager.getSensorList(Sensor.TYPE_LIGHT);

        String sensorListString = "";
        for (Sensor el : sensorList)
            sensorListString += el.getName() + " " + el.getStringType() + "\n";
        Log.println(Log.INFO, "LIGHT_TEST", sensorListString);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_light = sensorList.get(1);

        sensorManager.registerListener(listener_light, sensor_light, SensorManager.SENSOR_DELAY_NORMAL);

        sensorList = sensorManager.getSensorList(Sensor.TYPE_AMBIENT_TEMPERATURE);

        sensorListString = "";
        for (Sensor el : sensorList)
            sensorListString += el.getName() + " " + el.getStringType() + "\n";
        Log.println(Log.INFO, "TEMP_TEST", sensorListString);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_temperature = sensorList.get(1);

        sensorManager.registerListener(listener_temp, sensor_temperature, SensorManager.SENSOR_DELAY_NORMAL);

        sensorList = sensorManager.getSensorList(Sensor.TYPE_PRESSURE);

        sensorListString = "";
        for (Sensor el : sensorList)
            sensorListString += el.getName() + " " + el.getStringType() + "\n";
        Log.println(Log.INFO, "PRESSURE_TEST", sensorListString);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_pressure = sensorList.get(1);

        sensorManager.registerListener(listener_pressure, sensor_pressure, SensorManager.SENSOR_DELAY_NORMAL);

        sensorList = sensorManager.getSensorList(Sensor.TYPE_DEVICE_PRIVATE_BASE);

        sensorListString = "";
        for (Sensor el : sensorList)
            sensorListString += el.getName() + " " + el.getStringType() + "\n";
        Log.println(Log.INFO, "ALTITUDE_TEST", sensorListString);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_altitude = sensorList.get(0);

        sensorManager.registerListener(listener_altitude, sensor_altitude, SensorManager.SENSOR_DELAY_NORMAL);

        sensorList = sensorManager.getSensorList(Sensor.TYPE_RELATIVE_HUMIDITY);

        sensorListString = "";
        for (Sensor el : sensorList)
            sensorListString += el.getName() + " " + el.getStringType() + "\n";
        Log.println(Log.INFO, "HUM_TEST", sensorListString);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_humidity = sensorList.get(1);

        sensorManager.registerListener(listener_humidity, sensor_humidity, SensorManager.SENSOR_DELAY_NORMAL);

        sensorList = sensorManager.getSensorList(Sensor.TYPE_DEVICE_PRIVATE_BASE);

        sensorListString = "";
        for (Sensor el : sensorList)
            sensorListString += el.getName() + " " + el.getStringType() + "\n";
        Log.println(Log.INFO, "UP_TEST", sensorListString);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_update = sensorList.get(1);

        sensorManager.registerListener(listener_update, sensor_update, SensorManager.SENSOR_DELAY_NORMAL);

        // O sensor de luminosidade padrão vai ser o primeiro da lista, por isso o SmartLamp é o segundo
        Sensor sensor_heatIndex = sensorList.get(2);

        sensorManager.registerListener(listener_heatIndex, sensor_heatIndex, SensorManager.SENSOR_DELAY_NORMAL);

    }

    protected void onDestroy() {
        super.onDestroy();
        if (sensorManager != null) {
            sensorManager.unregisterListener(listener_light);
            sensorManager.unregisterListener(listener_temp);
            sensorManager.unregisterListener(listener_humidity);
            sensorManager.unregisterListener(listener_altitude);
            sensorManager.unregisterListener(listener_pressure);
            sensorManager.unregisterListener(listener_altitude);
            sensorManager.unregisterListener(listener_heatIndex);
        }
    }

    private SensorEventListener listener_light = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            textLuminosity.setText(String.format(Locale.ENGLISH,"%.2f Lx", value));
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    private SensorEventListener listener_temp = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            textTemperature.setText(String.format(Locale.ENGLISH,"%.2f °C", value));
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    private SensorEventListener listener_humidity = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            textHumidity.setText(String.format(Locale.ENGLISH,"%.2f %%", value));
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    private SensorEventListener listener_pressure = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            textPressure.setText(String.format(Locale.ENGLISH,"%.2f hPA", value/100));
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    private SensorEventListener listener_altitude = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            textAltitude.setText(String.format(Locale.ENGLISH,"%.2f M", value));
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    private SensorEventListener listener_update = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            if(value == 1.0) {
                textStatus.setText("Conectado");
                textStatus.setTextColor(Color.GREEN);
            }
            else{
                textStatus.setText("Disconectado");
                textStatus.setTextColor(Color.RED);
            }
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };

    private SensorEventListener listener_heatIndex = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            // The value of the first subscript in the values array is the current light intensity
            float value = event.values[0];
            textHeatIndex.setText(String.format(Locale.ENGLISH,"%.2f °C", value));
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    };
}
