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
#include "SDL\include\SDL_timer.h"



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
	current_animation3 = NULL;

	position.x = 175 * SCREEN_SIZE;
	position.y = 200 * SCREEN_SIZE;

	//initial position arrow

	arrow_src = { 15, 320, 22, 55 };
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
	bag_complete = { 358, 233, 56, 24 };
	bag_incomplete = { 424, 234, 40, 23 };

	//Bob Shot
	bobShot.PushBack({ 200, 42, 26, 28 });
	bobShot.PushBack({ 227, 42, 26, 28 });
	bobShot.PushBack({ 254, 42, 26, 28 });
	bobShot.speed = 0.4f;
	bobShot.loop = false;

	//Dragon Hurry Up
	hurry_up_dragon.PushBack({ 281, 42, 26, 28 });
	hurry_up_dragon.PushBack({ 308, 42, 26, 28 });
	hurry_up_dragon.speed = 0.15f;

	//Base Mecanism Left
	base_left.PushBack({ 87, 213, 56, 24 });
	base_left.PushBack({ 153, 213, 56, 24 });
	base_left.PushBack({ 219, 213, 56, 24 });
	base_left.PushBack({ 285, 213, 56, 24 });
	base_left.PushBack({ 87, 243, 56, 24 });
	base_left.PushBack({ 153, 243, 56, 24 });
	base_left.PushBack({ 219, 243, 56, 24 });
	base_left.PushBack({ 285, 243, 56, 24 });
	base_left.PushBack({ 87, 274, 56, 24 });
	base_left.PushBack({ 153, 274, 56, 24 });
	base_left.PushBack({ 219, 274, 56, 24 });
	base_left.PushBack({ 285, 274, 56, 24 });
	base_left.speed = 0.0f;

	//Lever
	lever.PushBack({ 280, 189, 16, 16 });
	lever.PushBack({ 300, 189, 16, 16 });
	lever.PushBack({ 320, 189, 16, 16 });
	lever.PushBack({ 340, 189, 16, 16 });
	lever.PushBack({ 360, 189, 16, 16 });
	lever.PushBack({ 380, 189, 16, 16 });
	lever.PushBack({ 400, 189, 16, 16 });
	lever.PushBack({ 420, 189, 16, 16 });
	lever.speed = 0.0f;

	//Top base
	top_base = { 27, 220, 34, 16 };

	//Blow tube
	blow = { 37, 269, 13, 11 };

	//hurry up
	hurry_up.PushBack({ 212, 339, 32, 28 });
	hurry_up.PushBack({ 248, 339, 32, 28 });
	hurry_up.PushBack({ 212, 339, 32, 28 });
	hurry_up.PushBack({ 284, 339, 32, 28 });
	hurry_up.PushBack({ 212, 339, 32, 28 });
	hurry_up.PushBack({ 320, 339, 32, 28 });
	hurry_up.PushBack({ 212, 339, 32, 28 });
	hurry_up.PushBack({ 356, 339, 32, 28 });
	hurry_up.PushBack({ 212, 339, 32, 28 });
	hurry_up.PushBack({ 392, 339, 32, 28 });
	hurry_up.PushBack({ 212, 339, 32, 28 });
	hurry_up.PushBack({ 428, 339, 32, 28 });

	hurry_up.loop = false;
	hurry_up.speed = 0.04f;

	//prev_bobbles array
	prev_bobble[0] = { 52, 286, 16, 16 };
	prev_bobble[1] = { 52, 312, 16, 16 };
	prev_bobble[2] = { 52, 338, 16, 16 };
	prev_bobble[3] = { 52, 364, 16, 16 };
	prev_bobble[4] = { 52, 390, 16, 16 };
	prev_bobble[5] = { 52, 416, 16, 16 };
	prev_bobble[6] = { 52, 442, 16, 16 };
	prev_bobble[7] = { 52, 468, 16, 16 };

	mystate = PREUPDATE;


}

ModulePlayer::~ModulePlayer()
{
	App->textures->Unload(graphics);

}

// Load assets
bool ModulePlayer::Start()
{
	b_destroyed_left = 0;
	LOG("Loading player");
	mystate = FIRST;
	graphics = App->textures->Load("Game/SpritesP1.png");
	
	//App->spheres->AddSphere(App->spheres->spheres[Random], 306, 368);
	lastTime = SDL_GetTicks();
	booblesGoDown_left = 16;
	booblesCounterDown_left = 0;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	angle = 0;
	App->textures->Unload(graphics);
	App->spheres->next_sphere_left = true;
	return true;
}

