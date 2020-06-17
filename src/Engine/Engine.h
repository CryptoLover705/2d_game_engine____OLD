#pragma once
#include <string>
#include <stdio.h>

#include "Level.h"
#include "RendererBase.h"
#include "SoundManager.h"

#define FPSCALCULATION_LENGTH 50

#include "Timer.h"

// Struct to hold the desired size of the window, e.t.c.
struct GameProperties
{
	std::string Name;
	int Height;
	int Width;
};




// Struct to hold the boolean values
struct States
{
	bool Quit;
	bool Paused;
};

class Engine
{

public:
	virtual ~Engine();

	// Component Variables
	RendererBase* Renderer;
	SoundManager* SoundController;
	// Base Functions
	virtual void Initialize(GameProperties props);
	void BaseEventHandler(SDL_Event& e);

	// Events
	virtual void Precache();
	virtual void Start();
	virtual void GameLoop();
	virtual void Tick();
	virtual void EventHandler(SDL_Event& e);
	virtual void Render();
	virtual void Cleanup();
	virtual void DefaultProperties();

	// Functions
	virtual void LaunchMessage();

	// Data
	static States State;
	static GameProperties Properties;
	static std::string BasePath;

	// Game
	Level* CurrentLevel;


public:
	void FPSInitialize();
	void FPSThink();
protected:
	uint32_t FrameCount;
	uint32_t FrameTimes[FPSCALCULATION_LENGTH];
	uint32_t FrameTimeLast;
	static float FPS;
};
