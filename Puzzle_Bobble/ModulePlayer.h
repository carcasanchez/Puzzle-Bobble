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
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CheckLose();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation1 = nullptr;
	Animation* current_animation2 = nullptr;
	Animation* current_animation3 = nullptr;
	Animation* current_animation_BaseLeft = nullptr;
	Animation* current_animation_lever = nullptr;
	Animation idle_left;
	Animation idle_right;
	Animation right;
	Animation bobShot;
	Animation base_left;
	Animation lever;
	Animation hurry_up;
	Animation hurry_up_dragon;
	SDL_Rect arrow_src;
	SDL_Rect* p_arrow_src = nullptr;
	SDL_Rect arrow_dst;
	SDL_Rect* p_arrow_dst = nullptr;
	double angle = 0.0;
	SDL_Point* p_center = nullptr;
	SDL_Point center;
	iPoint position;
	Mix_Chunk* shoot = nullptr;
	Mix_Chunk* explosion = nullptr;
	int b_destroyed_left = 0;
	SDL_Rect bag_complete;
	SDL_Rect bag_incomplete;
	SDL_Rect top_base;
	SDL_Rect blow;
	SDL_Rect prev_bobble[8];
	float orientationx, orientationy;
	int Random;
	bool LoseCondition = false;
	unsigned int lastTime, currentTime;
	int booblesGoDown_left, booblesCounterDown_left;
	States mystate;
};

#endif