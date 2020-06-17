#include "Entity.h"

Entity::~Entity(){}


int Entity::IDCount = 0;
void Entity::Initialize(){}
void Entity::Spawn(){}

bool Entity::IsColliding(Entity* collider){ return false; }

void Entity::EventHandler(SDL_Event &e){}
void Entity::Tick(float DeltaTime){}
void Entity::Input(){}
void Entity::Render(){}
void Entity::Cleanup(){}

void Entity::DrawCollisions(){}

void Entity::Delete()
{
	ToDelete = true;
}

void Entity::DefaultProperties()
{
	bDrawCollisions=false;
}
