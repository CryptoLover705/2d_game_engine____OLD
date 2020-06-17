#include "Level.h"
#include <sstream>
#include <stdio.h>
#include <algorithm>



Level::~Level(){}

void Level::Initialize(RendererBase* renderer, SoundManager* soundcontroller)
{
	Renderer = renderer;
	SoundController = soundcontroller;
	LevelSpeed = 1.f;
	TickTimer = Timer();
	TickTimer.Start();
}

void Level::EventHandler(SDL_Event* e)
{
	EntityRepository.iterate([&] (LinkedNode<Entity*>* node, Entity* ent)
	{
		if(ent != nullptr)
		{
			ent->EventHandler(*e);
		}
	});
}

void Level::Render()
{
	// Detect Tick:
	Uint32 PreT = TickTimer.GetTicks();
	const Uint32 TickLength = 10*LevelSpeed;
	if(PreT > TickLength)
	{
		float deltaTime = 1+((PreT-TickLength)/TickLength);
		Tick(deltaTime);
		TickTimer.Reset();
	}


	EntityRepository.iterate([&] (LinkedNode<Entity*>* node, Entity* ent)
	{
		if(ent != nullptr)
		{
			ent->Input();

			if(ent->Renderer != nullptr)
			{
				ent->Render();
			}
			if(ent->ToDelete)
			{
				printf("Deleted: %s N: %i\n", ent->ID.c_str(), ent->IDCount);
				delete ent;
				node->x = nullptr;
				EntityRepository.remove(node);
				node = nullptr;
				// Horrible function based iteration system needs to be fixed.
				// This actually means continue, if this was a loop.
				return;
			}
		}
	});
}

Entity* Level::Spawn(Entity* entity)
{
	 return this->Spawn(entity, Vector2(0, 0));
}

Entity* Level::Spawn(Entity* entity, Vector2 pos)
{
	std::stringstream ss;
	ss << "Entity" << Entity::IDCount;
	return this->Spawn(ss.str(), entity, pos);
}

Entity* Level::Spawn(std::string ID, Entity* s, Vector2 pos)
{
	printf("Spawned: %s\n", ID.c_str());

	s->Renderer = Renderer;
	s->SoundController = SoundController;

	Entity::IDCount++;
	s->ToDelete = false;
	s->position.x = pos.x;
	s->position.y = pos.y;
	s->ID = ID;

	EntityRepository.push_front(s);
	s->DefaultProperties();
	s->Initialize();
	s->Spawn();
	return s;
}

void Level::Tick(float DeltaTime)
{
	EntityRepository.iterate([&] (LinkedNode<Entity*>* node, Entity* ent)
	{
		if(ent != nullptr)
		{
			ent->Tick(DeltaTime);
		}
	});
}

template<typename LoopF>
void Level::LoopEntsByID(std::string ID, LoopF &loopFunction)
{
	EntityRepository.iterate([&] (LinkedNode<Entity*>* node, Entity* ent)
	{
		// TODO: Fix this method of iteration.
		if(ent != nullptr)
		{
			std::string str(ent->ID); std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			std::string sub(ID); std::transform(sub.begin(), sub.end(), sub.begin(), ::tolower);
			if(str.find(sub) == std::string::npos)
			{
				loopFunction(*ent);
			}
		}
	});
}

void Level::Cleanup()
{
	EntityRepository.iterate([&] (LinkedNode<Entity*>* node, Entity* ent)
	{
		delete ent;
		EntityRepository.remove(node);
		node = nullptr;
	});
}
