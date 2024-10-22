#pragma once                      // Inclui esse cabeçalho apenas uma vez

#include <iostream>               // std::cout (char-out) e std::endl (end-line)
#include <string.h>               // Função strcmp
#include <stdlib.h>               // Função atoi

#include "devweather_lib.h"        // Classe Smartlamp

namespace devtitans::devweather {  // Pacote devweather

class DevWeatherClient {          

    public:
        void start(int argc, char **argv);

};

} // namespace
