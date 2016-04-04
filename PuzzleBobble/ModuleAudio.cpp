#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

bool ModuleAudio::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = MIX_INIT_OGG;
	int init = (flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Audio lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}