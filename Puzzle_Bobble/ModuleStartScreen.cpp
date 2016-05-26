#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleStartScreen.h"
#include "ModuleLevel_1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleBoard.h"
ModuleStartScreen::ModuleStartScreen()
{
	background = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleStartScreen::~ModuleStartScreen()
{}

bool ModuleStartScreen::Start()
{

	graphics = App->textures->Load("Game/Start_Screen.png");
	
	if (Mix_PlayMusic(App->audio->start_music, 0) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	App->board->Disable();
	App->board->Enable();
	return true;
	
}

update_status ModuleStartScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &background);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		if (play == false)
		{
			Mix_PlayChannel(-1, App->audio->start_button, 0);
			play = true;
		}
		App->fade->FadeToBlack(App->menu_screen, App->level_1, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleStartScreen::CleanUp()
{
	play = false;
	App->textures->Unload(graphics);
	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}