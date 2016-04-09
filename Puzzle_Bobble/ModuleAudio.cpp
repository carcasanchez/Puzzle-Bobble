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

	music[0] = Mix_LoadMUS("SinglePlayerMusic.ogg");

	LOG("Playing Music\n");


	if (Mix_PlayMusic(music[0], -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
	
	}
	return ret;
}


bool ModuleAudio::CleanUp()
{
	LOG("Freeing audio and and music library\n");

	for (int i = 0; i < NUM_MUSICS;i++)
	Mix_FreeMusic(music[i]);

	//Mix_FreeChunk(effects);
	Mix_CloseAudio();
	Mix_Quit();// Close the audio library

	return true;
}

