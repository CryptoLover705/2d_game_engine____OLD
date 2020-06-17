/*
 * RendererOpenGL.cpp
 *
 *  Created on: 7 Mar 2014
 *      Author: Khalid
 */

///TODO: Make remove vsync from this.

#include "RendererOpenGL.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "SDL2/SDL_image.h"
#include "SDL2/SDL_opengl.h"

#include "Engine.h"

void RendererOpenGL::Initialize()
{
	Super::Initialize();
	//Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

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

	GameWindow = SDL_CreateWindow(Engine::Properties.Name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Engine::Properties.Width, Engine::Properties.Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(GameWindow == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); return;
	}

	UtilityRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(UtilityRenderer == nullptr)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	GLContext = SDL_GL_CreateContext(GameWindow);
	if(GLContext == NULL)
	{
		printf("OpenGL context creation failed!"); return;
	}

	if(SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString( error )); return;
	}

	GLenum state = glewInit();
	if(state != GLEW_OK)
	{
		printf("Error initializing OpenGL GLEW!\n"); return;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, Engine::Properties.Width, Engine::Properties.Height, 0.0, -1.0, 1.0);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}


void RendererOpenGL::RenderPresent()
{
	SDL_GL_SwapWindow(GameWindow);
}

void RendererOpenGL::RenderClear()
{
	glClearColor(1.f, 1.f, 1.f, 1.f); // Set Black Background
	glClear(GL_COLOR_BUFFER_BIT); //Clear color buffer
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();	// Reset current matrix
	glOrtho(0.0, Engine::Properties.Width, 0.0, Engine::Properties.Height, -1.0, 1.0);
}

void RendererOpenGL::Cleanup()
{
	SDL_GL_DeleteContext(GLContext);
	for(auto iter = GLTextureRepository.begin(); iter != GLTextureRepository.end(); iter++)
	{
		if(glIsTexture(iter->second->Data))
		{
			glDeleteTextures(1, &iter->second->Data);
		}
		delete iter->second;
		iter->second = nullptr;
	}
	SDL_DestroyRenderer(UtilityRenderer);
	SDL_DestroyWindow(GameWindow);
	printf("Renderer Destroyed");
	IMG_Quit();
	TTF_Quit();
	Super::Cleanup();
}

void RendererOpenGL::RenderDrawRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color)
{
	Vector2 localposition = WorldToLocalVector(worldposition);

	glLoadIdentity();
	glOrtho(0.0, Engine::Properties.Width, Engine::Properties.Height, 0.0, -1.0, 1.0);

	glTranslatef(localposition.x, localposition.y, 0.0f);

	glLineWidth(1.5);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_LINES);
		glVertex2d(			  0, 			  0);
		glVertex2d(dimensions.x,			  0);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(			  0,   dimensions.y);
		glVertex2d(dimensions.x,   dimensions.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(			  0, 			  0);
		glVertex2d(			  0,   dimensions.y);
	glEnd();
	glBegin(GL_LINES);
		glVertex2d(dimensions.x,              0);
		glVertex2d(dimensions.x,   dimensions.y);
	glEnd();
}

void RendererOpenGL::RenderFillRect(Vector2 worldposition, Vector2 dimensions, SDL_Color color)
{
	Vector2 localposition = WorldToLocalVector(worldposition);
	glLoadIdentity();
	glOrtho(0.0, Engine::Properties.Width, Engine::Properties.Height, 0.0, -1.0, 1.0);
	glTranslatef(localposition.x, localposition.y, 0.0f);
	glColor3ub(color.r, color.g, color.b);
	glBegin(GL_QUADS);
		glVertex2d(0, dimensions.y);
		glVertex2d(dimensions.x, dimensions.y);
		glVertex2d(dimensions.x, 0);
		glVertex2d(0, 0);
	glEnd();
}


int RendererOpenGL::PrecacheTexture(const std::string& name, const std::string& path)
{
	SDL_Surface* surface = IMG_Load((Engine::BasePath+path).c_str());
	if (surface == nullptr)
	{
		printf("Texture precache Fail: %s -> %s", name.c_str(), SDL_GetError());
		return PRECACHEFAIL_FAILTOLOAD;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int Mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4)
	{
		Mode = GL_RGBA;
	}


	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    GLTextureRepository[name] = new GLTextureWrapper(texture);
	GLTextureRepository[name]->Extras["Path"] = path;
	GLTextureRepository[name]->Extrai["Width"] = surface->w;
	GLTextureRepository[name]->Extrai["Height"] = surface->h;
	TexSizeRepository[name] = Vector2(surface->w, surface->h);
	SDL_FreeSurface(surface);
	printf("Precached Texture: %s\n", name.c_str());

	return PRECACHE_SUCCESS;
	//ATTN: GET THIS WORKING
}

