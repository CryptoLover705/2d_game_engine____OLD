#include "Sprite.h"
#include "RendererSDL.h"

#include <stdio.h>

bool BoxCollision(const SDL_Rect& A, const SDL_Rect& B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}


void Sprite::Initialize()
{
	GenerateTexture();
	Super::Initialize();
}

void Sprite::GenerateTexture()
{
	if(!Renderer->TextureExists(Texture)
	&& Texture != "NULL"
	&& TexturePath != "NULL")
	{
		Renderer->PrecacheTexture(Texture, TexturePath);
	}
}

void Sprite::Render()
{
	dimensions.x = Renderer->TexSizeRepository[Texture].x*scale;
	dimensions.y = Renderer->TexSizeRepository[Texture].y*scale;

	///TODO: Fix Vector Conversion
	Renderer->RenderImage(Texture.c_str(), position.ToInteger()-Vector2(dimensions/2), scale, rotation, flip);
	Super::Render();
}

// Very long collision function.
/// TODO: Shorten or Clean Collision Perhaps. Use an external handler?
bool Sprite::IsColliding(Entity* collider)
{
	if(Renderer != nullptr)
	{
		return SDLCollision(collider);
	}
	return false;
}

bool Sprite::SDLCollision(Entity* collider)
{
	/// TODO: Implement Box/Sphere AND per pixel collision detection.
	//RendererSDL* SDLRenderer = dynamic_cast<RendererSDL*>(Renderer);

	// Sprite/Sprite collision check (Per Pixel) YOLO!
	SDL_Rect a = {position.ToInteger().x,
				  position.ToInteger().y,
				  dimensions.ToInteger().x,
				  dimensions.ToInteger().y};

	SDL_Rect b = {collider->position.ToInteger().x,
				  collider->position.ToInteger().x,
				  collider->dimensions.ToInteger().x,
				  collider->dimensions.ToInteger().y};

	Sprite* spriteCollider = dynamic_cast<Sprite*>(collider);
	if(spriteCollider != nullptr)
	{
		// So.. The collider is a sprite!
		if(Renderer->TextureExists(Texture)
		&& Renderer->TextureExists(spriteCollider->Texture))
		{
			// Both have a valid texture! Cool! Time to collide!
			if(BoxCollision(a, b))
			{

				// An intersection has been found
				return true;
			}
		}
	}
	// Didn't collide.
	return false;
}

void Sprite::DefaultProperties()
{
	Super::DefaultProperties();
	Texture = "NULL";
	TexturePath = "NULL";
}
