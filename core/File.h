#ifndef IMGIF_FILE_H
#define IMGIF_FILE_H


#include <SDL2/SDL.h>
#include <gif_lib.h>
#include <imgui.h>
#include <memory>
#include <string>

#include "../gifwrap/SDL_gifwrap.h"

class File {
private:
    std::shared_ptr<SDL_Renderer> renderer;

    GIF_Image* image;
    SDL_Texture** textures;
    SDL_TimerID timerId = 0;

    int currentFrame = 0;
    bool looped = true;

    static Uint32 timer_callback(Uint32 interval, void* param);

public:
    File(std::string& filename, const std::shared_ptr<SDL_Renderer>& r);
    ~File();
    void render();
    void drawInfo();
};


#endif//IMGIF_FILE_H
