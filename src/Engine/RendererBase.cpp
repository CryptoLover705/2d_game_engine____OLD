#include "RendererBase.h"
#include "Engine.h"
#include <math.h>

void RendererBase::Initialize(){}
int RendererBase::PrecacheTexture(const std::string& name, const std::string& path){return 0;}
void RendererBase::RenderImage(const char* textureID, Vector2 worldposition){}
void RendererBase::RenderImage(const char* textureID, Vector2 worldposition, double scale, double rotation, SDL_RendererFlip flip){}
void RendererBase::RenderDrawRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color){}
void RendererBase::RenderFillRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color){}
void RendererBase::RenderPresent(){}
void RendererBase::RenderClear(){}
void RendererBase::Cleanup(){}
RendererBase::~RendererBase(){}

///TODO: Make Vector2f the standard for positions, (perhaps recreate the functions Vector2f parameters) CONSISTENCY IS IMPORTANT

void RendererBase::SetRenderView(int x, int y)
{
	this->RenderView.x = -x;
	this->RenderView.y = -y;
}

void RendererBase::SetRenderView(Vector2 pos)
{
	this->RenderView.x = -pos.x;
	this->RenderView.y = -pos.y;
}

bool RendererBase::TextureExists(const std::string& Texture){ return false; }

// Font Stuff
int RendererBase::PrecacheFont(const std::string& name, const std::string& path, int fontsize){return 0;}
void RendererBase::RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, SDL_Color color){}
void RendererBase::RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, double rotation, SDL_RendererFlip flip, SDL_Color color){}


// Vector Translation
Vector2 RendererBase::WorldToLocalVector(Vector2 in)
{
	//TODO: Improve this
	// Displace coordinates.
	in.x += floor(RenderView.x+(Engine::Properties.Width/2));
	in.y += floor(RenderView.y+(Engine::Properties.Height/2));
	return in;
}

Vector2 RendererBase::LocalToWorldVector(Vector2 in)
{
	//TODO: Improve this
	// Displace coordinates.
	in.x -= floor(RenderView.x+(Engine::Properties.Width/2));
	in.y -= floor(RenderView.y+(Engine::Properties.Height/2));
	return in;
}
