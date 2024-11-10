#include "devweather_lib.h"

using namespace std;                                   // Permite usar string, ifstream diretamente ao invés de std::string

namespace devtitans::devweather {                       // Entra no pacote devtitans::devweather

int DevWeather::connect() {
    char dirPath[] = "/sys/kernel/devweather";
    struct stat dirStat;
    if (stat(dirPath, &dirStat) == 0)
        if (S_ISDIR(dirStat.st_mode))
            return 1;                                  // Se o diretório existir, retorna 1

    // Diretório não existe
    return 0;                                          // Dispositivo não encontrado
}

string DevWeather::readFileValue(const string &file) {
    int connected = this->connect();

    if (connected == 1) {                              // Conectado. Vamos solicitar o valor ao dispositivo
        string value;
        string filename = string("/sys/kernel/devweather/") + file;
        ifstream fileStream(filename);                 // Abre o arquivo do módulo do kernel

        if (fileStream.is_open()) {                    // Verifica se o arquivo foi aberto com sucesso
            getline(fileStream, value);                // Lê a linha completa do arquivo
            fileStream.close();
            return value;
        }
    }

    // Se chegou aqui, não foi possível conectar ou se comunicar com o dispositivo
    return "";
}

string DevWeather::getAll() {
    // Lê os dados do atributo "allc", que corresponde aos valores dos sensores
    string data = readFileValue("allc");

    // Retorna a string com os dados ou uma string vazia em caso de erro
    return data;
}
float DevWeather::getHumidity() {
    string data = getAll();
    float humidity;
    sscanf(data.c_str(), "%f; %*f; %*f; %*f; %*f; %*f; %*f; %*f", &humidity);
    return humidity;
}

float DevWeather::getTemperatureDHT(){
    string data = getAll();
    float temperatured;
    sscanf(data.c_str(), "%*f; %f; %*f; %*f; %*f; %*f; %*f; %*f", &temperatured);
    return temperatured;
}

float DevWeather::getLux() {
    string data = getAll();
    float lux;
    sscanf(data.c_str(), "%*f; %*f; %f; %*f; %*f; %*f; %*f; %*f", &lux);
    return lux;
}

float DevWeather::getTemperatureBMP(){
    string data = getAll();
    float temperatureb;
    sscanf(data.c_str(), "%*f; %*f; %*f; %f; %*f; %*f; %*f; %*f", &temperatureb);
    return temperatureb;
}

float DevWeather::getPressure(){
    string data = getAll();
    float pressure;
    sscanf(data.c_str(), "%*f; %*f; %*f; %*f; %f; %*f; %*f; %*f", &pressure);
    return pressure;
}

float DevWeather::getAltitude(){
    string data = getAll();
    float altitude;
    sscanf(data.c_str(), "%*f; %*f; %*f; %*f; %*f; %f; %*f; %*f", &altitude);
    return altitude;
}

float DevWeather::getAverageTemperature(){
    string data = getAll();
    float temperaturem;
    sscanf(data.c_str(), "%*f; %*f; %*f; %*f; %*f; %*f; %f; %*f", &temperaturem);
    return temperaturem;
}

float DevWeather::getHeatIndex(){
    string data = getAll();
    float heatindex;
    sscanf(data.c_str(), "%*f; %*f; %*f; %*f; %*f; %*f; %*f; %f", &heatindex);
    return heatindex;
}



} // namespace devtitans::devweather
