#ifndef __STARTSCREEN_H__
#define __STARTSCREEN_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStartScreen : public Module
{
public:
	ModuleStartScreen();
	~ModuleStartScreen();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	
};


#endif
