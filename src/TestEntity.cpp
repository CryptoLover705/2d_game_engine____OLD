#include "TestEntity.h"

#include "Engine/Input.h"

#include <iostream>

void TestEntity::Render()
{
	SDL_Color c = {0, 255, 255};

	Super::Render();

	Renderer->RenderFillRect(position, dimensions, c);
	///TODO: Figure out why this text renders green.
	Renderer->RenderFont("I am a box", "ArialSmall", position.ToInteger()+Vector2(0, (int)dimensions.y), c);
}

void TestEntity::Tick(float DeltaTime)
{
	velocity = velocity * 0.8 * DeltaTime;


	Vector2 BackgroundDimensions = Renderer->TexSizeRepository["Background"];
	if(position.x <= 0)
	{
		Delete();
		velocity.x *= -1.0f * DeltaTime;
		if(velocity.x < 0)
			velocity.x = 1.5f;
	}
	else if(position.x >= BackgroundDimensions.x - dimensions.x)
	{
		velocity.x *= -1.0f * DeltaTime;
		if(velocity.x > 0)
			velocity.x = -1.5f;
	}
	if(position.y <= 0)
	{
		velocity.y *= -1.0f * DeltaTime;
		if(velocity.y < 0)
			velocity.y = 1.5f;
	}
	else if(position.y >= BackgroundDimensions.y - dimensions.y)
	{
		velocity.y *= -1.0f * DeltaTime;
		if(velocity.y > 0)
			velocity.y = -1.5f;
	}


	if(Input::GetKey(SDL_SCANCODE_UP))
	{
		velocity.y -= 5 * DeltaTime;
	}
	else if(Input::GetKey(SDL_SCANCODE_DOWN))
	{
		velocity.y += 5 * DeltaTime;
	}

	if(Input::GetKey(SDL_SCANCODE_LEFT))
	{
		velocity.x -= 5 * DeltaTime;
	}
	else if(Input::GetKey(SDL_SCANCODE_RIGHT))
	{
		velocity.x += 5 * DeltaTime;
	}

	position.x += velocity.x;
	position.y += velocity.y;
}

// TODO: Get rid of Input() perhaps? (Maybe make it do the same thing as Tick with deltatime).
void TestEntity::Input()
{
	Super::Input();
}

void TestEntity::DefaultProperties()
{
	dimensions = Vector2(100, 100);
}
