#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleAudio;
class ModuleFadeToBlack;
class ModuleStartScreen;
class ModuleLevel_1;
class ModuleCongrats;
class ModulePlayer;
class ModuleSphere;
class ModuleCollision;
class ModuleBoard;
class ModuleGameOver;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModuleStartScreen* menu_screen;
	ModuleLevel_1* level_1;
	ModuleCongrats* congratulations;
	ModuleGameOver* game_over;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModuleSphere* spheres;
	ModuleBoard* board;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__