#include "devweather_client.h"

using namespace std;

namespace devtitans::devweather {

void DevWeatherClient::start(int argc, char **argv) {
    cout << "Cliente DevWeather!" << endl;

    if (argc < 2) {
        cout << "Sintaxe: " << argv[0] << " <comando>" << endl;
        cout << "    Comandos: get-all" << endl;
        exit(1);
    }

    DevWeather devweather;  // Instancia a classe DevWeather

    // Comando get-all
    if (!strcmp(argv[1], "get-all")) {
        string data = devweather.getAll();  // Chama a função getAll()
        cout << "Dados dos sensores: " << data << endl;
    }
    else if (!strcmp(argv[1], "get-humidity")) {
    float humidity = devweather.getHumidity();
    cout << "Umidade: " << humidity << endl;
	}
	else if (!strcmp(argv[1], "get-temperatured")) {
    float temperatured = devweather.getTemperatureDHT();
    cout << "Temperatura DHT11: " << temperatured << endl;
	}
	else if (!strcmp(argv[1], "get-lux")) {
    float lux = devweather.getLux();
    cout << "Luminancia: " << lux << endl;
	}
	else if (!strcmp(argv[1], "get-temperatureb")) {
    float temperatureb = devweather.getTemperatureBMP();
    cout << "Temperatura BMP: " << temperatureb << endl;
	}
	else if (!strcmp(argv[1], "get-pressure")) {
    float pressure = devweather.getPressure();
    cout << "Pressao: " << pressure << endl;
	}
	else if (!strcmp(argv[1], "get-altitude")) {
    float altitude = devweather.getAltitude();
    cout << "Altitude: " << altitude << endl;
	}
	else if (!strcmp(argv[1], "get-temperaturem")) {
    float temperaturem = devweather.getAverageTemperature();
    cout << "Temperatura Media: " << temperaturem << endl;
	}
	else if (!strcmp(argv[1], "get-heatindex")) {
    float heatindex = devweather.getHeatIndex();
    cout << "Temperatura Media: " << heatindex << endl;
	}
    else {
        cout << "Comando inválido." << endl;
        exit(1);
    }
}

} // namespace

// MAIN

using namespace devtitans::devweather;

int main(int argc, char **argv) {
    DevWeatherClient client;
    client.start(argc, argv);
    return 0;
}
