#include "app_main.h"
#include "App.hpp"
#include "AppConfig.h"

#include "SystemIdentificationApp.hpp"

extern "C" void app_main(const App_Config_t* cfg) {
    SystemIdentificationApp app = *cfg;
    App* a = &app;
    a->main();
}
