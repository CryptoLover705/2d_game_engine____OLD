/*
 * ResourceWrapper.h
 * Purpose: SDL structures cannot be created/deleted easily and dynamically,
 * why not make a wrapper class to deal with this?
 */
#pragma once
#include "SDL2/SDL.h"
#include <map>

// For readability purposes. Nasty hack!
#define CreateFakeWrapper(NEWNAME, GENERICNAME) typedef GENERICNAME NEWNAME;

template<class T>
class ResourceWrapper
{
public:
	ResourceWrapper(T in)
	{
		Data = in;
	};
	std::map<std::string, float> Extraf;
	std::map<std::string, int> Extrai;
	std::map<std::string, double> Extrad;
	std::map<std::string, long> Extral;
	std::map<std::string, std::string> Extras;
	T Data;
};

// Fake Wrappers

//CreateFakeWrapper(TextureWrapper, ResourceWrapper<SDL_Surface*>);
//CreateFakeWrapper(SoundWrapper, ResourceWrapper<void*>);

/* Old Method:
#define CreateFakeWrapper(NAME, WRAPPED) class NAME{ public: WRAPPED Data; public: NAME(WRAPPED in){ Data = in; }; };
CreateFakeWrapper(SurfaceWrapper, SDL_Surface*);
CreateFakeWrapper(TextureWrapper, SDL_Texture*);
CreateFakeWrapper(SoundWrapper, void*);
*/
