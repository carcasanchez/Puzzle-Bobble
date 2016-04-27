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
#include "ModuleCongrats.h"
#include "ModuleGameOver.h"


ModuleGameOver::ModuleGameOver()
{
	gameover = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleGameOver::~ModuleGameOver()
{}

bool ModuleGameOver::Start()
{
	graphics = App->textures->Load("Game_Over.png");

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	return true;
}

update_status ModuleGameOver::Update()
{
	App->render->Blit(graphics, 0, 0, &gameover);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->game_over, App->menu_screen, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleGameOver::CleanUp()
{
	return true;
}