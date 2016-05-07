#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio() : Module(){}

ModuleAudio::~ModuleAudio(){}


bool ModuleAudio::Init()
{
	LOG("Init Audio Library\n");
	bool ret = true;

	// Initialize the audio library 
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Audio lib. Mix_Init: %s\n", Mix_GetError());
		ret = false;
	}
	return ret;
}


bool ModuleAudio::CleanUp()
{
	LOG("Freeing audio and and music library\n");

	for (unsigned int i = 0; i < last_audio; i++)
	Mix_FreeMusic(audio[i]);

	for (unsigned int i = 0; i < last_effect; i++)
		Mix_FreeChunk(effects[i]);

	Mix_CloseAudio();
	Mix_Quit();// Close the audio library

	return true;
}

Mix_Music* const ModuleAudio:: Load_music(const char *path)
{
	Mix_Music* music = Mix_LoadMUS(path);
	audio[last_audio++] = music;

	LOG("Loading Music\n");

	return music;
}

Mix_Chunk* const ModuleAudio::Load_effects(const char *path)
{
	Mix_Chunk* effect = Mix_LoadWAV(path);
	effects[last_effect++] = effect;

	LOG("Loading Music\n");

	return effect;
}

