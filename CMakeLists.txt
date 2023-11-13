cmake_minimum_required(VERSION 3.21)
project(ImGif)

set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(SDL2 REQUIRED)
include_directories(ImGif ${SDL2_INCLUDE_DIRS})


add_executable(ImGif
        ../bindings/imgui_impl_sdlrenderer.h
        ../bindings/imgui_impl_sdlrenderer.cpp
        ../bindings/imgui_impl_sdl.h
        ../bindings/imgui_impl_sdl.cpp
        gifwrap/SDL_gifwrap.h
        gifwrap/SDL_gifwrap.c
        main.cpp
        core/App.cpp core/App.h core/File.cpp core/File.h imfilebrowser/imfilebrowser.h)

target_link_libraries(ImGif ${CONAN_LIBS} ${SDL2_LIBRARIES})