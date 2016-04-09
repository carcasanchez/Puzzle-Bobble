#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleLevel_1.h"
#include "ModuleStartScreen.h"
#include "SDL/include/SDL.h"

ModuleStartScreen::~ModuleStartScreen()
{}

bool ModuleStartScreen::Start()
{

	graphics = App->textures->Load("Start_Screen.png");
	level_music = App->audio->Load("Title_Demonstration.ogg"); //TODO: Solve incomplete type 
	return true;


}

update_status ModuleStartScreen::Update()
{
	App->render->Blit(graphics, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{

		App->fade->FadeToBlack(App->menu_screen, App->level_1, 1);
	}
	return UPDATE_CONTINUE;
}

bool ModuleStartScreen::CleanUp()
{
	return true;
}