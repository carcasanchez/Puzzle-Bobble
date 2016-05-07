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
#include <math.h>

#define PI 3.14159265
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
	arrow_dst = { position.x - 49.69f, position.y - 80.3f, 22 * 2, 55 * 2 };
	p_arrow_dst = &arrow_dst;
	center = { 20, 64 };
	p_center = &center;

	// idle left 
	idle_left.PushBack({ 11, 42, 26, 28 });
	idle_left.PushBack({ 38, 42, 26, 28 });
	idle_left.PushBack({ 65, 42, 26, 28 });
	idle_left.PushBack({ 92, 42, 26, 28 });
	idle_left.loop = true;
	idle_left.speed = 0.1f;


	// Move right
	right.PushBack({ 8, 18, 29, 19 });
	right.PushBack({ 38, 18, 29, 19 });
	right.PushBack({ 68, 18, 29, 19 });
	right.PushBack({ 98, 18, 29, 19 });
	right.PushBack({ 128, 18, 29, 19 });
	right.PushBack({ 158, 18, 29, 19 });
	right.PushBack({ 188, 18, 29, 19 });
	right.PushBack({ 218, 18, 29, 19 });
	right.loop = true;
	right.speed = 0.5f;

	//idle right
	idle_right.PushBack({ 248, 18, 29, 19 });
	idle_right.PushBack({ 278, 18, 29, 19 });
	idle_right.PushBack({ 308, 18, 29, 19 });
	idle_right.PushBack({ 338, 18, 29, 19 });
	idle_right.PushBack({ 368, 18, 29, 19 });
	idle_right.PushBack({ 398, 18, 29, 19 });//
	idle_right.PushBack({ 368, 18, 29, 19 });
	idle_right.PushBack({ 398, 18, 29, 19 });//
	idle_right.loop = true;
	idle_right.speed = 0.1f;

	//Bags
	bag_complete = { 358, 833, 56, 24 };
	bag_incomplete = { 424, 834, 40, 23 };

	//Bob Shot
	bobShot.PushBack({ 200, 42, 26, 28 });
	bobShot.PushBack({ 227, 42, 26, 28 });
	bobShot.PushBack({ 254, 42, 26, 28 });
	bobShot.speed = 0.4f;
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

	//hurry up
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 248, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 284, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 320, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 356, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 392, 1439, 32, 28 });
	hurry_up.PushBack({ 212, 1439, 32, 28 });
	hurry_up.PushBack({ 428, 1439, 32, 28 });

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
	graphics = App->textures->Load("Game/Sprites.png");
	shoot = App->audio->Load_effects("Game/BubbleShot.wav");

	

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

bool ModulePlayer::CheckLose(){
	for (unsigned int i = App->spheres->last_sphere; i > 0; i--){
		if (App->spheres->active[i] == nullptr)
			continue;
		if (App->spheres->active[i]->position.y > 170 * SCREEN_SIZE)
		{
			return true;
		}

	}
	return false;
}

// Update: draw background
update_status ModulePlayer::PreUpdate(){

	if (mystate == PREUPDATE){	
		LoseCondition = CheckLose();
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

		if (angle>-70.0)
			angle -= 2.0;


		/////


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


		if (angle<70.0)
			angle += 2.0;

		//////
	}


	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN && App->spheres->next_sphere==true)
	{

		App->spheres->active[App->spheres->last_sphere - 1]->speed.x = (sin(angle*PI / 180)) * SPEED;
		App->spheres->active[App->spheres->last_sphere - 1]->speed.y = -(cos(angle*PI / 180)) * SPEED;

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
	App->render->Blit(graphics, position.x, position.y-4, &(current_animation1->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 95, position.y - 20, &(current_animation2->GetCurrentFrame()));
	//	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(){
	srand(time(NULL));
	bool succes = false;
	if (mystate == FIRST){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere; i++){
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
			for (unsigned int i = 0; i < App->spheres->last_sphere; i++){
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
