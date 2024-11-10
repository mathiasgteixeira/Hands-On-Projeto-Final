#include "devweather_service.h"

namespace aidl::devtitans::devweather {
  ndk::ScopedAStatus DevweatherService::connect(int32_t* _aidl_return) {
						*_aidl_return = this->devweather.connect();
						LOG(INFO) << "connect(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getAll(std::string* _aidl_return) {
						*_aidl_return = this->devweather.getAll();
						LOG(INFO) << "getAll(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getHumidity(float* _aidl_return) {
						*_aidl_return = this->devweather.getHumidity();
						LOG(INFO) << "getHumidity(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getTemperatureDHT(float* _aidl_return) {
			   *_aidl_return = this->devweather.getTemperatureDHT();
						LOG(INFO) << "getTemperatureDHT(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getLux(float* _aidl_return) {
						*_aidl_return = this->devweather.getLux();
						LOG(INFO) << "getLux(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getTemperatureBMP(float* _aidl_return) {
						*_aidl_return = this->devweather.getTemperatureBMP();
						LOG(INFO) << "getTemperatureBMP(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getPressure(float* _aidl_return) {
						*_aidl_return = this->devweather.getPressure();
						LOG(INFO) << "getPressure(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getAltitude(float* _aidl_return) {
			   *_aidl_return = this->devweather.getAltitude();
						LOG(INFO) << "getAltitude(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getAverageTemperature(float* _aidl_return) {
						*_aidl_return = this->devweather.getAverageTemperature();
						LOG(INFO) << "getAverageTemperature(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
  ::ndk::ScopedAStatus DevweatherService::getHeatIndex(float* _aidl_return) {
						*_aidl_return = this->devweather.getHeatIndex();
						LOG(INFO) << "getHeatIndex(): " << *_aidl_return;
						return ndk::ScopedAStatus::ok();
  }
	

}
