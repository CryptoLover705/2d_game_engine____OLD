#include "RendererSDL.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Engine.h"

void RendererSDL::Initialize()
{
	Super::Initialize();

	RenderView = Vector2(0, 0);
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError() );
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() < 0)
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", SDL_GetError() );
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	GameWindow = SDL_CreateWindow(Engine::Properties.Name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Engine::Properties.Width, Engine::Properties.Height, SDL_WINDOW_SHOWN);
	if(GameWindow == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED);
	if(GameRenderer == nullptr)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
}


int RendererSDL::PrecacheTexture(const std::string& name, const std::string& path)
{
	SDL_Surface* surface = IMG_Load((Engine::BasePath+path).c_str());
	if (surface == nullptr)
	{
		printf("Texture precache Fail: %s -> %s", name.c_str(), SDL_GetError());
		return PRECACHEFAIL_FAILTOLOAD;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(GameRenderer, surface);
	if(texture == nullptr)
	{
		printf("Texture could not be created! SDL_Error: %s\n", SDL_GetError());
		return PRECACHEFAIL_CREATION;
	}

	int texWidth, texHeight;
	TextureRepository[name] = new SDLTextureWrapper(texture);
	SDL_QueryTexture(TextureRepository[name]->Data, NULL, NULL, &texWidth, &texHeight);
	TextureRepository[name]->Extras["Path"] = path;
	TextureRepository[name]->Extrai["Width"] = texWidth;
	TextureRepository[name]->Extrai["Height"] = texHeight;
	TexSizeRepository[name] = Vector2(texWidth, texHeight);
	SDL_FreeSurface(surface);
	printf("Precached Texture: %s\n", name.c_str());

	return PRECACHE_SUCCESS;
}

void RendererSDL::RenderImage(const char* textureID, Vector2 worldposition)
{
	this->RenderImage(textureID, worldposition, 1.0, 0, SDL_FLIP_NONE);
}

void RendererSDL::RenderImage(const char* textureID, Vector2 worldposition, double scale, double rotation, SDL_RendererFlip flip)
{
	std::string strID = std::string(textureID);
	Vector2 pos = WorldToLocalVector(worldposition);
	if(TextureRepository.count(strID) > 0
	&& TextureRepository[strID]->Data == nullptr)
	{
		printf("Texture render attempt does not exist! -> %s\n", textureID);
		return;
	}
	SDL_Rect TexDimensions = {pos.x, pos.y, (int)floor(TextureRepository[strID]->Extrai["Width"]*scale),
											(int)floor(TextureRepository[strID]->Extrai["Height"]*scale)};
	SDL_RenderCopyEx(GameRenderer, TextureRepository[strID]->Data, NULL, &TexDimensions, rotation, NULL, flip);
}

void RendererSDL::RenderDrawRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color)
{
	Vector2 pos = WorldToLocalVector(worldposition);
	SDL_Rect rect = {pos.x, pos.y, dimensions.x, dimensions.y};
	SDL_SetRenderDrawColor(GameRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(GameRenderer, &rect);
}

void RendererSDL::RenderFillRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color)
{
	Vector2 pos = WorldToLocalVector(worldposition);
	SDL_Rect rect = {pos.x, pos.y, dimensions.x, dimensions.y};
	SDL_SetRenderDrawColor(GameRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(GameRenderer, &rect);
}

void RendererSDL::RenderPresent()
{
	SDL_RenderPresent(GameRenderer);
}

void RendererSDL::RenderClear()
{
	SDL_SetRenderDrawColor(GameRenderer, 255, 255, 255, 255);
	SDL_RenderClear(GameRenderer);
}
void RendererSDL::Cleanup()
{
	for(auto iter = FontRepository.begin(); iter != FontRepository.end(); iter++)
	{
		TTF_CloseFont(iter->second->Data);
		iter->second->Data = nullptr;
		delete iter->second;
		iter->second = nullptr;
	}

	for(auto iter = TextureRepository.begin(); iter != TextureRepository.end(); iter++)
	{
		SDL_DestroyTexture(iter->second->Data);
		iter->second->Data = nullptr;
		delete iter->second;
		iter->second = nullptr;
	}
	SDL_DestroyRenderer(GameRenderer);
	SDL_DestroyWindow(GameWindow);
	IMG_Quit();
	TTF_Quit();
	Super::Cleanup();
}



bool RendererSDL::TextureExists(const std::string& Texture)
{
	return (TextureRepository[Texture] != nullptr);
}

// SDL_ttf
int RendererSDL::PrecacheFont(const std::string& name, const std::string& path, int fontsize)
{
	TTF_Font *font = TTF_OpenFont((Engine::BasePath+path).c_str(), fontsize);
	if(font == nullptr)
	{
		printf("Font precache fail: %s -> %s", name.c_str(), SDL_GetError());
		return PRECACHEFAIL_FAILTOLOAD;
	}

	FontRepository[name] = new SDLFontWrapper(font);
	FontRepository[name]->Extras["Path"] = path;
	FontRepository[name]->Extrai["Size"] = fontsize;

	printf("Precached Font: %s\n", name.c_str());
	return PRECACHE_SUCCESS;
}

void RendererSDL::RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, double rotation, SDL_RendererFlip flip, SDL_Color color)
{
	std::string strID = std::string(fontID);
	Vector2 pos = WorldToLocalVector(worldposition);

	if(FontRepository.count(strID) > 0
	&& FontRepository[strID]->Data == nullptr)
	{
		printf("Font render attempt does not exist! -> %s\n", fontID);
		return;
	}

	SDL_Surface *surf = TTF_RenderText_Blended(FontRepository[strID]->Data, message.c_str(), color);
	if (surf == nullptr)
	{
		printf("Font surface render fail: %s -> %s", fontID, SDL_GetError());
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(GameRenderer, surf);
	if (texture == nullptr)
	{
		printf("Font texture from surface render fail: %s -> %s", fontID, SDL_GetError());
		system("PAUSE");
		exit(EXIT_FAILURE);
	}


	int texWidth, texHeight;
	SDL_QueryTexture(texture, NULL, NULL, &texWidth, &texHeight);

	SDL_Rect TexDimensions = {pos.x, pos.y, texWidth, texHeight};
	SDL_RenderCopyEx(GameRenderer, texture, NULL, &TexDimensions, rotation, NULL, flip);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);

}

void RendererSDL::RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, SDL_Color color)
{
	this->RenderFont(message, fontID, worldposition, 0, SDL_RendererFlip::SDL_FLIP_NONE, color);
}
