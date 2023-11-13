#ifndef IMGIF_APP_H
#define IMGIF_APP_H

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <string>

#include "File.h"

#include "../imfilebrowser/imfilebrowser.h"

class App {
private:
    bool failed = false;
    std::string filename;
    ImGui::FileBrowser fileDialog;

    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;
    File* file = nullptr;

    bool initSdl();
    bool initImGui();
    void destroy();
    void loadFile();

    void menuBar();

public:
    App();
    void update();
    void run();
};


#endif//IMGIF_APP_H
