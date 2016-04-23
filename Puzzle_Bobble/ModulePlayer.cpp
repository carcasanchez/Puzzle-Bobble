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

	// move left
	left.PushBack({ 79, 54, 23, 18 });
	left.PushBack({ 45, 54, 23, 18 });
	left.PushBack({ 13, 54, 23, 18 });
	left.PushBack({ 556, 18, 20, 18 });
	left.PushBack({ 524, 17, 21, 19 });
	left.PushBack({ 490, 18, 21, 18 });
	left.PushBack({ 455, 19, 20, 17 });
	left.PushBack({ 419, 19, 21, 17 });
	left.loop = true;
	left.speed = 0.1f;

	// Move right
	right.PushBack({ 419, 19, 21, 17 });
	right.PushBack({ 455, 19, 20, 17 });
	right.PushBack({ 490, 18, 21, 18 });
	right.PushBack({ 524, 17, 21, 19 });
	right.PushBack({ 556, 18, 20, 18 });
	right.PushBack({ 13, 54, 23, 18 });
	right.PushBack({ 45, 54, 23, 18 });
	right.PushBack({ 79, 54, 23, 18 });
	right.loop = true;
	right.speed = 0.1f;

	//idle right
	idle_right.PushBack({ 119, 53, 19, 19 });
	idle_right.PushBack({ 153, 53, 18, 19 });
	idle_right.PushBack({ 220, 53, 20, 19 });
	idle_right.PushBack({ 187, 53, 19, 19 });
	idle_right.PushBack({ 252, 54, 21, 18 });
	idle_right.PushBack({ 283, 55, 24, 17 });
	idle_right.PushBack({ 252, 54, 21, 18 });
	idle_right.PushBack({ 283, 55, 24, 17 });
	idle_right.loop = true;
	idle_right.speed = 0.1f;

	//Bags
	bag_complete = { 358, 833, 56, 24 };
	bag_incomplete = { 424, 834, 40, 23 };

	//Bob Shot
	bobShot.PushBack({ 254, 19, 17, 17 });
	bobShot.PushBack({ 288, 18, 22, 18 });
	bobShot.PushBack({ 322, 18, 22, 18 });
	bobShot.speed = 0.05f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

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
update_status ModulePlayer::Update()
{
	int speed = 1;
	current_animation1 = &idle_right;
	current_animation2 = &idle_left;


	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (current_animation1 != &left)
		{
			current_animation1 = &left;
		}


		if (angle>-70)
			angle -= 1;


		if (orientationx > -6)
		{
			if (orientationx <= 0)
			{
				orientationx -= 0.1;
				orientationy += 0.1;
			}
			else
			{
				orientationx -= 0.1;
				orientationy -= 0.1;
			}

		}

	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (current_animation1 != &right)
		{
			current_animation1 = &right;
		}

		if (angle<70)
			angle += 1;

		if (orientationx < 6)
		{
			if (orientationx >= 0)
			{
				orientationx += 0.1;
				orientationy += 0.1;
			}
			else
			{
				orientationx += 0.1;
				orientationy -= 0.1;
			}

		}



	}




	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN)
	{
		App->spheres->AddSphere(App->spheres->redSphere, position.x, position.y);

		if (current_animation2 != &bobShot)
		{
			bobShot.Reset();
			current_animation2 = &bobShot;
		}
		Mix_PlayChannel(-1, shoot, 0);
	}



	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
		current_animation1 = &idle_right;


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x - 175, position.y - 10, &bag_complete);
	App->render->Blit(graphics, position.x - 175, position.y - 10, &bag_incomplete);
	App->render->Blit(graphics, position.x, position.y, &(current_animation1->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 100, position.y, &(current_animation2->GetCurrentFrame()));
	SDL_RenderCopyEx(App->render->renderer, graphics, p_arrow_src, p_arrow_dst, angle, p_center, SDL_FLIP_NONE);
	//	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));


	return UPDATE_CONTINUE;
}