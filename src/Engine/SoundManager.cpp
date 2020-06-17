#include "SoundManager.h"
#include "Engine.h"

#include <stdlib.h>
#include <stdio.h>

///TODO: Implement an entire resource manager which encapsulated the soundmanager and renderer.
///TODO: MP3s with SDL Mixer MUST be of a bitrate of 256kbps and 44100Hz sample rate. (Fix this is possible?)

SoundManager::SoundManager()
{
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		system("PAUSE");
		exit(EXIT_SUCCESS);
	}
}

// Sound Stuff (Temporary)
void SoundManager::PrecacheSound(const std::string& name, const std::string& path)
{
	Mix_Chunk* ChunkyChunk = Mix_LoadWAV((Engine::BasePath+path).c_str());
	SoundRepository[name] = new SDLSoundWrapper(ChunkyChunk);
	SoundRepository[name]->Extras["Path"] = path;

}
void SoundManager::PrecacheMusic(const std::string& name, const std::string& path)
{
	Mix_Music* ChunkyChunk = Mix_LoadMUS((Engine::BasePath+path).c_str());

	MusicRepository[name] = new SDLMusicWrapper(ChunkyChunk);
	MusicRepository[name]->Extras["Path"] = path;
}

/// TODO: Add validation to PlaySound()
void SoundManager::PlaySound(const std::string& name, int channel, int loops)
{
	Mix_PlayChannel(channel, SoundRepository[name]->Data, loops);
}
void SoundManager::PlayMusic(const std::string& name)
{
	Mix_PlayMusic(MusicRepository[name]->Data, -1);
}
bool SoundManager::IsMusicPlaying()
{
	return !(bool)Mix_PausedMusic();
}
void SoundManager::ResumeMusic()
{
	Mix_ResumeMusic();
}
void SoundManager::PauseMusic()
{
	Mix_PauseMusic();
}
void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}

SoundManager::~SoundManager()
{
	for(auto iter = SoundRepository.begin(); iter != SoundRepository.end(); iter++)
	{
		Mix_FreeChunk(iter->second->Data);
		iter->second->Data = nullptr;
		delete iter->second;
		iter->second = nullptr;
	}
	for(auto iter = MusicRepository.begin(); iter != MusicRepository.end(); iter++)
	{
		Mix_FreeMusic(iter->second->Data);
		iter->second->Data = nullptr;
		delete iter->second;
		iter->second = nullptr;
	}
	Mix_Quit();
}
