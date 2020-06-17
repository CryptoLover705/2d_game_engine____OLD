#include "Player.h"
#include <stdio.h>
#include <math.h>

#include "Engine/Input.h"
#include "Engine/Engine.h"

///TODO: Rotary collisions

void Player::Spawn()
{
}

void Player::Initialize()
{
	Super::Initialize();
}

void Player::Tick(float DeltaTime)
{
	velocity = velocity * 0.95 * DeltaTime;

	Vector2 BackgroundDimensions = Renderer->TexSizeRepository["Background"];
	if(position.x <= dimensions.x/2)
	{
		velocity.x *= -1.2f * DeltaTime;
		if(velocity.x < 0)
			velocity.x = 1.5f;
		OnCollision();
	}
	else if(position.x >= BackgroundDimensions.x - dimensions.x/2)
	{
		velocity.x *= -1.2f * DeltaTime;
		if(velocity.x > 0)
			velocity.x = -1.5f;
		OnCollision();
	}
	if(position.y <= dimensions.y/2)
	{
		velocity.y *= -1.2f * DeltaTime;
		if(velocity.y < 0)
			velocity.y = 1.5f;
		OnCollision();
	}
	else if(position.y >= BackgroundDimensions.y - dimensions.y/2)
	{
		velocity.y *= -1.2f * DeltaTime;
		if(velocity.y > 0)
			velocity.y = -1.5f;
		OnCollision();
	}

	float Acceleration = 0.5*DeltaTime;
	if(Input::GetKey(SDL_SCANCODE_W))
	{
		velocity.x += Acceleration*sin(rotation*M_PI/180);
		velocity.y -= Acceleration*cos(rotation*M_PI/180);

	}
	else if(Input::GetKey(SDL_SCANCODE_S))
	{
		velocity.x -= Acceleration*sin(rotation*M_PI/180);
		velocity.y += Acceleration*cos(rotation*M_PI/180);
	}
	if(Input::GetKey(SDL_SCANCODE_A))
	{
		rotation -= 3.25;
	}
	else if(Input::GetKey(SDL_SCANCODE_D))
	{
		rotation += 3.25;
	}

	position.x += velocity.x;
	position.y += velocity.y;
}

void Player::OnCollision()
{
	if(SoundController->IsMusicPlaying())
		SoundController->StopMusic();
	SoundController->PlaySound("Thump", -1, 0);
}

void Player::Input()
{
	Super::Input();
}

void Player::Render()
{
	Renderer->SetRenderView(position);

	Super::Render();

	///TODO: Sort out the position of this.
	Renderer->RenderFont("I am a man", "ArialSmall", position+Vector2f(-20, 70), {0, 0, 0});
}


void Player::DefaultProperties()
{
	Super::DefaultProperties();

	velocity = Vector2f(0, 0);




	Texture = "ToiletMan";
	TexturePath = "/res/ToiletMan.png";
	dimensions = Vector2f(40, 40);
	flip = SDL_FLIP_NONE;
	rotation = 0;
	scale = 0.25;
}
