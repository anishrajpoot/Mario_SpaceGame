#pragma once

#include <SDL.h>
#include <iostream>
#include <fstream>

#include "Preferences.h"
#include "InputSystem.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "DataStructures.h"

#include "Utilities.h"
#include "DebugHelp.h"
#include "CollisionManager.h"




class Application
{
private:
	SDL_Window* m_window; // Window For Game
	Renderer* m_renderer;  // Renderer For Game
	SDL_Event m_window_event; // Manages Events Like Exit And Resize

	bool isRunning = true; // Set To True If Game Is Running

	const int frameRate = FRAMERATE; // Determines The Framerate Of Game
	const int frameDelay = 1000 / frameRate; // Time in milliseconds per frame
	Uint32 frameStart; // To store the start time of each frame

	
	SDL_Texture* playerTexture;  // Texture For Player Sprite
	Sprite player; // Player Sprite

	CollisionManager collisionManager; // Detects Collision Within Game

	
	

public:
	Application();
	~Application();

	void Run();
	void HandleEvents();

	void OnUpdate(double deltaTime);
	void OnStart();
	void Draw();
	bool Running();

};


