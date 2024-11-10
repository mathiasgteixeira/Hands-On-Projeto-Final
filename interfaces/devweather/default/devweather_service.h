#pragma once

#include <android-base/logging.h>
#include <android/binder_process.h>
#include <android/binder_manager.h>

#include <aidl/devtitans/devweather/BnDevweather.h>            // Criado pelo AIDL automaticamente

#include "devweather_lib.h"                                   // Classe DevWeather (biblioteca)

using namespace devtitans::devweather;

namespace aidl::devtitans::devweather {

class DevweatherService : public BnDevweather {
    public:
						  ndk::ScopedAStatus connect(int32_t* _aidl_return) override;
						  ndk::ScopedAStatus getAll(std::string* _aidl_return) override;
						  ndk::ScopedAStatus getHumidity(float* _aidl_return) override;
						  ndk::ScopedAStatus getTemperatureDHT(float* _aidl_return) override;
						  ndk::ScopedAStatus getLux(float* _aidl_return) override;
						  ndk::ScopedAStatus getTemperatureBMP(float* _aidl_return) override;
						  ndk::ScopedAStatus getPressure(float* _aidl_return) override;
						  ndk::ScopedAStatus getAltitude(float* _aidl_return) override;
						  ndk::ScopedAStatus getAverageTemperature(float* _aidl_return) override;
						  ndk::ScopedAStatus getHeatIndex(float* _aidl_return) override;

    private:
        DevWeather devweather;                                 // Biblioteca
};

}
