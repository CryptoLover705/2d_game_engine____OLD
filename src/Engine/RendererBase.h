#pragma once
#include <string>
#include <map>

#include "SDL2/SDL.h"
#include "Vector2.h"

enum PrecacheStatus
{
	PRECACHE_SUCCESS = 1,
	PRECACHEFAIL_UNKNOWN = 0,
	PRECACHEFAIL_FAILTOLOAD = -1,
	PRECACHEFAIL_CREATION = -2
};

class RendererBase
{
public:
	virtual void Initialize();
	virtual void Cleanup();

	virtual int PrecacheTexture(const std::string& name, const std::string& path);
	virtual void RenderImage(const char* textureID, Vector2 worldposition);
	virtual void RenderImage(const char* textureID, Vector2 worldposition, double scale, double rotation, SDL_RendererFlip flip);
	virtual void RenderDrawRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color);
	virtual void RenderFillRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color);
	virtual void RenderPresent();
	virtual void RenderClear();
	virtual bool TextureExists(const std::string& Texture);

	// Font Stuff
	virtual int PrecacheFont(const std::string& name, const std::string& path, int fontsize);
	virtual void RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, SDL_Color color);
	virtual void RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, double rotation, SDL_RendererFlip flip, SDL_Color color);

	virtual void SetRenderView(int x, int y);
	virtual void SetRenderView(Vector2 pos);
	virtual Vector2 WorldToLocalVector(Vector2 in);
	virtual Vector2 LocalToWorldVector(Vector2 in);

	virtual ~RendererBase();

	std::map<std::string, Vector2> TexSizeRepository;
	Vector2 RenderView;
};
