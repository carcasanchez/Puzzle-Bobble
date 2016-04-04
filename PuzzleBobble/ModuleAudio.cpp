#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio() : Module(){}

ModuleAudio::~ModuleAudio(){}


bool ModuleAudio::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// Initialize the audio library 
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 1024);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Audio lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	music = Mix_LoadMUS("music.ogg");

	if (Mix_PlayMusic(music, -1) == -1) 
	{
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
		// well, there's no music, but most games don't break without music...
	}

	return ret;
}


bool ModuleAudio::CleanUp()
{
	LOG("Freeing audio and and music library");

	Mix_FreeMusic(music);
	Mix_FreeChunk(effects);

	Mix_Quit();// Close the audio library
	
	return true;
}
