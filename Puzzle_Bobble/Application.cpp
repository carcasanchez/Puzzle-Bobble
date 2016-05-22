#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel_1.h"
#include "ModuleStartScreen.h"
#include "ModuleCongrats.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleSphere.h"
#include "ModuleBoard.h"
#include "ModuleGameOver.h"
#include "UserInterface.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = menu_screen = new ModuleStartScreen();
	modules[i++] = level_1 = new ModuleLevel_1();
	modules[i++] = congratulations = new ModuleCongrats();
	modules[i++] = game_over = new ModuleGameOver();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = spheres = new ModuleSphere();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = board = new ModuleBoard();
	modules[i++] = UI = new ModuleUserInterface();
	modules[i++] = fade = new ModuleFadeToBlack();

}	

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	App->level_1->Disable();
	App->congratulations->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->game_over->Disable();
	App->UI->Disable();


	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		if (modules[i]->IsEnabled())
		ret = modules[i]->PreUpdate();
		else{ UPDATE_CONTINUE; }

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		if (modules[i]->IsEnabled())
		ret = modules[i]->Update();
		else{ UPDATE_CONTINUE; }

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		if (modules[i]->IsEnabled())
		ret = modules[i]->PostUpdate();
		else{ UPDATE_CONTINUE; }

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}