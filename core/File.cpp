#include "File.h"
#include <iostream>
using namespace std;

File::File(std::string& filename, const shared_ptr<SDL_Renderer>& r) : renderer(r) {
    image = GIF_LoadImage(filename.c_str());
    assert(image != nullptr);
    textures = new SDL_Texture*[image->num_frames];
    for (int i = 0; i < image->num_frames; ++i) {
        textures[i] = SDL_CreateTextureFromSurface(renderer.get(), image->frames[i]->surface);
    }
}

File::~File() {
    GIF_FreeImage(image);
    for (int i = 0; i < image->num_frames; ++i)
        SDL_DestroyTexture(textures[i]);
    if (timerId != 0) SDL_RemoveTimer(timerId);
}


void File::render() {
    int i = currentFrame;
    //    for (int i = 0; i <= currentFrame; ++i) {
    SDL_RenderCopy(renderer.get(), textures[i], nullptr, nullptr);
    //    }
}

void File::drawInfo() {
    GIF_Frame* frame = image->frames[currentFrame];
    ImGui::SetNextWindowSizeConstraints(ImVec2(150, 150), ImVec2(300, 300));
    ImGui::Begin("Info");

    ImGui::SliderInt("Frame", &currentFrame, 0, image->num_frames - 1);


    ImGui::BeginDisabled(currentFrame == 0);
    if (ImGui::ArrowButton("Prev", ImGuiDir_Left)) --currentFrame;
    ImGui::EndDisabled();
    ImGui::SameLine();
    ImGui::BeginDisabled(currentFrame == image->num_frames - 1);
    if (ImGui::ArrowButton("Next", ImGuiDir_Right)) ++currentFrame;
    ImGui::EndDisabled();

    ImGui::Text("Delay(ms): %d", frame->delay);



    if (ImGui::Button("Play")) {
        if (timerId != 0) SDL_RemoveTimer(timerId);
        timerId = SDL_AddTimer(frame->delay, timer_callback, this);
    }
    ImGui::SameLine();
    if (ImGui::Button("Stop")) {
        if (timerId != 0) SDL_RemoveTimer(timerId);
    }

    ImGui::Checkbox("Looped", &looped);


    ImGui::End();
}
Uint32 File::timer_callback(Uint32 interval, void* param) {
    File* self = (File*) param;
    if (self->looped) {
        self->currentFrame = (self->currentFrame + 1) % self->image->num_frames;
    } else {
        if (self->currentFrame < self->image->num_frames - 1) {
            ++self->currentFrame;
        }
    }

    return interval;
}
