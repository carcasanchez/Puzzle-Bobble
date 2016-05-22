#ifndef _UserInerface_H__
#define _UserInerface_H__

#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface();
	~ModuleUserInterface();

	bool Start();
	update_status Update();
	bool CleanUp();
	void WinLose();
	void LoseWin();


public:
	SDL_Texture* graphics_UI = nullptr;
	SDL_Rect win;
	SDL_Rect lose;
	Uint32 check_time = 0;
};


#endif