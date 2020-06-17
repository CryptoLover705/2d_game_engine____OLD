#pragma once
#include "Entity.h"

class Sprite : public Entity
{
public:
	virtual void Initialize() override;
	virtual void Render() override;
	virtual bool IsColliding(Entity* collider) override;
	virtual bool SDLCollision(Entity* collider);
	virtual void GenerateTexture();
	virtual void DefaultProperties() override;

	std::string TexturePath;
    std::string Texture;
	double scale;
	double rotation;
	SDL_RendererFlip flip;

private:
	typedef Entity Super;
};
