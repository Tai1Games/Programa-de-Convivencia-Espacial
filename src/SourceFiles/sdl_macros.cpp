#include "SDL_macros.h"

// converts string of the form "#4455AAFF" to a corresponding SDL_Color
//
SDL_Color hex2sdlcolor(std::string input) {

    if (input[0] == '#')
        input.erase(0, 1);

    unsigned long value = stoul(input, nullptr, 16);

    SDL_Color color;

    color.r = (value >> 24) & 0xff;
    color.g = (value >> 16) & 0xff;
    color.b = (value >> 8) & 0xff;
    color.a = (value >> 0) & 0xff;
    return color;
}
