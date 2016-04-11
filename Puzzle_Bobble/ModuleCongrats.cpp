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


ModuleCongrats::ModuleCongrats()
{
	congrats = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleCongrats::~ModuleCongrats()
{}

bool ModuleCongrats::Start()
{
	graphics = App->textures->Load("congrats.png");
	level_music = App->audio->Load("SinglePlayerMusic.ogg");

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	return true;
}

update_status ModuleCongrats::Update()
{
	App->render->Blit(graphics, 0, 0, &congrats);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->congratulations, App->menu_screen, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleCongrats::CleanUp()
{
	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);
	return true;
}