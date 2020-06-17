///TODO: Complete the Direct3D renderer.

#ifdef DX_SUPPORTED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "Engine.h"
#include "RendererDirect3D.h"


void RendererDirect3D::Initialize()
{
	GameWindow = SDL_CreateWindow(Engine::Properties.Name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Engine::Properties.Width, Engine::Properties.Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(GameWindow == nullptr)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError()); return;
	}

	Direct3D = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS Direct3DParams;    // create a struct to hold various device information

    ZeroMemory(&Direct3DParams, sizeof(Direct3DParams));    // clear out the struct for use
    Direct3DParams.Windowed = false;
	Direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Direct3DParams.EnableAutoDepthStencil = true;
	Direct3DParams.AutoDepthStencilFormat = D3DFMT_D16;
	Direct3DParams.hDeviceWindow = GetActiveWindow();
	Direct3DParams.BackBufferWidth = 800;
	Direct3DParams.BackBufferHeight = 600;
	Direct3DParams.BackBufferFormat = D3DFMT_R5G6B5;
	Direct3DParams.MultiSampleType = D3DMULTISAMPLE_NONE;
    // create a device class using this information and information from the d3dpp stuct
    Direct3D->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      GetActiveWindow(),
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &Direct3DParams,
                      &Direct3DDevice);
}

void RendererDirect3D::PrecacheTexture(const std::string& name, const std::string& path)
{

}

void RendererDirect3D::RenderImage(const char* textureID, Vector2 position)
{

}

void RendererDirect3D::RenderImage(const char* textureID, Vector2 position, double scale)
{

}

void RendererDirect3D::RenderDrawRect(Vector2 position, Vector2 dimensions, SDL_Color color)
{

}

void RendererDirect3D::RenderFillRect(Vector2 position, Vector2 dimensions, SDL_Color color)
{

}

void RendererDirect3D::RenderPresent()
{
	//Direct3DDevice->EndScene();
	Direct3DDevice->Present(NULL, NULL, NULL, NULL);
}

void RendererDirect3D::RenderClear()
{
	Direct3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
	//Direct3DDevice->BeginScene();
}

void RendererDirect3D::Cleanup()
{
	Direct3DDevice->Release();
	Direct3D->Release();
}

#endif // DX_SUPPORTED
