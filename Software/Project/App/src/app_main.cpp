#include "app_main.h"
#include "App.hpp"
#include "AppConfig.h"

#include "TrimIdentificationApp.hpp"

extern "C" void app_main(const App_Config_t* cfg) {
    TrimIdentificationApp app = *cfg;
    App* a = &app;
    a->main();
}
