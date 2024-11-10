package devtitans.devweatherapp;

import androidx.appcompat.app.AppCompatActivity;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.*;

import android.os.ServiceManager;
import android.os.IBinder;
import android.os.RemoteException;

import devtitans.devweather.IDevweather;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "DevTITANS.DevweatherAppv2";

    private TextView textStatus, textTemperature, textHumidity, textHeatIndex, textLuminosity, textPressure, textAltitude;
    private IBinder binder;
    private IDevweather service;

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

        binder = ServiceManager.getService("devtitans.devweather.IDevweather/default");
        if (binder != null) {
            service = IDevweather.Stub.asInterface(binder);
            if (service != null)
                Toast.makeText(this, "Serviço Devweather acessado com sucesso.", Toast.LENGTH_LONG).show();
            else
                Toast.makeText(this, "Erro ao acessar o serviço Devweather!", Toast.LENGTH_LONG).show();
        }
        else
            Toast.makeText(this, "Erro ao acessar o Binder!", Toast.LENGTH_LONG).show();

        updateAll(null);
    }

    public void updateAll(View view) {
        Log.d(TAG, "Atualizando dados do dispositivo ...");

        if (binder == null) {
            textStatus.setText("Erro no Binder");
            textStatus.setTextColor(Color.parseColor("#73312f"));
        }
        else if (service == null) {
            textStatus.setText("Erro no Serviço");
            textStatus.setTextColor(Color.parseColor("#73312f"));
        }
        else {
            textStatus.setText("Atualizando ...");
            textStatus.setTextColor(Color.parseColor("#c47e00"));

            try {
                float humidity = service.getHumidity();
                textHumidity.setText(String.valueOf(humidity));

                float temperature = service.getAverageTemperature();
                textTemperature.setText(String.valueOf(temperature));

                float heatIndex = service.getHeatIndex();
                textHeatIndex.setText(String.valueOf(heatIndex));

                float luminosity = service.getLux();
                textLuminosity.setText(String.valueOf(luminosity));

                float pressure = service.getPressure();
                textPressure.setText(String.valueOf(pressure));

                float altitude = service.getAltitude();
                textAltitude.setText(String.valueOf(altitude));

                int status = service.connect();
                if (status == 0) {
                    textStatus.setText("Desconectado");
                    textStatus.setTextColor(Color.parseColor("#73312f"));
                }
                else if (status == 1) {
                    textStatus.setText("Conectado");
                    textStatus.setTextColor(Color.parseColor("#6d790c"));
                }

            } catch (android.os.RemoteException e) {
                Toast.makeText(this, "Erro ao acessar o Binder!", Toast.LENGTH_LONG).show();
                Log.e(TAG, "Erro atualizando dados:", e);
            }

        }

    }
}
