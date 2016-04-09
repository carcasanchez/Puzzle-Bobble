/* "ModuleStartScreen.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

ModuleStartScreen::ModuleStartScreen()
{
	
}

ModuleStartScreen::~ModuleStartScreen()
{}

bool ModuleStartScreen::Init()
{

	background = App->textures->Load("level1_3");
	return true;


}

update_status ModuleStartScreen::Update()
{
	return UPDATE_CONTINUE;
}*/