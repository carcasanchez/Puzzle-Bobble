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
#include "UserInterface.h"

ModuleUserInterface::ModuleUserInterface()
{
	graphics_UI = NULL;

	/* Win - Lose */
	win = { 81, 320, 110, 33 };
	lose = { 84, 358, 125, 32 };
}

ModuleUserInterface::~ModuleUserInterface()
{
	App->textures->Unload(graphics_UI);
}


// Load assets
bool ModuleUserInterface::Start()
{
	LOG("Loading UI");
	graphics_UI = App->textures->Load("Game/SpritesP2.png");
	return true;
}

bool ModuleUserInterface::CleanUp()
{
	LOG("Unloading UI");
	App->textures->Unload(graphics_UI);
	return true;
}

void ModuleUserInterface::LoseWin()
{
	App->render->Blit(graphics_UI, 17 * SCREEN_SIZE, 80 * SCREEN_SIZE, &lose);
	App->render->Blit(graphics_UI, 180 * SCREEN_SIZE, 80* SCREEN_SIZE, &win);
}

void ModuleUserInterface::WinLose()
{
	App->render->Blit(graphics_UI, 17 * SCREEN_SIZE, 80 * SCREEN_SIZE, &win);
	App->render->Blit(graphics_UI, 180 * SCREEN_SIZE, 80 * SCREEN_SIZE, &lose);
}



update_status ModuleUserInterface::Update()
{
	if (App->player->IsEnabled() && App->player2->IsEnabled())
	{
		if (App->board->CheckWinL() || App->player2->LoseCondition == true)
		{
			WinLose();
			if (check_time == 0)check_time = SDL_GetTicks();
		}

		else if (App->board->CheckWinR() || App->player->LoseCondition == true)
		{
			LoseWin();
			if (check_time == 0)check_time = SDL_GetTicks();
		}


		if (check_time != 0)
		{

			if (SDL_GetTicks() - check_time >= 2000)
			{
				check_time = 0;
				App->fade->FadeToBlack(App->level_1, App->menu_screen, 1);
			}

		}
	}


	return UPDATE_CONTINUE;
}