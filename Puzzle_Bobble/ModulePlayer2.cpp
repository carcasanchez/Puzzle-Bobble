#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSphere.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "SDL\include\SDL_render.h"
#include "SDL\include\SDL_timer.h"

#include <time.h>
#include <stdlib.h> 
#include <math.h>

#define PI 3.14159265
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	graphics = NULL;
	current_animation1 = NULL;
	current_animation2 = NULL;
	current_animation3 = NULL;

	position.x = 335 * SCREEN_SIZE;
	position.y = 200 * SCREEN_SIZE;

	//initial position arrow

	arrow_src = { 15, 514, 22, 55 };
	p_arrow_src = &arrow_src;
	arrow_dst = { position.x - 104.845f*SCREEN_SIZE, position.y - 40.15f*SCREEN_SIZE, 22 * 2, 55 * 2 };
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

	//Dragon Hurry Up
	hurry_up_dragon.PushBack({ 281, 42, 26, 28 });
	hurry_up_dragon.PushBack({ 308, 42, 26, 28 });
	hurry_up_dragon.speed = 0.2f;

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

	hurry_up.loop = false;
	hurry_up.speed = 0.04f;

	mystate = PREUPDATE;


}

ModulePlayer2::~ModulePlayer2()
{
	App->textures->Unload(graphics);

}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");
	mystate = FIRST;
	graphics = App->textures->Load("Game/Sprites.png");
	shoot = App->audio->Load_effects("Game/BubbleShot.wav");
	//App->spheres->AddSphere(App->spheres->spheres[Random], 306, 368);
	lastTime = SDL_GetTicks();

	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");
	angle = 0;
	App->textures->Unload(graphics);

	return true;
}

bool ModulePlayer2::CheckLose(){

	for (unsigned int i = App->spheres->last_sphere_right; i > 0; i--)
	{
		if (App->spheres->active_right[i] == nullptr)
			continue;
		if (App->spheres->active_right[i]->position.y > 170 * SCREEN_SIZE && App->spheres->active_right[i]->speed.y == 0)
		{
			return true;
		}
	}
	return false;
}


update_status ModulePlayer2::PreUpdate(){

	if (mystate == PREUPDATE){	
		LoseCondition = CheckLose();
		
		App->spheres->AddSphere(App->spheres->spheres[Random], 73 + 197 * SCREEN_SIZE, 184* SCREEN_SIZE, COLLIDER_SPHERE_RIGHT);
	
		
		mystate = UPDATE;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer2::Update()
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


	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
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

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
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

	

	currentTime = SDL_GetTicks();

	
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN && App->spheres->next_sphere_right == true || currentTime - lastTime > 8000)
	{

		App->spheres->active_right[App->spheres->last_sphere_right - 1]->speed.x = (sin(angle*PI / 180)) * SPEED;
		App->spheres->active_right[App->spheres->last_sphere_right - 1]->speed.y = -(cos(angle*PI / 180)) * SPEED;

		if (current_animation2 != &bobShot)
		{
			current_animation2 = &bobShot;
		}
		Mix_PlayChannel(-1, shoot, 0);
		App->spheres->next_sphere_right = false;
		lastTime = currentTime;
		hurry_up.Reset();
	}

	if (currentTime - lastTime > 3000)
	{

		current_animation3 = &hurry_up;
		current_animation2 = &hurry_up_dragon;
		App->render->Blit(graphics, position.x - 170 * SCREEN_SIZE, position.y - 35 * SCREEN_SIZE, &(current_animation3->GetCurrentFrame()));
	}


	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE){

		current_animation1 = &idle_right;
		base_left.speed = 0.0f;
		lever.speed = 0.0f;
	}


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x - 172*SCREEN_SIZE, position.y - 7*SCREEN_SIZE, &bag_complete);
	App->render->Blit(graphics, position.x - 172 * SCREEN_SIZE, position.y - 7 * SCREEN_SIZE, &bag_incomplete);
	App->render->Blit(graphics, position.x - 111 * SCREEN_SIZE, position.y - 23 * SCREEN_SIZE, &top_base);
	App->render->Blit(graphics, position.x - 126 * SCREEN_SIZE, position.y - 7 * SCREEN_SIZE, &(current_animation_BaseLeft->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 82 * SCREEN_SIZE, position.y + 1 * SCREEN_SIZE, &(current_animation_lever->GetCurrentFrame()));
	SDL_RenderCopyEx(App->render->renderer, graphics, p_arrow_src, p_arrow_dst, angle, p_center, SDL_FLIP_NONE);
	App->render->Blit(graphics, position.x - 102 * SCREEN_SIZE, position.y, &blow);
	App->render->Blit(graphics, position.x - 80 * SCREEN_SIZE, position.y - 2 * SCREEN_SIZE, &(current_animation1->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 122 * SCREEN_SIZE, position.y - 10 * SCREEN_SIZE, &(current_animation2->GetCurrentFrame()));
	//	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer2::PostUpdate(){
	srand(time(NULL));
	bool succes = false;


	if (mystate == FIRST){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere_right; i++){
				if (App->spheres->active_right[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active_right[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = PREUPDATE;

	}

	 if (mystate == UPDATE){
 		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere_right; i++){
				if (App->spheres->active_right[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active_right[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = POSTUPDATE;
	}

	return update_status::UPDATE_CONTINUE;
}
