#pragma once

#include "Vector2.h"
#include "RendererBase.h"
#include "SoundManager.h"

///TODO: Properly implement Entity:IDCount

class Entity
{
public:
	// Events
	virtual void Initialize();
	virtual void Spawn();
	virtual void EventHandler(SDL_Event &e);
	virtual void Render();
	virtual void Tick(float DeltaTime);
	virtual void Input();
	virtual void DefaultProperties();
	virtual void Cleanup();

	// Control
	std::string ID;
	static int IDCount;

	virtual ~Entity();

	Vector2f position;
	Vector2f dimensions;

	void Delete();
	bool ToDelete;

	virtual bool IsColliding(Entity* collider);

	// Pointers
	RendererBase* Renderer;
	SoundManager* SoundController;

	// Debug
	bool bDrawCollisions;
	void DrawCollisions();
};
