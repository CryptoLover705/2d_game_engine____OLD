#pragma once
#include "Engine/Sprite.h"

class Player : public Sprite
{
public:
	void Spawn() override;
	void Initialize() override;
	void Tick(float DeltaTime) override;
	void Input() override;
	void Render() override;
	void OnCollision();
	void DefaultProperties() override;
	Vector2f velocity;
private:
	typedef Sprite Super;
};
