#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSphere.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_render.h"

#include <time.h>
#include <stdlib.h> 

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation1 = NULL;
	current_animation2 = NULL;

	position.x = 350;
	position.y = 400;

	//initial position arrow

	arrow_src = { 15, 514, 22, 55 };
	p_arrow_src = &arrow_src;
	arrow_dst = { position.x - 49.69, position.y - 80.3, 22 * 2, 55 * 2 };
	p_arrow_dst = &arrow_dst;
	center = { 20, 64 };
	p_center = &center;

	// idle left 
	idle_left.PushBack({ 16, 17, 17, 19 });
	idle_left.PushBack({ 50, 17, 17, 19 });
	idle_left.PushBack({ 84, 17, 17, 19 });
	idle_left.PushBack({ 118, 17, 17, 19 });
	idle_left.loop = true;
	idle_left.speed = 0.1f;


	// Move right
	right.PushBack({ 415, 20, 34, 20 });
	right.PushBack({ 451, 20, 34, 20 });
	right.PushBack({ 486, 20, 34, 20 });
	right.PushBack({ 520, 20, 34, 20 });
	right.PushBack({ 552, 20, 34, 20 });
	right.PushBack({ 9, 56, 34, 20 });
	right.PushBack({ 41, 56, 34, 20 });
	right.PushBack({ 75, 56, 34, 20 });
	right.loop = true;
	right.speed = 0.5f;

	//idle right
	idle_right.PushBack({ 114, 55, 34, 20 });
	idle_right.PushBack({ 148, 55, 34, 20 });
	idle_right.PushBack({ 215, 55, 34, 20 });
	idle_right.PushBack({ 182, 55, 34, 20 });
	idle_right.PushBack({ 249, 55, 34, 20 });
	idle_right.PushBack({ 285, 55, 29, 20 });//
	idle_right.PushBack({ 249, 55, 34, 20 });
	idle_right.PushBack({ 285, 55, 29, 20 });//
	idle_right.loop = true;
	idle_right.speed = 0.1f;

	//Bags
	bag_complete = { 358, 833, 56, 24 };
	bag_incomplete = { 424, 834, 40, 23 };

	//Bob Shot
	bobShot.PushBack({ 254, 19, 17, 17 });
	bobShot.PushBack({ 288, 18, 22, 18 });
	bobShot.PushBack({ 322, 18, 22, 18 });
	bobShot.speed = 0.1f;
	bobShot.loop = false;

	//Base Mecanism Left
	base_left.PushBack({ 87, 813, 56, 24 });
	base_left.PushBack({ 153, 813, 56, 24 });
	base_left.PushBack({ 219, 813, 56, 24 });
	base_left.PushBack({ 285, 813, 56, 24 });
	base_left.PushBack({ 87, 843, 56, 24 });
	base_left.PushBack({ 153, 843, 56, 24 });
	base_left.PushBack({ 219, 843, 56, 24 });
	base_left.PushBack({ 285, 843, 56, 24 });
	base_left.PushBack({ 87, 874, 56, 24 });
	base_left.PushBack({ 153, 874, 56, 24 });
	base_left.PushBack({ 219, 874, 56, 24 });
	base_left.PushBack({ 285, 874, 56, 24 });
	base_left.speed = 0.0f;

	//Lever
	lever.PushBack({ 280, 789, 16, 16 });
	lever.PushBack({ 300, 789, 16, 16 });
	lever.PushBack({ 320, 789, 16, 16 });
	lever.PushBack({ 340, 789, 16, 16 });
	lever.PushBack({ 360, 789, 16, 16 });
	lever.PushBack({ 380, 789, 16, 16 });
	lever.PushBack({ 400, 789, 16, 16 });
	lever.PushBack({ 420, 789, 16, 16 });
	lever.speed = 0.0f;

	//Top base
	top_base = { 27, 820, 34, 16 };

	//Blow tube
	blow = { 37, 869, 13, 11 };

	mystate = PREUPDATE;


}

