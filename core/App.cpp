#include "App.h"

#include "../bindings/imgui_impl_sdl.h"
#include "../bindings/imgui_impl_sdlrenderer.h"
#include <memory>

using namespace std;

App::App() {
    if (!initSdl()) {
        failed = true;
    }
    if (!initImGui()) {
        failed = true;
    }
    filename = "sample.gif";
    loadFile();

    fileDialog.SetTitle("Open file");
    fileDialog.SetTypeFilters({".gif"});
}


void App::update() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0xff);
    SDL_RenderClear(renderer.get());

    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    menuBar();
    if (file) {
        file->drawInfo();
        file->render();
    }

    fileDialog.Display();
    if (fileDialog.HasSelected()) {
        filename = fileDialog.GetSelected().string();
        loadFile();

        fileDialog.ClearSelected();
        fileDialog.Close();
    }


    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(renderer.get());
}

void App::run() {
    if (failed) {
        cerr << "App has failed to init and can't run" << endl;
        return;
    }
    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) quit = true;
        }
        update();
    }
    destroy();
}


bool App::initSdl() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        cerr << "Can't init SDL" << endl;
        return false;
    }

    window = shared_ptr<SDL_Window>(
            SDL_CreateWindow("ImGif", 100, 100, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI),
            SDL_DestroyWindow);

    renderer = shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer);

    return true;
}

bool App::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplSDL2_InitForSDLRenderer(window.get());
    ImGui_ImplSDLRenderer_Init(renderer.get());


    ImGui::StyleColorsDark();

    return true;
}

void App::loadFile() {
    delete file;
    file = new File(filename, renderer);
}

void App::destroy() {
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui::DestroyContext();
}
void App::menuBar() {
    ImGui::BeginMainMenuBar();
    if (ImGui::MenuItem("Open") && !fileDialog.IsOpened()) {
        fileDialog.Open();
    }
    ImGui::EndMainMenuBar();
}
