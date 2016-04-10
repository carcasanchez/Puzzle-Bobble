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
#include "ModuleStartScreen.h"


ModuleLevel_1::ModuleLevel_1(){}

ModuleLevel_1::~ModuleLevel_1()
{}

bool ModuleLevel_1::Start()
{
	graphics = App->textures->Load("Level1_3.png");
	level_music = App->audio->Load("SinglePlayerMusic.ogg"); 

	if (Mix_PlayMusic(level_music, -1) == -1) {
		LOG("Mix_PlayMusic: %s\n", Mix_GetError());

	}
	return true;
}

update_status ModuleLevel_1::Update()
{
	App->render->Blit(graphics, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->level_1, App->level_2, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleLevel_1::CleanUp()
{
	while (!Mix_FadeOutMusic(1000) && Mix_PlayingMusic())
		SDL_Delay(1000);

	return true;
}