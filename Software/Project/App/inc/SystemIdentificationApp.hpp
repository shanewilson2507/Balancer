#include "App.hpp"

class SystemIdentificationApp : public App {
public:
    SystemIdentificationApp(const App_Config_t& cfg);
    void main(void) override;
};