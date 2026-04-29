#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
    : m_window(window), m_renderer(nullptr), m_texture(nullptr)
{
}

Renderer::~Renderer()
{
    SDL_DestroyTexture(m_texture);
    SDL_DestroyRenderer(m_renderer);
}

bool Renderer::Init()
{
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        std::cerr << "Error! Failed to create the renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    int screenWidth, screenHeight;
    SDL_GetWindowSize(m_window, &screenWidth, &screenHeight);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screenWidth, screenHeight);
    if (!m_texture)
    {
        std::cerr << "Error! Failed to create the texture: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::Clear()
{
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Renderer::Present()
{
    SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Renderer::GetRenderer()
{
    return m_renderer;
}

SDL_Texture* Renderer::LoadTexture(const char* filePath, SDL_Renderer* renderer)
{
    // Load image from file
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface)
    {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Create texture from surface pixels
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }

    // Free the loaded surface
    SDL_FreeSurface(surface);

    return texture;
}

void Renderer::DrawRect(const Rect& rect)
{
    if (rect.isVisible)
    {
        SDL_SetRenderDrawColor(m_renderer, rect.color.r, rect.color.g, rect.color.b, rect.color.a);
        SDL_Rect sdlRect = { rect.x, rect.y, rect.w, rect.h };
        SDL_RenderFillRect(m_renderer, &sdlRect);
    }

    if (rect.isVisible and rect.showCollider)
    {
        SDL_Rect rectA = { rect.BoxCollider.x, rect.BoxCollider.y, rect.BoxCollider.w, rect.BoxCollider.h };
        SDL_SetRenderDrawColor(m_renderer, rect.BoxCollider.color.r, rect.BoxCollider.color.g, rect.BoxCollider.color.b, rect.BoxCollider.color.a);
        SDL_RenderDrawRect(m_renderer, &rectA);
    }
}

void Renderer::DrawRect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(m_renderer, &rect);
}

void Renderer::DrawText2D(const Text& text, TTF_Font* font, SDL_Color color) {
    // Create a surface from the text

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.content.c_str(),color);
    if (!surface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Set the destination rectangle for rendering
    SDL_Rect dstRect = { text.x, text.y, text.w, text.h };
    SDL_RenderCopy(m_renderer, texture, NULL, &dstRect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Renderer::DrawText2D(const Text& text, Font& font, SDL_Color color) {
    // Create a surface from the text
    SDL_Surface* surface = TTF_RenderText_Blended(font.GetSDLFont(), text.content.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Set the destination rectangle for rendering
    SDL_Rect dstRect = { text.x, text.y, text.w, text.h };
    SDL_RenderCopy(m_renderer, texture, NULL, &dstRect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Renderer::DrawSprite(const Sprite& sprite)
{
    if (sprite.texture && sprite.isVisible) // Ensure the sprite has a texture and is visible
    {
        SDL_SetTextureColorMod(sprite.texture, sprite.color.r, sprite.color.g, sprite.color.b); // Set color mod
        SDL_Rect sdlRect = { sprite.x, sprite.y, sprite.w, sprite.h }; // Define the rectangle for rendering
        SDL_RenderCopy(m_renderer, sprite.texture, nullptr, &sdlRect); // Render the sprite
    }

    if (sprite.isVisible and sprite.showCollider)
    {
        SDL_Rect rect = { sprite.BoxCollider.x, sprite.BoxCollider.y, sprite.BoxCollider.w, sprite.BoxCollider.h };
        SDL_SetRenderDrawColor(m_renderer, sprite.BoxCollider.color.r, sprite.BoxCollider.color.g, sprite.BoxCollider.color.b, sprite.BoxCollider.color.a);
        SDL_RenderDrawRect(m_renderer, &rect);
    }
}



