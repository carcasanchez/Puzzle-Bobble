#ifndef __LEVEL_1_H__
#define __LEVEL_1_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"


struct SDL_Texture;

class ModuleLevel_1 : public Module
{
public:
	ModuleLevel_1();
	~ModuleLevel_1();

	bool Start();
	update_status Update();
	bool CleanUp();
	//Uint32 time = 0;

public:
	unsigned int currentTime;
	SDL_Texture* graphics = nullptr;
	Mix_Music* level_music = nullptr;
	SDL_Rect level1;

};


#endif //__LEVEL_1_H__

