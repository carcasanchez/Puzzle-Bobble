#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleSphere.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation1 = NULL;
	current_animation2 = NULL;
	current_animation_arrow = NULL;
	
	position.x = 350;
	position.y = 400;

	//initial position arrow
	arrow_init.PushBack({ 15, 514, 22, 55 });
	
	//arrow left
	arrow_left.PushBack({ 15, 514, 22, 55 });
	arrow_left.PushBack({ 49, 515, 21, 54 });
	arrow_left.PushBack({ 83, 515, 21, 54 });
	arrow_left.PushBack({ 117, 515, 21, 54 });
	arrow_left.PushBack({ 151, 515, 21, 54 });
	arrow_left.PushBack({ 185, 515, 21, 54 });
	arrow_left.PushBack({ 219, 515, 21, 54 });
	arrow_left.PushBack({ 253, 515, 21, 54 });
	arrow_left.PushBack({ 287, 516, 21, 53 });
	arrow_left.PushBack({ 321, 515, 21, 54 });
	arrow_left.PushBack({ 355, 516, 21, 53 });
	arrow_left.PushBack({ 389, 516, 21, 53 });
	arrow_left.PushBack({ 423, 516, 21, 53 });
	arrow_left.PushBack({ 490, 517, 23, 52 });
	arrow_left.PushBack({ 523, 517, 25, 52 });
	arrow_left.PushBack({ 591, 517, 26, 52 });
	arrow_left.PushBack({ 12, 584, 28, 50 });
	arrow_left.PushBack({ 46, 584, 29, 50 });
	arrow_left.PushBack({ 79, 584, 29, 50 });
	arrow_left.PushBack({ 113, 585, 31, 49 });
	arrow_left.PushBack({ 147, 585, 32, 49 });
	arrow_left.PushBack({ 196, 586, 33, 48 });
	arrow_left.PushBack({ 246, 586, 35, 47 });
	arrow_left.PushBack({ 295, 586, 36, 47 });
	arrow_left.PushBack({ 345, 586, 36, 47 });
	arrow_left.PushBack({ 395, 587, 37, 46 });
	arrow_left.PushBack({ 444, 588, 38, 44 });
	arrow_left.PushBack({ 544, 588, 39, 44 });
	arrow_left.PushBack({ 23, 655, 41, 43 });
	arrow_left.PushBack({ 73, 656, 42, 41 });
	arrow_left.PushBack({ 123, 656, 42, 41 });
	arrow_left.PushBack({ 173, 656, 42, 41 });
	arrow_left.PushBack({ 222, 657, 44, 40 });
	arrow_left.PushBack({ 272, 658, 44, 38 });
	arrow_left.PushBack({ 322, 659, 45, 37 });
	arrow_left.PushBack({ 372, 659, 45, 37 });
	arrow_left.PushBack({ 421, 659, 47, 36 });
	arrow_left.PushBack({ 472, 660, 47, 35 });
	arrow_left.PushBack({ 524, 661, 48, 33 });
	arrow_left.PushBack({ 21, 712, 48, 32 });
	arrow_left.PushBack({ 85, 712, 48, 32 });
	arrow_left.PushBack({ 149, 713, 50, 30 });
	arrow_left.PushBack({ 213, 713, 50, 30 });
	arrow_left.PushBack({ 277, 714, 51, 29 });
	arrow_left.PushBack({ 342, 715, 51, 27 });
	arrow_left.PushBack({ 406, 715, 51, 27 });
	arrow_left.PushBack({ 471, 716, 51, 26 });
	arrow_left.PushBack({ 535, 717, 52, 24 });
	arrow_left.PushBack({ 20, 751, 52, 24 });
	arrow_left.PushBack({ 84, 752, 53, 22 });
	arrow_left.PushBack({ 148, 752, 53, 22 });
	arrow_left.PushBack({ 212, 752, 53, 21 });
	arrow_left.PushBack({ 276, 752, 54, 21 });
	arrow_left.PushBack({ 341, 752, 53, 21 });
	arrow_left.PushBack({ 404, 752, 54, 21 });
	arrow_left.PushBack({ 468, 752, 54, 21 });
	arrow_left.PushBack({ 532, 752, 54, 21 });
	arrow_left.PushBack({ 19, 786, 54, 21 });
	arrow_left.PushBack({ 83, 786, 54, 21 });
	arrow_left.PushBack({ 148, 786, 53, 21 });
	arrow_left.PushBack({ 212, 786, 53, 21 });
	arrow_left.speed = 1.f;
	
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

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	current_animation1 = &idle_right;
	current_animation2 = &idle_left;
	current_animation_arrow = &arrow_init;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (current_animation1 != &left)
		{
			current_animation1 = &left;
		}
		
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		if (current_animation1 != &right)
		{
			current_animation1 = &right;
		}
		if (current_animation_arrow != &arrow_left)
		{
			current_animation_arrow = &arrow_left;
		}
	}


	// TODO 3: Shoot balls when the player hits SPACE

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
	App->render->Blit(graphics, position.x, position.y, &(current_animation1->GetCurrentFrame()));
	App->render->Blit(graphics, position.x-100, position.y, &(current_animation2->GetCurrentFrame()));
	App->render->Blit(graphics, position.x - 50, position.y - 80, &(current_animation_arrow->GetCurrentFrame()));


	return UPDATE_CONTINUE;
}