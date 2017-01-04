#include "ofApp.h"

int main()
{
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3,3);
    settings.width = 2048;
    settings.height = (settings.width * (9.0/16));

    auto window = ofCreateWindow(settings);
    auto app = make_shared<ofApp>();
    ofRunApp(window, app);

    return ofRunMainLoop();
}
