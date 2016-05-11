#include "Globals.h"
#include "SDL/include/SDL.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
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
	graphics = App->textures->Load("Game/congrats.png");

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
	return true;
}