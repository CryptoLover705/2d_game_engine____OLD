#pragma once

#include "Engine/Engine.h"

class SpaceGame : public Engine
{
public:
	void Initialize(GameProperties props) override;

	// Events
	void Precache() override;
	void Start() override;
	void GameLoop() override;
	void Tick() override;
	void EventHandler(SDL_Event& e) override;
	void Render() override;
	void Cleanup() override;
	void DefaultProperties() override;
private:
	typedef Engine Super;
};

