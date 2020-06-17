#pragma once
#include "RendererBase.h"
#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "ResourceWrapper.h"

CreateFakeWrapper(SDLTextureWrapper, ResourceWrapper<SDL_Texture*>);
CreateFakeWrapper(SDLFontWrapper, ResourceWrapper<TTF_Font*>);

// TODO: make SDL_RendererFlip and SDL_Colour my own type to avoid SDL.h inclusion in RendererBase?

class RendererSDL : public RendererBase
{
public:
	// Main rendering stuff
	void Initialize() override;
	void RenderPresent() override;
	void RenderClear() override;
	void Cleanup() override;

	// Basic Rendering
	void RenderDrawRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color) override;
	void RenderFillRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color) override;

	// Texture Stuff
	int PrecacheTexture(const std::string& name, const std::string& path) override;
	void RenderImage(const char* textureID, Vector2 worldposition) override;
	void RenderImage(const char* textureID, Vector2 worldposition, double scale, double rotation, SDL_RendererFlip flip) override;
	bool TextureExists(const std::string& Texture) override;

	// Font Stuff
	int PrecacheFont(const std::string& name, const std::string& path, int fontsize) override;
	void RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, SDL_Color color) override;
	void RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, double rotation, SDL_RendererFlip flip, SDL_Color color) override;

public:
	std::map<std::string, SDLTextureWrapper*> TextureRepository;
	std::map<std::string, SDLFontWrapper*> FontRepository;

private:
	typedef RendererBase Super;

public:
	SDL_Window* GameWindow;
	SDL_Renderer* GameRenderer;

};
