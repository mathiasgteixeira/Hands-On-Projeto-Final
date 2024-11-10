#pragma once                           // Inclui esse cabeçalho apenas uma vez

#include <fstream>                     // Classe ifstream
#include <sys/stat.h>                  // Função e struct stat



using namespace std;                   // Permite usar string diretamente ao invés de std::string

namespace devtitans::devweather {       // Pacote devweather

class DevWeather {
    public:
        /**
         * Verifica se o diretório /sys/kernel/devweather existe.
         * Se existir, o dispositivo está conectado via USB.
         *
         * Retorna:
         *      0: dispositivo não encontrado
         *      1: sucesso
         */
        int connect();

        /**
         * Lê uma string com os dados de todos os sensores no formato
         * "%.2f; %.2f; %.2f; %.2f; %.2f; %.2f; %.2f; %.2f\n".
         *
         * Retorna:
         *      String contendo os dados dos sensores ou
         *      uma string vazia em caso de erro.
         */
        string getAll();
        
         /**
         * Metodos para obter cada valor de sensor individualmente

         */
        float getHumidity();
		float getTemperatureDHT();
		float getLux();
		float getTemperatureBMP();
		float getPressure();
		float getAltitude();
		float getAverageTemperature();
		float getHeatIndex();

    private:
        /**
         * Método para ler o conteúdo de um arquivo no diretório
         * /sys/kernel/devweather.
         *
         * Retorna:
         *      String contendo o valor lido do arquivo ou
         *      uma string vazia em caso de erro.
         */
        string readFileValue(const string &file);
};

} // namespace devtitans::devweather
