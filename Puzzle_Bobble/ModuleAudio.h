#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_AUDIO 20

#include "Module.h"
#include "Globals.h"

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();
	Mix_Music* audio[MAX_AUDIO];
	uint last_audio = 0;

	bool Init();
	bool CleanUp();
	Mix_Music* const Load(const char* path);
};



#endif //__ModuleAudio_H__