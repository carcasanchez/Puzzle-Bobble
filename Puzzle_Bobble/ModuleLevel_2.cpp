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


ModuleLevel_2::ModuleLevel_2()
{
	level2 = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

ModuleLevel_2::~ModuleLevel_2()
{}

bool ModuleLevel_2::Start()
{
	graphics = App->textures->Load("Level3_5.png");
	level_music = App->audio->Load("SinglePlayerMusic.ogg");

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	return true;
}

update_status ModuleLevel_2::Update()
{
	App->render->Blit(graphics, 0, 0, &level2);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->level_2, App->congratulations, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleLevel_2::CleanUp()
{
	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}