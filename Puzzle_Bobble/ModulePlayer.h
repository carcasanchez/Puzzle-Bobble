#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_rect.h"

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
	Animation* current_animation_BaseLeft = nullptr;
	Animation idle_left;
	Animation idle_right;
	Animation right;
	Animation bobShot;
	Animation base_left;
	SDL_Rect arrow_src;
	SDL_Rect* p_arrow_src = nullptr;
	SDL_Rect arrow_dst;
	SDL_Rect* p_arrow_dst = nullptr;
	double angle = 0;
	SDL_Point* p_center = nullptr;
	SDL_Point center;
	iPoint position;
	Mix_Chunk* shoot = nullptr;
	SDL_Rect bag_complete;
	SDL_Rect bag_incomplete;
	float orientationx, orientationy;

};

#endif