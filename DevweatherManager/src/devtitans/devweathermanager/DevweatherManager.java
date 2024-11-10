package devtitans.devweathermanager;

import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import android.os.RemoteException;

import devtitans.devweather.IDevweather;                      // Criado pelo AIDL

public class DevweatherManager {
    private static final String TAG = "DevTITANS.DevweatherManager";
    private IBinder binder;
    private IDevweather service;

    private static DevweatherManager instance;

    // Construtor. Configura a "instância da classe" (objeto) recém-criada. 
    // Note o "private" no construtor. Essa classe só pode ser instanciada dentro desse arquivo.
    private DevweatherManager() {
        Log.d(TAG, "Nova (única) instância do DevweatherManager ...");

        binder = ServiceManager.getService("devtitans.devweather.IDevweather/default");
        if (binder != null) {
            service = IDevweather.Stub.asInterface(binder);
            if (service != null)
                Log.d(TAG, "Serviço Devweather acessado com sucesso.");
            else
                Log.e(TAG, "Erro ao acessar o serviço Devweather!");
        }
        else
            Log.e(TAG, "Erro ao acessar o Binder!");
    }

    // Acessa a (única) instância dessa classe. Se ela não existir ainda, cria.
    // Note o "static" no método. Podemos executá-lo sem precisar instanciar um objeto.
    public static DevweatherManager getInstance() {
        if (instance == null)
            instance = new DevweatherManager();

        return instance;
    }

    public int connect() throws RemoteException {
        Log.d(TAG, "Executando método connect() ...");
        return service.connect();
    }

    public float getHumidity() throws RemoteException {
        Log.d(TAG, "Executando método float getHumidity() ...");
        return service.getHumidity();
    }
    
    public float getTemperatureDHT() throws RemoteException {
        Log.d(TAG, "Executando método float getTemperatureDHT() ...");
        return service.getTemperatureDHT();
    }
    
    public float getLux() throws RemoteException {
        Log.d(TAG, "Executando método float getLux() ...");
        return service.getLux();
    }
    
    public float getTemperatureBMP() throws RemoteException {
        Log.d(TAG, "Executando método float getTemperatureBMP() ...");
        return service.getTemperatureBMP();
    }
    
    public float getPressure() throws RemoteException {
        Log.d(TAG, "Executando método float getPressure() ...");
        return service.getPressure();
    }
    
    public float getAltitude() throws RemoteException {
        Log.d(TAG, "Executando método float getAltitude() ...");
        return service.getAltitude();
    }
    
    public float getAverageTemperature() throws RemoteException {
        Log.d(TAG, "Executando método float getAverageTemperature() ...");
        return service.getAverageTemperature();
    }
    
    public float getHeatIndex() throws RemoteException {
        Log.d(TAG, "Executando método float getHeatIndex() ...");
        return service.getHeatIndex();
    }
}
