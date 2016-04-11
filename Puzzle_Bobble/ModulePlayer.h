#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation1 = nullptr;
	Animation* current_animation2 = nullptr;
	Animation idle_left;
	Animation idle_right;
	Animation left;
	Animation right;
	Animation bobShot; 

	iPoint position;


};

#endif