ModulePlayer::~ModulePlayer()
{
	App->textures->Unload(graphics);

}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	mystate = FIRST;
	graphics = App->textures->Load("Sprites.png");
	shoot = App->audio->Load_effects("BubbleShot.wav");

	orientationy = -8;
	orientationx = 0;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	angle = 0;
	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::PreUpdate(){

	if (mystate == PREUPDATE){	
		App->spheres->AddSphere(App->spheres->spheres[Random], 306, 368);
		mystate = UPDATE;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::Update()
{
	
	int speed = 1;
	current_animation1 = &idle_right;
	if (current_animation2 == &bobShot){
		if (bobShot.Finished()){
			current_animation2 = &idle_left;
			bobShot.Reset();
		}
	}
	else{
		current_animation2 = &idle_left;
	}
	current_animation_BaseLeft = &base_left;
	current_animation_lever = &lever;


	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (current_animation1 != &right)
		{
			lever.speed = -0.4f;
			base_left.speed = -0.4f;
			right.speed=-0.4f;
			current_animation1 = &right;
		}

		if (angle>-70)
			angle -= 2;


		if (orientationx > -6)
		{
			if (orientationx <= 0)
			{
				orientationx -= 0.18;
				orientationy += 0.18;
			}
			else
			{
				orientationx -= 0.18;
				orientationy -= 0.18;
			}

		}

	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (current_animation1 != &right)
		{
			lever.speed = 0.4f;
			base_left.speed = 0.4f;
			right.speed = 0.4f;
			current_animation1 = &right;
		}


		if (angle<70)
			angle += 2;

		if (orientationx < 6)
		{
			if (orientationx >= 0)
			{
				orientationx += 0.18;
				orientationy += 0.18;
			}
			else
			{
				orientationx += 0.18;
				orientationy -= 0.18;
			}
		}
	}


	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN && App->spheres->next_sphere==true)
	{
		//App->spheres->AddSphere(App->spheres->spheres[Random], 310, 370);
		App->spheres->active[App->spheres->last_sphere-1]->speed.x = orientationx;
		App->spheres->active[App->spheres->last_sphere-1]->speed.y = orientationy;

		if (current_animation2 != &bobShot)
		{
			current_animation2 = &bobShot;
		}
		Mix_PlayChannel(-1, shoot, 0);
		App->spheres->next_sphere = false;

	}



	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE){

		current_animation1 = &idle_right;
		base_left.speed = 0.0f;
		lever.speed = 0.0f;
	}


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x - 185, position.y - 14, &bag_complete);
	App->render->Blit(graphics, position.x - 185, position.y - 14, &bag_incomplete);
	App->render->Blit(graphics, position.x - 62, position.y - 46, &top_base);
	App->render->Blit(graphics, position.x - 92, position.y - 14, &(current_animation_BaseLeft->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 3, position.y + 2, &(current_animation_lever->GetCurrentFrame()));
	SDL_RenderCopyEx(App->render->renderer, graphics, p_arrow_src, p_arrow_dst, angle, p_center, SDL_FLIP_NONE);
	App->render->Blit(graphics, position.x - 44, position.y, &blow);
	App->render->Blit(graphics, position.x, position.y, &(current_animation1->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 78, position.y - 4, &(current_animation2->GetCurrentFrame()));
	//	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(){
	srand(time(NULL));
	bool succes = false;
	if (mystate == FIRST){
		while (succes != true){
			Random = rand() % 8;
			for (int i = 0; i < App->spheres->last_sphere; i++){
				if (App->spheres->active[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = PREUPDATE;

	}
	else if (mystate == UPDATE){
		while (succes != true){
			Random = rand() % 8;
			for (int i = 0; i < App->spheres->last_sphere; i++){
				if (App->spheres->active[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = POSTUPDATE;
	}

	return update_status::UPDATE_CONTINUE;
}