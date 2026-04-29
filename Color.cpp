#include "Color.h"


const SDL_Color Color::White = { 255, 255, 255, 255 };  // White Color (R,G,B,A)
const SDL_Color Color::Red = { 255, 0, 0, 255 };        // Red Color
const SDL_Color Color::Green = { 0, 255, 0, 255 };      // Green Color
const SDL_Color Color::Blue = { 0, 0, 255, 255 };       // Blue Color
const SDL_Color Color::Yellow = { 255, 255, 0, 255 };   // Yellow Color
const SDL_Color Color::Black = {0, 0, 0, 255 };         // Black Color


const SDL_Color Color::New(int r, int g, int b, int a)
{
    const SDL_Color color = { r,g,b,a };
    return color;
}

const SDL_Color Color::GetSDLColor()
{
    SDL_Color color = { r,g,b,a };
    return color;
}