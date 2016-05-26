#ifndef __STARTSCREEN_H__
#define __STARTSCREEN_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;


class ModuleStartScreen : public Module
{
public:
	ModuleStartScreen();
	~ModuleStartScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	bool play = false;
	SDL_Texture* graphics = nullptr;
	SDL_Rect background;
	Mix_Music* level_music = nullptr;

};


#endif
