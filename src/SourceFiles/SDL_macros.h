#pragma once

#include <string>
#include <SDL.h>

/*
 * This file includes some SDL related macros
 */

// the RECT macro is used to automatically cast the argument to integer (since in GameObject the
// dimension, position, etc., are of type double
#define RECT(x,y,w,h) {static_cast<int>(x),static_cast<int>(y),static_cast<int>(w),static_cast<int>(h)}

// the COLOREXP macro is used to expand an SDL_Color variable into its components, so instead of writing
//
//    SDL_SetRenderDrawColor(game_->getRenderer(), color.r, color.g, color.b, color.a);
//
// we can simply write
//
// SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color));
#define COLOREXP(color) color.r, color.g, color.b, color.a

// Write colors in an easy way in hex, e.g., 0xaaff12ff. Instead of writing
//
//   { 0x44, 0x11, 0x22, 0x33 }
//
// simply write {COLOR(0x44112233)}
//
#define COLOR(num) static_cast<Uint8>((num >> 24) & 0xff), static_cast<Uint8>((num >> 16) & 0xff), static_cast<Uint8>((num >> 8) & 0xff), static_cast<Uint8>(num & 0xff)

// converts string of the form "#4455AAFF" to a corresponding SDL_Color
//
SDL_Color hex2sdlcolor(std::string input);
