#pragma once

#include "SDL2/SDL.h"

#include "LinkedList.h"
#include "Entity.h"
#include "SoundManager.h"
#include "Timer.h"

class Level
{
public:
	virtual ~Level();

	// Events
	virtual void Initialize(RendererBase* renderer, SoundManager* soundcontroller);
	virtual void Cleanup();
	virtual void EventHandler(SDL_Event* e);
	virtual void Render();
	virtual void Tick(float DeltaTime);

	// Data
	RendererBase* Renderer;
	SoundManager* SoundController;
	std::string LevelName;
	LinkedList<Entity*> EntityRepository;
	Timer TickTimer;

	// Functions

	// Utility Functions
	Entity* Spawn(std::string name, Entity* entity);
	Entity* Spawn(Entity* entity);
	Entity* Spawn(Entity* entity, Vector2 position);
	Entity* Spawn(std::string ID, Entity* entity, Vector2 position);

	template<typename LoopF>
	void LoopEntsByID(std::string ID, LoopF &loopFunction);

	float LevelSpeed;
};
