#pragma once

#include "Shapes.h"
#include <SDL_ttf.h>
#include <SDL.h>
#include <iostream>

class Renderer
{
private:
    SDL_Renderer* m_renderer;  // SDL renderer
    SDL_Texture* m_texture;    // Texture used for rendering
    SDL_Window* m_window;      // The window to which the renderer is attached

public:
    Renderer(SDL_Window* window);               // Constructor to initialize the renderer
    ~Renderer();                                // Destructor to clean up resources

    bool Init();                                // Initialize the renderer and texture
    void Clear();                               // Clear the renderer (set to a default color)
    void Present();                             // Present the rendered content on screen

    SDL_Renderer* GetRenderer();

    void DrawRect(const Rect& rect);                             // Draw A Rectangle
    void DrawRect(int x, int y, int w, int h, SDL_Color color);  // Draw a rectangle

    void DrawSprite(const Sprite& sprite);

    void DrawText2D(const Text& text, TTF_Font* font, SDL_Color color);
    void DrawText2D(const Text& text, Font& font, SDL_Color color);

    SDL_Texture* LoadTexture(const char* filePath, SDL_Renderer* renderer);
};




