/*#include "ModuleStartScreen.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"


ModuleStartScreen::~ModuleStartScreen()
{}

bool ModuleStartScreen::Init()
{

	background = App->textures->Load("level1_3.png");
	level_music = App->audio->Load("SinglePlayerMusic.ogg"); //TODO: Solve incomplete type 
	
	return true;


}

update_status ModuleStartScreen::Update()
{
	App->render->Blit(App->textures->textures[0], 0, 0, NULL);
	return UPDATE_CONTINUE;
}

bool ModuleStartScreen::CleanUp()
{
	return true;
}*/