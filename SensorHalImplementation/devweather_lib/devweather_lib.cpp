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
    string data = readFileValue("info");
    sscanf(data.c_str(), "%f ;%f ;%f ;%f ;%f ;%f; %f; %f", &this->dados[0], &this->dados[1], &this->dados[2], &this->dados[3], &this->dados[4], &this->dados[5], &this->dados[6], &this->dados[7]);
    // Retorna a string com os dados ou uma string vazia em caso de erro
    return data;
}
float DevWeather::getHumidity() {
    return this->dados[0];
}

float DevWeather::getTemperatureDHT(){
    return this->dados[1];
}

float DevWeather::getLux() {
    return this->dados[2];
}

float DevWeather::getTemperatureBMP(){
    return this->dados[3];
}

float DevWeather::getPressure(){
    return this->dados[4];
}

float DevWeather::getAltitude(){
    return this->dados[5];
}

float DevWeather::getAverageTemperature(){
    return this->dados[6];
}

float DevWeather::getHeatIndex(){
    return this->dados[7];
}



} // namespace devtitans::devweather

