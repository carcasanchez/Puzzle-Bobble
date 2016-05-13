#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_1.h"
#include "ModuleCongrats.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleStartScreen.h"
#include "ModuleBoard.h"
#include "ModuleGameOver.h"

ModuleLevel_1::ModuleLevel_1()
{
	level1 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

}

ModuleLevel_1::~ModuleLevel_1()
{}

bool ModuleLevel_1::Start()
{
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
	int map[] = { 0, 2, 3, 3, 3, 6, 7, 4,
		0, 2, 3, 3, 3, 6, 7, 4,
		0, 2, 3, 3, 3, 6, 7, 4,
		0, 2, 3, 3, 3, 6, 7, 4,
		9, 9, 9, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9, 9, 9,
		9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9, 
				 9, 9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9};

	//int map[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	graphics = App->textures->Load("Game/two_player_background.png");
	level_music = App->audio->Load_music("Game/SinglePlayerMusic.ogg"); 
	
	App->player->Enable();
	App->player2->Enable();
	App->board->CreateMap(map);
	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());
	}
	return true;
}

update_status ModuleLevel_1::Update()
{
	App->render->Blit(graphics, 0, 0, &level1);

	if (App->board->CheckWin())
	{
		App->fade->FadeToBlack(App->level_1, App->congratulations, 1);
	}
	if (App->player->LoseCondition == true)
	{
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleLevel_1::CleanUp()
{

	App->player->Disable();
	App->player2->Disable();

	//LEFT
	for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++)
	{
		if (App->spheres->active_left[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active_left[i]->collider);

		App->spheres->active_left[i]->collider = nullptr;
		App->spheres->active_left[i] = nullptr;
	}

	//RIGHT
	for (unsigned int i = 0; i < App->spheres->last_sphere_right; i++)
	{
		if (App->spheres->active_right[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active_right[i]->collider);

		App->spheres->active_right[i]->collider = nullptr;
		App->spheres->active_right[i] = nullptr;
	}

	App->spheres->last_sphere_left = 0;
	App->spheres->last_sphere_right = 0;

   for (unsigned int i = 0; i < NUM_SQUARES; i++)
	{
	   if (App->board->board_left[i] != nullptr){
		   App->board->board_left[i]->Empty = true;
	   }
	   if (App->board->board_right[i] != nullptr){
		   App->board->board_right[i]->Empty = true;
	   }
	}

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}