#include "AnimatedSprite.h"

#include <sstream>

///TODO: Finish creating this.

void AnimatedSprite::Initialize()
{
	Super::Initialize();
}

void AnimatedSprite::PrecacheAnimation(std::string name, std::string path, std::string extension, int length)
{
	for(int i=0; i<length; i++)
	{
		std::ostringstream sPath;
		std::ostringstream sName;
		sPath << path << i << extension;
		sName << "Animation" << name << i;
		Renderer->PrecacheTexture(sName.str(), sPath.str());
	}
}

void AnimatedSprite::RenderAnimation(std::string name, float AnimationSpeed)
{
	Renderer->RenderImage(name.c_str(), position, scale, rotation, flip);
}
