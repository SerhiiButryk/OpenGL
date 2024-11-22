#include "public/XEngine.h"
#include "Gui.h"

namespace client {
    /**
     *  Our application
     */
    class Application : public xengine::Application {
    public:
        Application() = default;
        virtual ~Application() = default;

        void onCreate() override {}
        void onDestroy() override {}

        std::string getResourcePath() override { return "../../engine/res"; }

        xengine::UI* createUI() { return new Gui(); }
    };
}

/**
*  Creates application
*/
xengine::Application* createApplication() {
    return new client::Application();
}