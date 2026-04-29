#pragma once

#include <SDL.h>
#include "Shapes.h"

struct BoxCollider
{
    int x, y, w, h;
    SDL_Color color = { 0,255,0,255 }; // Color of the BoxCollider for visibility
    std::string tag = "";

    bool CheckCollision(const BoxCollider& other) const {
        return (x < other.x + other.w &&
            x + w > other.x &&
            y < other.y + other.h &&
            h + y > other.y);
    }
};



