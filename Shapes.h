#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>
#include <vector>

#include "Color.h"
#include "DataStructures.h"
#include "DebugHelp.h"
#include "Collider.h"



// Class Representing A Basic Rectangle
class Rect
{
public:
    int x, y;  // Positions Of Rectangle
    int w, h;  // Dimensions Of Rectangle

    SDL_Color color;    // Color Of Rectangle

    std::string tag = "";
    bool isVisible = true; // Hides The Rectangle If False
    bool lockTransform = false; // Locks Any Changes To Position
    bool showCollider = true;

    BoxCollider BoxCollider;

    // Constructor
    Rect(int _x, int _y, int _w, int _h, SDL_Color _color)
    {
        x = _x;    y = _y;
        h = _h;    w = _w;
        color = _color;
        BoxCollider = { x, y, w, h, {255, 0, 0, 255} };
    }

    // Default constructor
    Rect()
    {
        x = y = w = h = 0;
        color = Color::Black;
    }
   
    // Utility method to set the rectangle properties
    void Set(int _x, int _y, int _w, int _h, SDL_Color _color, float _rotation)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        color = _color;
        UpdateCollider();
    }

    // Increase The Scale
    void UpScale(int scale)
    {
        if (!lockTransform)
        {
            w += scale;
            h += scale;
        }

        if (w < 0) w = 0; // Prevent negative width
        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }
    // Decrease The Scale
    void DownScale(int scale)
    {
        if (!lockTransform)
        {
            w -= scale;
            h -= scale;
        }
        if (w < 0) w = 0; // Prevent negative width
        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }
    // Adjust The Overall Scale
    void Scale(int scaleX, int scaleY)
    {
        if (!lockTransform)
        {
            w += scaleX;
            h += scaleY;
        }

        if (w < 0) w = 0; // Prevent negative width
        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }
    // Adjust The X-Axis Scale
    void ScaleX(int scaleX)
    {
        if (!lockTransform)
            w += scaleX;
        if (w < 0) w = 0; // Prevent negative width
        UpdateCollider();
    }
    // Adjust The X-Axis Scale
    void ScaleY(int scaleY)
    {
        if (!lockTransform)
            h += scaleY;

        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }


    // Move The Rectangle To The Specified Position
    void Move(const Vector2& vect)
    {
        if (!lockTransform)
        {
            x += vect.x;
            y += vect.y;
        }
        UpdateCollider();
    }
    void Move(int _x, int _y)
    {
        if (!lockTransform)
        {
            x += _x;
            y += _y;
        }
        UpdateCollider();
    }


    // Sets The Position Of The Rectangle
    void SetPosition(int _x, int _y)
    {
        if (!lockTransform)
            x = _x;  y = _y;

        UpdateCollider();
    }

    // Sets The Scale Of The Rectangle
    void SetScale(int _x, int _y)
    {
        if (!lockTransform)
            x = _x;  y = _y;

        UpdateCollider();
    }

    // Move In Specific Directions
    void MoveLeft(int _x)
    {
        if (!lockTransform)
        {
            x -= _x;
        }
        UpdateCollider();
    }
    void MoveRight(int _x)
    {
        if (!lockTransform)
        {
            x += _x;
        }
        UpdateCollider();
    }
    void MoveUp(int _y)
    {
        if (!lockTransform)
        {
            y -= _y;
        }
        UpdateCollider();
    }
    void MoveDown(int _y)
    {
        if (!lockTransform)
        {
            y += _y;
        }
        UpdateCollider();
    }

    // Checks Collision
   /* bool CheckCollision(const Sprite& other) const
    {
        return (BoxCollider.x < other.BoxCollider.x + other.BoxCollider.w and
            BoxCollider.x + BoxCollider.w > other.BoxCollider.x and
            BoxCollider.y < other.BoxCollider.y + other.Collider.h and
            BoxCollider.y + Collider.h > other.BoxCollider.y);
    }
    bool CheckCollision(const Rect& other) const
    {
        return (BoxCollider.x < other.BoxCollider.x + other.BoxCollider.w and
            BoxCollider.x + BoxCollider.w > other.BoxCollider.x and
            BoxCollider.y < other.BoxCollider.y + other.Collider.h and
            BoxCollider.y + Collider.h > other.BoxCollider.y);
    }*/

    void DebugData() const
    {
       
        Print::YellowLine("Transform: ");

        // For Position
        Print::Cyan("Position:   X = ");
        std::cout << x;
        Print::Cyan("     Y = ");
        std::cout << y << std::endl;

        // For Scale
        Print::Green("Scale:      X = ");
        std::cout << w;
        Print::Green("     Y = ");
        std::cout << h << std::endl;

        // Others
        Print::Magenta("Visible: ");
        std::cout << ((isVisible) ? "True " : "False ");
        Print::Magenta("      Lock Transform: ");
        std::cout << ((lockTransform) ? "True\n" : "False\n");
        system("cls");
    }

    void UpdateCollider()
    {
        BoxCollider.x = x;
        BoxCollider.y = y;
    }

    void SetTag(std::string _tag)
    {
        tag = _tag;
        BoxCollider.tag = _tag;
    }
    bool Comparetag(std::string _tag)
    {
        if (tag == _tag and tag == BoxCollider.tag)
            return true;

        return false;
    }
};