bool ModulePlayer::CheckLose(){
	for (unsigned int i = App->spheres->last_sphere_left; i > 0; i--){
		if (App->spheres->active_left[i] == nullptr)
			continue;
		if (App->spheres->active_left[i]->position.y > 170 * SCREEN_SIZE && App->spheres->active_left[i]->speed.y == 0)
		{
			return true;
		}
	}
	return false;
}


update_status ModulePlayer::PreUpdate(){

	if (mystate == PREUPDATE){	
		LoseCondition = CheckLose();
		
		App->spheres->AddSphere(App->spheres->spheres[Random], 73 * SCREEN_SIZE, 184 * SCREEN_SIZE, COLLIDER_SPHERE_LEFT);
		//App->spheres->AddSphere(App->spheres->spheres[Random], 120 * SCREEN_SIZE, 200 * SCREEN_SIZE);
		
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

	

	currentTime = SDL_GetTicks();

	
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_DOWN && App->spheres->next_sphere_left == true || currentTime - lastTime > 8000)
	{

		App->spheres->active_left[App->spheres->last_sphere_left - 1]->speed.x = (sin(angle*PI / 180)) * SPEED;
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->speed.y = -(cos(angle*PI / 180)) * SPEED;

		if (current_animation2 != &bobShot)
		{
			current_animation2 = &bobShot;
		}
		Mix_PlayChannel(-1, App->audio->shoot, 0);
		App->spheres->next_sphere_left = false;
		lastTime = currentTime;
		hurry_up.Reset();
		booblesCounterDown_left++;
	}



	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE){

		current_animation1 = &idle_right;
		base_left.speed = 0.0f;
		lever.speed = 0.0f;
	}

	/*
	0 Blue
	1 Gray
	2 Red
	3 Yellow
	4 Green
	5 Black
	6 Orange
	7 Violet
	*/

	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left-1]->ChangeColor(BLUE);
	}
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(GRAY);
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(RED);
	}
	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(YELLOW);
	}
	if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(GREEN);
	}
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(BLACK);
	}
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(ORANGE);
	}
	if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->active_left[App->spheres->last_sphere_left - 1]->ChangeColor(VIOLET);
	}

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN)
	{
		for (int i = 0; i < App->spheres->last_sphere_left - 1; i++)
		{
			if (App->spheres->active_left[i] == nullptr)
				continue;
			App->spheres->active_left[i]->ChangeColor(App->spheres->active_left[App->spheres->last_sphere_left - 1]->sphere_color);
		}
	}


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x - 172*SCREEN_SIZE, position.y - 7*SCREEN_SIZE, &bag_complete);
	App->render->Blit(graphics, position.x - 172 * SCREEN_SIZE, position.y - 7 * SCREEN_SIZE, &bag_incomplete);
	App->render->Blit(graphics, position.x - 111 * SCREEN_SIZE, position.y - 23 * SCREEN_SIZE, &top_base);
	App->render->Blit(graphics, position.x - 126 * SCREEN_SIZE, position.y - 7 * SCREEN_SIZE, &(current_animation_BaseLeft->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 82 * SCREEN_SIZE, position.y + 1 * SCREEN_SIZE, &(current_animation_lever->GetCurrentFrame()));
	SDL_RenderCopyEx(App->render->renderer, graphics, p_arrow_src, p_arrow_dst, angle, p_center, SDL_FLIP_NONE);
	App->render->Blit(graphics, position.x - 102 * SCREEN_SIZE, position.y, &blow);

	if (currentTime - lastTime > 3000)
	{

		current_animation3 = &hurry_up;
		current_animation2 = &hurry_up_dragon;
		App->render->Blit(graphics, position.x - 165 * SCREEN_SIZE, position.y - 20 * SCREEN_SIZE, &(current_animation3->GetCurrentFrame()));
	}

	App->render->Blit(graphics, position.x - 80 * SCREEN_SIZE, position.y - 2 * SCREEN_SIZE, &(current_animation1->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 122 * SCREEN_SIZE, position.y - 10 * SCREEN_SIZE, &(current_animation2->GetCurrentFrame()));
	//	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 135 * SCREEN_SIZE, position.y + 1 * SCREEN_SIZE, &prev_bobble[Random]);

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(){
	srand(time(NULL));
	bool succes = false;
	

	if (mystate == FIRST){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++){
				if (App->spheres->active_left[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active_left[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = PREUPDATE;

	}

	 if (mystate == UPDATE){
		while (succes != true){
			Random = rand() % 8;
			for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++){
				if (App->spheres->active_left[i] == nullptr){
					continue;
				}
				else if (App->spheres->spheres[Random].sphere_color == App->spheres->active_left[i]->sphere_color){
					succes = true;
				}
			}
		}
		mystate = POSTUPDATE;
	}

	return update_status::UPDATE_CONTINUE;
}
