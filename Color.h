#pragma once
#include <SDL.h>

struct Color
{
public:
    int r, g, b, a;

    // Empty Constructor
    Color()
    {
        r = g = b = a = 0;
    }

    // Constructor
    Color(int _r, int _g, int _b, int _a=255)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    Color(SDL_Color color)
    {
        r = color.r;
        g = color.g;
        b = color.b;
        a = color.a;
    }

    

    // Predefined Colors
    static const SDL_Color White; 
    static const SDL_Color Red;
    static const SDL_Color Green;
    static const SDL_Color Blue;
    static const SDL_Color Yellow;
    static const SDL_Color Black;

    // User Defined Color
    static const SDL_Color New(int r, int g, int b, int a=255);
    const SDL_Color GetSDLColor();
};