bool RendererOpenGL::TextureExists(const std::string& Texture)
{
	return (GLTextureRepository[Texture] != nullptr);
}

void RendererOpenGL::RenderImage(const char* textureID, Vector2 worldposition, double scale, double rotation, SDL_RendererFlip flip)
{
	Vector2 localposition = WorldToLocalVector(worldposition);

	std::string ID = std::string(textureID);
	int width = GLTextureRepository[ID]->Extrai["Width"]*scale;
	int height = GLTextureRepository[ID]->Extrai["Height"]*scale;
	float hwidth = width/2;
	float hheight = height/2;

	glLoadIdentity();
	glOrtho(0.0, Engine::Properties.Width, Engine::Properties.Height, 0.0, -1.0, 1.0);

	glTranslatef(localposition.x+hwidth, localposition.y+hheight, 0.0f);
	glRotatef(rotation, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, GLTextureRepository[ID]->Data);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Render textured quad
	glBegin(GL_QUADS);
		glTexCoord2i(    0,    0); glVertex2f(-hwidth,-hheight);
		glTexCoord2i(	 1,    0); glVertex2f(hwidth,-hheight);
		glTexCoord2i(	 1,    1); glVertex2f(hwidth, hheight);
		glTexCoord2i(    0,    1); glVertex2f(-hwidth, hheight);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void RendererOpenGL::RenderImage(const char* textureID, Vector2 worldposition)
{
	this->RenderImage(textureID, worldposition, 1, 0, SDL_FLIP_NONE);
}

int RendererOpenGL::PrecacheFont(const std::string& name, const std::string& path, int fontsize)
{
	TTF_Font *font = TTF_OpenFont((Engine::BasePath+path).c_str(), fontsize);
	if(font == nullptr)
	{
		printf("Font precache fail: %s -> %s\n", name.c_str(), SDL_GetError());
		return PRECACHEFAIL_FAILTOLOAD;
	}

	GLFontRepository[name] = new GLFontWrapper(font);
	GLFontRepository[name]->Extras["Path"] = path;
	GLFontRepository[name]->Extrai["Size"] = fontsize;

	printf("Precached Font: %s\n", name.c_str());
	return PRECACHE_SUCCESS;
}

void RendererOpenGL::RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, double rotation, SDL_RendererFlip flip, SDL_Color color)
{
	std::string strID = std::string(fontID);
	if(GLFontRepository.count(strID) > 0
	&& GLFontRepository[strID]->Data == nullptr)
	{
		printf("Font render attempt does not exist! -> %s\n", fontID);
		system("PAUSE");
		return;
	}

	SDL_Surface *surface = TTF_RenderText_Blended(GLFontRepository[strID]->Data, message.c_str(), color);
	if (surface == nullptr)
	{
		printf("Font surface render fail: %s -> %s\n", fontID, SDL_GetError());
		system("PAUSE");
		return;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int Mode = GL_RGB;
	if(surface->format->BytesPerPixel == 4)
	{
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	Vector2 localposition = WorldToLocalVector(worldposition);
	int width = surface->w;
	int height = surface->h;
	float hwidth = width/2;
	float hheight = height/2;

	glLoadIdentity();
	glOrtho(0.0, Engine::Properties.Width, Engine::Properties.Height, 0.0, -1.0, 1.0);

	glTranslatef(localposition.x+hwidth, localposition.y+hheight, 0.0f);
	glRotatef(rotation, 0, 0, 1);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, texture);
	//Render textured quad
	glBegin(GL_QUADS);
		glTexCoord2i(    0,    0); glVertex2f(-hwidth,-hheight);
		glTexCoord2i(	 1,    0); glVertex2f(hwidth,-hheight);
		glTexCoord2i(	 1,    1); glVertex2f(hwidth, hheight);
		glTexCoord2i(    0,    1); glVertex2f(-hwidth, hheight);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_FreeSurface(surface);

}

void RendererOpenGL::RenderFont(const std::string& message, const char* fontID, Vector2 worldposition, SDL_Color color)
{
	this->RenderFont(message, fontID, worldposition, 0, SDL_RendererFlip::SDL_FLIP_NONE, color);
}
