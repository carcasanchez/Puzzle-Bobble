#ifndef __STARTSCREEN_H__
#define __STARTSCREEN_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct Mix_Music;

class ModuleStartScreen : public Module
{
public:

	~ModuleStartScreen();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	Mix_Music* level_music = nullptr;

};


#endif
