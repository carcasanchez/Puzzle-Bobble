#ifndef __CONGRATS__
#define __CONGRATS__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleCongrats : public Module
{
public:
	ModuleCongrats();
	~ModuleCongrats();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	Mix_Music* level_music = nullptr;
	SDL_Rect congrats;

};


#endif //__LEVEL_1_H__