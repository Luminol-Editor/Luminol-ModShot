#pragma once
#include <SDL.h>

class Display {
public:
    SDL_DisplayMode currentDisplayMode;

    //Display();
    static int getScreenWidth();
    static int getScreenHeight();
    static bool isWayland();
    static bool isX();
};