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

public:
	SDL_Texture* graphics = nullptr;
	Mix_Music* level_music = nullptr;

};


#endif //__LEVEL_1_H__

