#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleStartScreen.h"
#include "ModuleCongrats.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleSphere.h"

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
	modules[i++] = level_2 = new ModuleLevel_2();
	modules[i++] = congratulations = new ModuleCongrats();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = spheres = new ModuleSphere();
	modules[i++] = collision = new ModuleCollision();
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
	App->level_2->Disable();
	App->congratulations->Disable();
	App->player->Disable();

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