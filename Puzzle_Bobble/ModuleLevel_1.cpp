#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModulePlayer.h"
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
	1 Green
	2 Gray
	3 Black
	4 Red
	5 Orange
	6 Yellow
	7 Violet
	*/
	int map[] = {4,4,6,6,0,0,1,1,
			     4,4,6,6,0,0,1,
			 	 0,0,1,1,4,4,6,6,
				 0,1,1,4,4,6,6,
				 9, 9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9, 
				 9, 9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9, 
				 9, 9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9, 
				 9, 9, 9, 9, 9, 9, 9, 9,
				 9, 9, 9, 9, 9, 9, 9};

	//int map[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


	graphics = App->textures->Load("Level1_3.png");
	level_music = App->audio->Load_music("SinglePlayerMusic.ogg"); 
	
	App->player->Enable();
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
		App->fade->FadeToBlack(App->level_1, App->level_2, 1);
	}
	if (App->spheres->LoseCondition == true)
	{
		App->spheres->LoseCondition = false;
		App->fade->FadeToBlack(App->level_1, App->game_over, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleLevel_1::CleanUp()
{

	App->player->Disable();

	for (int i = 0; i < App->spheres->last_sphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active[i]->collider);

		App->spheres->active[i]->collider = nullptr;
		App->spheres->active[i] = nullptr;


	}

	for (int i = 0; i < NUM_SQUARES; i++)
	{

		App->board->board[i].Empty = true;

	}

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}