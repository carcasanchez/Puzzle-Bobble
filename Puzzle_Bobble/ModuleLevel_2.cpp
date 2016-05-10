#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_2.h"
#include "ModuleStartScreen.h"
#include "ModulePlayer.h"
#include "ModuleBoard.h"
#include "ModuleCongrats.h"
#include "ModuleGameOver.h"


ModuleLevel_2::ModuleLevel_2()
{
	level2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleLevel_2::~ModuleLevel_2()
{}

bool ModuleLevel_2::Start()
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
	graphics = App->textures->Load("Game/Level3_5.png");
	level_music = App->audio->Load_music("Game/SinglePlayerMusic.ogg");
	int map[] = { 4,7,6,3,3,3,2,0,
					4,7,7,5,3,2,7,
					2,2,3,7,6,3,6,2,
					2,7,7,4,4,5,3,
					7,7,0,6,7,5,5,3,
					9, 9, 9, 9, 9, 9, 9,
					9, 9, 9, 9, 9, 9, 9, 9,
					9, 9, 9, 9, 9, 9, 9,
					9, 9, 9, 9, 9, 9, 9, 9,
					9, 9, 9, 9, 9, 9, 9,
					9, 9, 9, 9, 9, 9, 9, 9,
					9, 9, 9, 9, 9, 9, 9 };

	App->player->Enable();
	App->board->CreateMap(map);

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	return true;
}

update_status ModuleLevel_2::Update()
{
	App->render->Blit(graphics, 0, 0, &level2);

	if (App->board->CheckWin())
	{
		App->fade->FadeToBlack(App->level_2, App->congratulations, 1);
	}

	if (App->player->LoseCondition == true)
	{
		App->player->LoseCondition = false;
		App->fade->FadeToBlack(App->level_2, App->game_over, 1);
	}
	
	return UPDATE_CONTINUE;
}

bool ModuleLevel_2::CleanUp()
{
	App->player->Disable();

	for (unsigned int i = 0; i < App->spheres->last_sphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;

		App->collision->EraseCollider(App->spheres->active[i]->collider);

		App->spheres->active[i]->collider = nullptr;
		App->spheres->active[i] = nullptr;
		

	}

	App->spheres->last_sphere = 0;

	for (unsigned int i = 0; i < NUM_SQUARES; i++)
	{

		App->board->board[i].Empty = true;

	}

	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}