#pragma once

#include <map>

#include "SDL2/SDL_mixer.h"

#include "ResourceWrapper.h"

CreateFakeWrapper(SDLMusicWrapper, ResourceWrapper<Mix_Music*>);
CreateFakeWrapper(SDLSoundWrapper, ResourceWrapper<Mix_Chunk*>);
class SoundManager
{
public:
	SoundManager();
	virtual ~SoundManager();
	virtual void PrecacheSound(const std::string& name, const std::string& path);
	virtual void PlaySound(const std::string& name, int channel, int loops);

	virtual void PrecacheMusic(const std::string& name, const std::string& path);
	virtual void PlayMusic(const std::string& name);
	virtual bool IsMusicPlaying();
	virtual void ResumeMusic();
	virtual void PauseMusic();
	virtual void StopMusic();

protected:
	std::map<std::string, SDLSoundWrapper*> SoundRepository;
	std::map<std::string, SDLMusicWrapper*> MusicRepository;
};
