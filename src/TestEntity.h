#pragma once

#include "Engine/Entity.h"
#include "Engine/LinkedList.h"

class TestEntity : public Entity
{
public:
	void Render() override;
	void Input() override;
	void Tick(float DeltaTime) override;

	void DefaultProperties() override;
	Vector2f velocity;
private:
	typedef Entity Super;
};