// Class Representing A Basic Sprite 
class Sprite
{
public:
    int x, y;          // Position of the sprite
    int w, h;          // Dimensions of the sprite


    SDL_Texture* texture; // Texture for the sprite
    SDL_Color color;   // Color tint (optional)
    std::string tag = "";

    bool isVisible = true;
    bool lockTransform = false;
    bool showCollider = false;

    

    // BoxCollider structure
    BoxCollider BoxCollider;

    // Constructor
    Sprite(int _x, int _y, int _w, int _h, SDL_Texture* _texture)
        : x(_x), y(_y), w(_w), h(_h), texture(_texture), color({ 255, 255, 255, 255 }) // White tint by default
    {
        BoxCollider = { x, y, w, h, {255, 0, 0, 255}};
    } 

    // Default constructor
    Sprite()
        : x(0), y(0), w(0), h(0), texture(nullptr), color({ 255, 255, 255, 255 }) {
     
    }

    
    // Utility method to set the rectangle properties
    void Set(int _x, int _y, int _w, int _h, SDL_Color _color, float _rotation)
    {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
        color = _color;
        UpdateCollider();
    }

    // Increase The Scale
    void UpScale(int scale)
    {
        if (!lockTransform)
        {
            w += scale;
            h += scale;
        }

        if (w < 0) w = 0; // Prevent negative width
        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }
    // Decrease The Scale
    void DownScale(int scale)
    {
        if (!lockTransform)
        {
            w -= scale;
            h -= scale;
        }
        if (w < 0) w = 0; // Prevent negative width
        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }
    // Adjust The Overall Scale
    void Scale(int scaleX, int scaleY)
    {
        if (!lockTransform)
        {
            w += scaleX;
            h += scaleY;
        }

        if (w < 0) w = 0; // Prevent negative width
        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }
    // Adjust The X-Axis Scale
    void ScaleX(int scaleX)
    {
        if (!lockTransform)
            w += scaleX;
        if (w < 0) w = 0; // Prevent negative width
        UpdateCollider();
    }
    // Adjust The X-Axis Scale
    void ScaleY(int scaleY)
    {
        if (!lockTransform)
            h += scaleY;

        if (h < 0) h = 0; // Prevent negative height
        UpdateCollider();
    }


    // Move The Rectangle To The Specified Position
    void Move(const Vector2& vect)
    {
        if (!lockTransform)
        {
            x += vect.x;
            y += vect.y;
        }
        UpdateCollider();
    }
    void Move(int _x, int _y)
    {
        if (!lockTransform)
        {
            x += _x;
            y += _y;
        }
        UpdateCollider();
    }


    // Sets The Position Of The Rectangle
    void SetPosition(int _x, int _y)
    {
        if (!lockTransform)
            x = _x;  y = _y;

        UpdateCollider();
    }

    // Sets The Scale Of The Rectangle
    void SetScale(int _x, int _y)
    {
        if (!lockTransform)
            x = _x;  y = _y;

        UpdateCollider();
    }

    // Move In Specific Directions
    void MoveLeft(int _x)
    {
        if (!lockTransform)
        {
            x -= _x;
        }
        UpdateCollider();
    }
    void MoveRight(int _x)
    {
        if (!lockTransform)
        {
            x += _x;
        }
        UpdateCollider();
    }
    void MoveUp(int _y)
    {
        if (!lockTransform)
        {
            y -= _y;
        }
        UpdateCollider();
    }
    void MoveDown(int _y)
    {
        if (!lockTransform)
        {
            y += _y;
        }
        UpdateCollider();
    }

