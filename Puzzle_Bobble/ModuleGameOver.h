#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleAudio.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	Mix_Music* level_music = nullptr;
	SDL_Rect gameover;

};


#endif //__GAMEOVER_H__