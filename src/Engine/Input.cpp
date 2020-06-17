#include "Input.h"

bool Input::mouseInput[NUM_MOUSEBUTTONS];
bool Input::downMouse[NUM_MOUSEBUTTONS];
bool Input::upMouse[NUM_MOUSEBUTTONS];
const Uint8* Input::keyState = SDL_GetKeyboardState(NULL);

Vector2 Input::mousePosition = Vector2();

void Input::Update()
{
	for(int i = 0; i < NUM_MOUSEBUTTONS; i++)
	{
		downMouse[i] = false;
		upMouse[i] = false;
	}
}

void Input::EventHandler(SDL_Event *e)
{

	for(int i = 0; i < NUM_MOUSEBUTTONS; i++)
	{
		bool down = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(i);

		if(mouseInput[i] && !down)
		{
			upMouse[i] = true;
			mouseInput[i] = false;
		}

		if(down)
		{
			downMouse[i] = true;
			mouseInput[1] = true;
		}
	}


	switch(e->type)
	{
		case SDL_MOUSEMOTION:
			mousePosition.x = (float)e->motion.x;
			mousePosition.y = (float)e->motion.y;
			break;
	}
}

bool Input::GetKey(int keyCode)
{
	return keyState[keyCode];
}

bool Input::GetKeyDown(int keyCode)
{
	return NULL;
}

bool Input::GetKeyUp(int keyCode)
{
	return NULL;
}

bool Input::GetMouse(int button)
{
	return mouseInput[button];
}

bool Input::GetMouseDown(int button)
{
	return downMouse[button];
}

bool Input::GetMouseUp(int button)
{
	return upMouse[button];
}

Vector2 Input::GetMousePosition()
{
	return mousePosition;
}

void Input::ShowCursor(bool visible)
{
	visible ? SDL_ShowCursor(1) : SDL_ShowCursor(0);
}