    // Checks Collision
    bool CheckCollision(const Sprite& other) const 
    {
        return (BoxCollider.x < other.BoxCollider.x + other.BoxCollider.w and
            BoxCollider.x + BoxCollider.w > other.BoxCollider.x and
            BoxCollider.y < other.BoxCollider.y + other.BoxCollider.h and
            BoxCollider.y + BoxCollider.h > other.BoxCollider.y);
    }
    bool CheckCollision(const Rect& other) const
    {
        return (BoxCollider.x < other.BoxCollider.x + other.BoxCollider.w and
            BoxCollider.x + BoxCollider.w > other.BoxCollider.x and
            BoxCollider.y < other.BoxCollider.y + other.BoxCollider.h and
            BoxCollider.y + BoxCollider.h > other.BoxCollider.y);
    }

    void DebugData() const
    {
        /*std::cout << "Transform: \n";
        std::cout << "Position:   X = " << x << "     Y = " << y << std::endl;
        std::cout << "Scale:      X = " << h << "     Y = " << w << std::endl;
        std::cout << "Visible: " << ((isVisible) ? "True " : "False ") << "      Lock Transform: " << ((lockTransform) ? "True\n" : "False\n");
        system("cls");*/

        Print::YellowLine("Transform: ");

        // For Position
        Print::Cyan("Position:   X = "); 
        std::cout << x;
        Print::Cyan("     Y = ");
        std::cout << y << std::endl;

        // For Scale
        Print::Green("Scale:      X = ");
        std::cout << w;
        Print::Green("     Y = ");
        std::cout << h << std::endl;

        
        // For Position Of BoxCollider
        Print::MagentaLine("For BoxCollider: ");
        Print::Magenta("Scale:      X = ");
        std::cout << BoxCollider.x;
        Print::Magenta("     Y = ");
        std::cout << BoxCollider.y << std::endl;

        // For Scale Of BoxCollider
        Print::Magenta("Scale:      X = ");
        std::cout << BoxCollider.w;
        Print::Magenta("     Y = ");
        std::cout << BoxCollider.h << std::endl;



        // Others
        Print::Magenta("Visible: ");
        std::cout << ((isVisible) ? "True " : "False ");
        Print::Magenta("      Lock Transform: ");
        std::cout << ((lockTransform) ? "True\n" : "False\n");
        system("cls");
    }

    void UpdateCollider()
    {
        BoxCollider.x = x; 
        BoxCollider.y = y; 
    }
    void SetTag(std::string _tag)
    {
        tag = _tag;
        BoxCollider.tag = _tag;
    }
    bool Comparetag(std::string _tag)
    {
        if (tag == _tag and tag == BoxCollider.tag)
            return true;

        return false;
    }
};


// Class Representing A Font
class Font
{
    TTF_Font* font ;
public:
    

    Font()
    {
        font = nullptr;
    }

    Font(std::string _path, int _size)
    {
        font = TTF_OpenFont(_path.c_str(), _size);

        if (!font)
        {
            Error::PrintExit("<Error> Failed to load font: ", TTF_GetError());
            return;
        }
    }

    void Load(std::string _path, int _size)
    {
        TTF_CloseFont(font); // Free Memory Incase Prevously Loaded

        font = TTF_OpenFont(_path.c_str(), _size);

        if (!font)
        {
            Error::PrintExit("<Error> Failed to load font: ", TTF_GetError());
            return;
        }
    }

    TTF_Font* GetSDLFont()
    {
        return font;
    }
    
    void ForceFree()
    {
        TTF_CloseFont(font);
    }

    ~Font() 
    {
        /*Debug::Warning("", "Stage 1");
        if (font != nullptr)
        {
            Debug::Warning("", "Stage 2");
            TTF_CloseFont(font);
            Debug::Warning("", "Stage 3");
        }
        
        Debug::Warning("","Stage 4");*/
    }
};

// Class Representing A Text
class Text {
public:
    int x, y;         // Position of the text
    int w, h;         // Width and height of the text
    std::string content; // The actual text content
    Color color;

    Text()
    {
        x = y = w = h = 0;
        content = "";
    }

    // Constructor
    Text(int x, int y, const std::string& content, Color color)
        : x(x), y(y), content(content) , color(color){
        // You may want to set width and height based on font metrics here
    }

    void Set(int _x, int _y, int _w, int _h, std::string _content, Color _color) 
    {
        x = _x;  y = _y;  w = _w; h = _h; content = _content; color = _color;
    }


    void SetPosition(int _x, int _y)
    {
        x = _x; y = _y;
    }

    void SetScale(int _w, int _h)
    {
        w = _w; h = _h;
    }

    void SetColor(Color& _color)
    {
        color = _color;
    }
 
};




