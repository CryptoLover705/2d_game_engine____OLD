/*
 * RendererDirect3D.h
 * Purpose: For some reason D3D is still being used.
 *  Created on: 7 Mar 2014
 *      Author: Khalid
 */
#pragma once
#ifdef DX_SUPPORTED

#include "RendererBase.h"

//#ifdef __WIN64__ && __WIN32__

#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>

class RendererDirect3D: public RendererBase
{
public:
	void Initialize() override;
	void PrecacheTexture(const std::string& name, const std::string& path) override;
	void RenderImage(const char* textureID, Vector2 position) override;
	void RenderImage(const char* textureID, Vector2 position, double scale) override;
	void RenderDrawRect(Vector2 position, Vector2 dimensions, SDL_Color color) override;
	void RenderFillRect(Vector2 position, Vector2 dimensions, SDL_Color color) override;
	void RenderPresent() override;
	void RenderClear() override;
	void Cleanup() override;
private:
	typedef RendererBase Super;
	SDL_Window* GameWindow;
	LPDIRECT3D9  Direct3D;
	LPDIRECT3DDEVICE9 Direct3DDevice;

};

#endif // DX_SUPPORTED
