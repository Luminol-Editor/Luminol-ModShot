#include "display.h"
#include <stdlib.h>

//SDL_DisplayMode Display::currentDisplayMode;

/*Display::Display() {
    SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
}*/

int Display::getScreenWidth() {
    SDL_DisplayMode currentDisplayMode;
    SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
    return currentDisplayMode.w;
}

int Display::getScreenHeight() {
    SDL_DisplayMode currentDisplayMode;
    SDL_GetCurrentDisplayMode(0, &currentDisplayMode);
    return currentDisplayMode.h;
}

bool Display::isWayland() {
    #ifdef __linux__
    if(getenv("DISPLAY") != NULL)
        return false;
    else if(getenv("WAYLAND_DISPLAY") != NULL)
        return true;
    #elif _WIN32
    return false;
    #endif
}

bool Display::isX() {
    #ifdef __linux__
    if(getenv("DISPLAY") != NULL)
        return true;
    else if(getenv("WAYLAND_DISPLAY") != NULL)
        return false;
    #elif _WIN32
    return false;
    #endif
}