#include "devweather_service.h"

using namespace aidl::devtitans::devweather;
using namespace std;                                      
using namespace ndk;


int main() {
  LOG(INFO) << "Iniciando Devweather AIDL Service ...";

		ABinderProcess_setThreadPoolMaxThreadCount(0);

		shared_ptr<DevweatherService> devweather_service = SharedRefBase::make<DevweatherService>();

		const string instance = std::string() + IDevweather::descriptor + "/default"; 
		binder_status_t status = AServiceManager_addService(devweather_service->asBinder().get(), instance.c_str());
		CHECK(status == STATUS_OK);

		LOG(INFO) << "Devweather AIDL Service iniciado com nome: " << instance;
		ABinderProcess_joinThreadPool();

		return EXIT_FAILURE;                                   // Não deve chegar nunca aqui
}
