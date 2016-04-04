#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )


#include "Module.h"
#include "Globals.h"

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();
	Mix_Music *music;
	Mix_Chunk *effects;

	bool Init();
	bool CleanUp();

};



#endif //__ModuleAudio_H__