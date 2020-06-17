#pragma once

#include "Vector2.h"
#include "SDL2/SDL.h"

const int NUM_KEYS = SDL_Scancode::SDL_NUM_SCANCODES;
const int NUM_MOUSEBUTTONS = 256;


class Input
{
public:
	static const Uint8* keyState;

	static bool mouseInput[NUM_MOUSEBUTTONS];
	static bool downMouse[NUM_MOUSEBUTTONS];
	static bool upMouse[NUM_MOUSEBUTTONS];
	static Vector2 mousePosition;


	static bool GetKey(int keyCode);
	static bool GetKeyUp(int keyCode);
	static bool GetKeyDown(int keyCode);

	static bool GetMouse(int button);
	static bool GetMouseDown(int button);
	static bool GetMouseUp(int button);


	static void ShowCursor(bool value);
	static Vector2 GetMousePosition();


	static void EventHandler(SDL_Event *e);
	static void Update();
};

