#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleBoard.h"

#include "ModuleSphere.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"
#include <time.h>
#include <stdlib.h> 
Particle::Particle()
{};

ModuleSphere::ModuleSphere()
{
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		active_right[i] = nullptr;
		active_left[i] = nullptr;
	}
}

ModuleSphere::~ModuleSphere()
{}

// Load assets
bool ModuleSphere::Start()
{

	for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
		active_explosion[i] = nullptr;


	//////////////////////////////////////Collision scenary/////////////////////////////////////////////

	//RIGHT PLAYER
	App->collision->AddCollider(SDL_Rect{ 162, 15, 12, 194 }, COLLIDER_LATERAL_WALL);	//Left
	App->collision->AddCollider(SDL_Rect{ 303, 16, 8, 194 }, COLLIDER_LATERAL_WALL);	//Right 
	App->collision->AddCollider(SDL_Rect{ 165, 16, 144, 8 }, COLLIDER_WALL);			//Top

	//LEFT PLAYER
	App->collision->AddCollider(SDL_Rect{ 144, 24, 8, 194 }, COLLIDER_LATERAL_WALL);	//Right 136
	App->collision->AddCollider(SDL_Rect{ 7, 24, 8, 194 }, COLLIDER_LATERAL_WALL);		//Left
	App->collision->AddCollider(SDL_Rect{ 7, 16, 144, 8 }, COLLIDER_WALL);				//Top

	///////////////////////////////////////////////////////////////////////////////////
	LOG("Loading particles");
	graphics = App->textures->Load("Game/Bobbles.png");


	spheres[0].idle.PushBack({ 11, 16, 16, 16 });
	spheres[0].idle.PushBack({ 31, 16, 16, 16 });
	spheres[0].idle.PushBack({ 51, 16, 16, 16 });
	spheres[0].idle.PushBack({ 11, 16, 16, 16 });

	spheres[0].idle.loop = false;
	spheres[0].idle.speed = 0.3f;

	spheres[0].anim.PushBack({ 71, 16, 16, 16 });
	spheres[0].anim.PushBack({ 92, 16, 16, 16 });
	spheres[0].anim.PushBack({ 112, 16, 16, 16 });
	spheres[0].anim.PushBack({ 132, 16, 16, 16 });
	spheres[0].anim.PushBack({ 152, 16, 16, 16 });
	spheres[0].anim.PushBack({ 172, 16, 16, 16 });
	spheres[0].anim.loop = false;
	spheres[0].anim.speed = 0.3f;

	monster_blue.anim.PushBack({ 462, 15, 20, 19 });
	monster_blue.anim.PushBack({ 486, 15, 20, 19 });
	monster_blue.anim.PushBack({ 510, 15, 20, 19 });
	monster_blue.anim.PushBack({ 534, 15, 20, 19 });
	monster_blue.anim.PushBack({ 534, 15, 20, 19 });
	monster_blue.anim.speed = 0.1f;
	monster_blue.anim.loop = true;

	explosion_blue.anim.PushBack({ 198, 8, 32, 31 });
	explosion_blue.anim.PushBack({ 231, 8, 32, 31 });
	explosion_blue.anim.PushBack({ 264, 8, 32, 31 });
	explosion_blue.anim.PushBack({ 297, 8, 32, 31 });
	explosion_blue.anim.PushBack({ 330, 8, 32, 31 });
	explosion_blue.anim.PushBack({ 363, 8, 32, 31 });
	explosion_blue.anim.PushBack({ 396, 8, 32, 31 });
	explosion_blue.anim.loop = false;
	explosion_blue.anim.speed = 0.2f;

	spheres[0].lost.PushBack({ 11, 224, 16, 16 });
	spheres[0].lost.PushBack({ 31, 224, 16, 16 });
	spheres[0].lost.PushBack({ 51, 224, 16, 16 });
	spheres[0].lost.PushBack({ 11, 224, 16, 16 });

	spheres[0].sphere_color = BLUE;

	/////////////////////////////

	spheres[1].idle.PushBack({ 11, 42, 16, 16 });
	spheres[1].idle.PushBack({ 31, 42, 16, 16 });
	spheres[1].idle.PushBack({ 51, 42, 16, 16 });
	spheres[1].idle.PushBack({ 11, 42, 16, 16 });

	spheres[1].idle.loop = false;
	spheres[1].idle.speed = 0.3f;

	spheres[1].anim.PushBack({ 71, 42, 16, 16 });
	spheres[1].anim.PushBack({ 92, 42, 16, 16 });
	spheres[1].anim.PushBack({ 112, 42, 16, 16 });
	spheres[1].anim.PushBack({ 132, 42, 16, 16 });
	spheres[1].anim.PushBack({ 152, 42, 16, 16 });
	spheres[1].anim.PushBack({ 172, 42, 16, 16 });
	spheres[1].anim.loop = false;
	spheres[1].anim.speed = 0.3f;

	explosion_gray.anim.PushBack({ 198, 40, 32, 31 });
	explosion_gray.anim.PushBack({ 231, 40, 32, 31 });
	explosion_gray.anim.PushBack({ 264, 40, 32, 31 });
	explosion_gray.anim.PushBack({ 297, 40, 32, 31 });
	explosion_gray.anim.PushBack({ 330, 40, 32, 31 });
	explosion_gray.anim.PushBack({ 363, 40, 32, 31 });
	explosion_gray.anim.PushBack({ 396, 40, 32, 31 });
	explosion_gray.anim.speed = 0.2f;
	explosion_gray.anim.loop = false;

	monster_gray.anim.PushBack({ 462, 46, 20, 19 });
	monster_gray.anim.PushBack({ 486, 46, 20, 19 });
	monster_gray.anim.PushBack({ 510, 46, 20, 19 });
	monster_gray.anim.PushBack({ 534, 46, 20, 19 });
	monster_gray.anim.speed = 0.1f;
	monster_gray.anim.loop = true;

	spheres[1].lost.PushBack({ 71, 224, 16, 16 });
	spheres[1].lost.PushBack({ 91, 224, 16, 16 });
	spheres[1].lost.PushBack({ 111, 224, 16, 16 });
	spheres[1].lost.PushBack({ 71, 224, 16, 16 });

	spheres[1].sphere_color = GRAY;


	//////////////////////////////
	spheres[2].idle.PushBack({ 11, 68, 16, 16 });

	spheres[2].idle.loop = false;
	spheres[2].idle.speed = 0.3f;

	spheres[2].anim.PushBack({ 71, 68, 16, 16 });
	spheres[2].anim.PushBack({ 92, 68, 16, 16 });
	spheres[2].anim.PushBack({ 112, 68, 16, 16 });
	spheres[2].anim.PushBack({ 132, 68, 16, 16 });
	spheres[2].anim.PushBack({ 152, 68, 16, 16 });
	spheres[2].anim.PushBack({ 172, 68, 16, 16 });
	spheres[2].anim.loop = false;
	spheres[2].anim.speed = 0.3f;

	explosion_red.anim.PushBack({ 198, 72, 32, 31 });
	explosion_red.anim.PushBack({ 231, 72, 32, 31 });
	explosion_red.anim.PushBack({ 264, 72, 32, 31 });
	explosion_red.anim.PushBack({ 297, 72, 32, 31 });
	explosion_red.anim.PushBack({ 330, 72, 32, 31 });
	explosion_red.anim.PushBack({ 363, 72, 32, 31 });
	explosion_red.anim.PushBack({ 396, 72, 32, 31 });
	explosion_red.anim.speed = 0.2f;
	explosion_red.anim.loop = false;

	monster_red.anim.PushBack({ 462, 76, 20, 19 });
	monster_red.anim.PushBack({ 486, 76, 20, 19 });
	monster_red.anim.PushBack({ 510, 76, 20, 19 });
	monster_red.anim.PushBack({ 534, 76, 20, 19 });
	monster_red.anim.speed = 0.1f;
	monster_red.anim.loop = true;


	spheres[2].lost.PushBack({ 11, 250, 16, 16 });


	spheres[2].sphere_color = RED;

	////////////////////
	spheres[3].idle.PushBack({ 11, 94, 16, 16 });
	spheres[3].idle.PushBack({ 31, 94, 16, 16 });
	spheres[3].idle.PushBack({ 51, 94, 16, 16 });
	spheres[3].idle.PushBack({ 11, 94, 16, 16 });

	spheres[3].idle.loop = false;
	spheres[3].idle.speed = 0.5f;

	spheres[3].anim.PushBack({ 71, 94, 16, 16 });
	spheres[3].anim.PushBack({ 92, 94, 16, 16 });
	spheres[3].anim.PushBack({ 112, 94, 16, 16 });
	spheres[3].anim.PushBack({ 132, 94, 16, 16 });
	spheres[3].anim.PushBack({ 152, 94, 16, 16 });
	spheres[3].anim.PushBack({ 172, 94, 16, 16 });
	spheres[3].anim.loop = false;
	spheres[3].anim.speed = 0.3f;

	explosion_yellow.anim.PushBack({ 198, 104, 32, 31 });
	explosion_yellow.anim.PushBack({ 231, 104, 32, 31 });
	explosion_yellow.anim.PushBack({ 264, 104, 32, 31 });
	explosion_yellow.anim.PushBack({ 297, 104, 32, 31 });
	explosion_yellow.anim.PushBack({ 330, 104, 32, 31 });
	explosion_yellow.anim.PushBack({ 363, 104, 32, 31 });
	explosion_yellow.anim.PushBack({ 396, 104, 32, 31 });
	explosion_yellow.anim.speed = 0.2f;
	explosion_yellow.anim.loop = false;

	monster_yellow.anim.PushBack({ 462, 106, 20, 19 });
	monster_yellow.anim.PushBack({ 486, 106, 20, 19 });
	monster_yellow.anim.PushBack({ 510, 106, 20, 19 });
	monster_yellow.anim.PushBack({ 534, 106, 20, 19 });
	monster_yellow.anim.speed = 0.1f;
	monster_yellow.anim.loop = true;

	spheres[3].lost.PushBack({ 71, 250, 16, 16 });
	spheres[3].lost.PushBack({ 91, 250, 16, 16 });
	spheres[3].lost.PushBack({ 111, 250, 16, 16 });
	spheres[3].lost.PushBack({ 71, 250, 16, 16 });

	spheres[3].sphere_color = YELLOW;
	///////////////////////////////////////////

	spheres[4].idle.PushBack({ 11, 120, 16, 16 });
	spheres[4].idle.PushBack({ 31, 120, 16, 16 });
	spheres[4].idle.PushBack({ 51, 120, 16, 16 });
	spheres[4].idle.PushBack({ 11, 120, 16, 16 });

	spheres[4].idle.loop = false;
	spheres[4].idle.speed = 0.3f;

	spheres[4].anim.PushBack({ 71, 120, 16, 16 });
	spheres[4].anim.PushBack({ 92, 120, 16, 16 });
	spheres[4].anim.PushBack({ 112, 120, 16, 16 });
	spheres[4].anim.PushBack({ 132, 120, 16, 16 });
	spheres[4].anim.PushBack({ 152, 120, 16, 16 });
	spheres[4].anim.PushBack({ 172, 120, 16, 16 });
	spheres[4].anim.loop = false;
	spheres[4].anim.speed = 0.3f;

	explosion_green.anim.PushBack({ 198, 136, 32, 31 });
	explosion_green.anim.PushBack({ 231, 136, 32, 31 });
	explosion_green.anim.PushBack({ 264, 136, 32, 31 });
	explosion_green.anim.PushBack({ 297, 136, 32, 31 });
	explosion_green.anim.PushBack({ 330, 136, 32, 31 });
	explosion_green.anim.PushBack({ 363, 136, 32, 31 });
	explosion_green.anim.PushBack({ 396, 136, 32, 31 });
	explosion_green.anim.loop = false;
	explosion_green.anim.speed = 0.2f;

	monster_green.anim.PushBack({ 462, 137, 20, 19 });
	monster_green.anim.PushBack({ 486, 137, 20, 19 });
	monster_green.anim.PushBack({ 510, 137, 20, 19 });
	monster_green.anim.PushBack({ 534, 137, 20, 19 });
	monster_green.anim.speed = 0.1f;
	monster_green.anim.loop = true;

	spheres[4].lost.PushBack({ 11, 224, 16, 16 });
	spheres[4].lost.PushBack({ 31, 224, 16, 16 });
	spheres[4].lost.PushBack({ 51, 224, 16, 16 });
	spheres[4].lost.PushBack({ 11, 224, 16, 16 });

	spheres[4].sphere_color = GREEN;

	/////////////////////////////////

	spheres[5].idle.PushBack({ 11, 146, 16, 16 });
	spheres[5].idle.PushBack({ 31, 146, 16, 16 });
	spheres[5].idle.PushBack({ 51, 146, 16, 16 });
	spheres[5].idle.PushBack({ 11, 146, 16, 16 });

	spheres[5].idle.loop = false;
	spheres[5].idle.speed = 0.3f;

	spheres[5].anim.PushBack({ 71, 146, 16, 16 });
	spheres[5].anim.PushBack({ 92, 146, 16, 16 });
	spheres[5].anim.PushBack({ 112, 146, 16, 16 });
	spheres[5].anim.PushBack({ 132, 146, 16, 16 });
	spheres[5].anim.PushBack({ 152, 146, 16, 16 });
	spheres[5].anim.PushBack({ 172, 146, 16, 16 });
	spheres[5].anim.loop = false;
	spheres[5].anim.speed = 0.3f;

	explosion_black.anim.PushBack({ 198, 168, 32, 31 });
	explosion_black.anim.PushBack({ 231, 168, 32, 31 });
	explosion_black.anim.PushBack({ 264, 168, 32, 31 });
	explosion_black.anim.PushBack({ 297, 168, 32, 31 });
	explosion_black.anim.PushBack({ 330, 168, 32, 31 });
	explosion_black.anim.PushBack({ 363, 168, 32, 31 });
	explosion_black.anim.PushBack({ 396, 168, 32, 31 });
	explosion_black.anim.loop = false;
	explosion_black.anim.speed = 0.2f;

	monster_black.anim.PushBack({ 462, 169, 20, 19 });
	monster_black.anim.PushBack({ 486, 169, 20, 19 });
	monster_black.anim.PushBack({ 510, 169, 20, 19 });
	monster_black.anim.PushBack({ 534, 169, 20, 19 });
	monster_black.anim.speed = 0.1f;
	monster_black.anim.loop = true;

	spheres[5].lost.PushBack({ 71, 276, 16, 16 });
	spheres[5].lost.PushBack({ 91, 276, 16, 16 });
	spheres[5].lost.PushBack({ 111, 276, 16, 16 });
	spheres[5].lost.PushBack({ 71, 276, 16, 16 });

	spheres[5].sphere_color = BLACK;
	/////////////////////

	spheres[6].idle.PushBack({ 11, 172, 16, 16 });
	spheres[6].idle.PushBack({ 31, 172, 16, 16 });
	spheres[6].idle.PushBack({ 51, 172, 16, 16 });
	spheres[6].idle.PushBack({ 11, 172, 16, 16 });

	spheres[6].idle.loop = false;
	spheres[6].idle.speed = 0.3f;

	spheres[6].anim.PushBack({ 71, 172, 16, 16 });
	spheres[6].anim.PushBack({ 92, 172, 16, 16 });
	spheres[6].anim.PushBack({ 112, 172, 16, 16 });
	spheres[6].anim.PushBack({ 132, 172, 16, 16 });
	spheres[6].anim.PushBack({ 152, 172, 16, 16 });
	spheres[6].anim.PushBack({ 172, 172, 16, 16 });
	spheres[6].anim.loop = false;
	spheres[6].anim.speed = 0.3f;

	explosion_orange.anim.PushBack({ 198, 200, 32, 31 });
	explosion_orange.anim.PushBack({ 231, 200, 32, 31 });
	explosion_orange.anim.PushBack({ 264, 200, 32, 31 });
	explosion_orange.anim.PushBack({ 297, 200, 32, 31 });
	explosion_orange.anim.PushBack({ 330, 200, 32, 31 });
	explosion_orange.anim.PushBack({ 363, 200, 32, 31 });
	explosion_orange.anim.PushBack({ 396, 200, 32, 31 });
	explosion_orange.anim.speed = 0.2f;
	explosion_orange.anim.loop = false;

	monster_orange.anim.PushBack({ 462, 200, 20, 19 });
	monster_orange.anim.PushBack({ 486, 200, 20, 19 });
	monster_orange.anim.PushBack({ 510, 200, 20, 19 });
	monster_orange.anim.PushBack({ 534, 200, 20, 19 });
	monster_orange.anim.speed = 0.1f;
	monster_orange.anim.loop = true;

	spheres[6].lost.PushBack({ 11, 302, 16, 16 });
	spheres[6].lost.PushBack({ 31, 302, 16, 16 });
	spheres[6].lost.PushBack({ 51, 302, 16, 16 });
	spheres[6].lost.PushBack({ 11, 302, 16, 16 });


	spheres[6].sphere_color = ORANGE;

	///////////////////////

	spheres[7].idle.PushBack({ 11, 198, 16, 16 });
	spheres[7].idle.PushBack({ 31, 198, 16, 16 });
	spheres[7].idle.PushBack({ 51, 198, 16, 16 });
	spheres[7].idle.PushBack({ 11, 198, 16, 16 });

	spheres[7].idle.loop = false;
	spheres[7].idle.speed = 0.3f;

	spheres[7].anim.PushBack({ 71, 198, 16, 16 });
	spheres[7].anim.PushBack({ 92, 198, 16, 16 });
	spheres[7].anim.PushBack({ 112, 198, 16, 16 });
	spheres[7].anim.PushBack({ 132, 198, 16, 16 });
	spheres[7].anim.PushBack({ 152, 198, 16, 16 });
	spheres[7].anim.PushBack({ 172, 198, 16, 16 });
	spheres[7].anim.loop = false;
	spheres[7].anim.speed = 0.3f;

	explosion_violet.anim.PushBack({ 198, 232, 32, 31 });
	explosion_violet.anim.PushBack({ 231, 232, 32, 31 });
	explosion_violet.anim.PushBack({ 264, 232, 32, 31 });
	explosion_violet.anim.PushBack({ 297, 232, 32, 31 });
	explosion_violet.anim.PushBack({ 330, 232, 32, 31 });
	explosion_violet.anim.PushBack({ 363, 232, 32, 31 });
	explosion_violet.anim.PushBack({ 396, 232, 32, 31 });
	explosion_violet.anim.speed = 0.2f;
	explosion_violet.anim.loop = false;

	monster_violet.anim.PushBack({ 462, 230, 20, 19 });
	monster_violet.anim.PushBack({ 486, 230, 20, 19 });
	monster_violet.anim.PushBack({ 510, 230, 20, 19 });
	monster_violet.anim.PushBack({ 534, 230, 20, 19 });
	monster_violet.anim.speed = 0.1f;
	monster_violet.anim.loop = true;

	spheres[7].lost.PushBack({ 71, 302, 16, 16 });
	spheres[7].lost.PushBack({ 91, 302, 16, 16 });
	spheres[7].lost.PushBack({ 111, 302, 16, 16 });
	spheres[7].lost.PushBack({ 71, 302, 16, 16 });

	spheres[7].sphere_color = VIOLET;

	return true;


}

// Unload assets
bool ModuleSphere::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	//LEFT
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active_left[i] != nullptr)
		{
			delete active_left[i];
			active_left[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_UNACTIVE_SPHERES; i++)
	{
		delete unactive_left[i];
		unactive_left[i] = nullptr;
		delete unactive_right[i];
		unactive_right[i] = nullptr;
	}

	//RIGHT
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active_right[i] != nullptr)
		{
			delete active_right[i];
			active_right[i] = nullptr;
			
		}
	}
	return true;
}

// Update: draw background
update_status ModuleSphere::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			Sphere* s_l = active_left[i];
			Sphere* s_r = active_right[i];

			if (s_l != nullptr)
			if (s_l->Update() == false || (s_l->speed.y>0 && s_l->position.y>SCREEN_HEIGHT*SCREEN_SIZE))
			{
				delete s_l;
				active_left[i] = nullptr;
			}
			else if (SDL_GetTicks() >= s_l->born)
			{
				int random_time_l = rand() % 100;
				if (random_time_l % 5 == 0)
				{
					if (s_l->idle.Finished())
					{
						s_l->idle.Reset();
					}
				}
				App->render->Blit(graphics, s_l->position.x, s_l->position.y, &(s_l->idle.GetCurrentFrame()));
				if (s_l->fx_played == false)
				{
					s_l->fx_played = true;
				}
			}


			if (s_r != nullptr)
			if (s_r->Update() == false || (s_r->speed.y > 0 && s_r->position.y > SCREEN_HEIGHT*SCREEN_SIZE))
			{
				delete s_r;
				active_right[i] = nullptr;
			}
			else if (SDL_GetTicks() >= s_r->born)
			{
				int random_time_r = rand() % 100;
				if (random_time_r % 5 == 0)
				{
					if (s_r->idle.Finished())
					{
						s_r->idle.Reset();
					}
				}
				App->render->Blit(graphics, s_r->position.x, s_r->position.y, &(s_r->idle.GetCurrentFrame()));
				if (s_r->fx_played == false)
				{
					s_r->fx_played = true;
				}
			}
		}


		for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
		{
			Particle* p = active_explosion[i];

			if (p == nullptr)
				continue;

			if (p->Update() == false)
			{
				delete p;
				active_explosion[i] = nullptr;
				continue;
			}

			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		}

		for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
		{
			Particle* p = active_monsters[i];

			if (p == nullptr)
				continue;

			if (p->position.y >SCREEN_WIDTH*SCREEN_SIZE)
			{
				delete p;
				active_monsters[i] = nullptr;
				continue;
			}

			p->speed.y += 1;

			p->position.x += p->speed.x;
			p->position.y += p->speed.y;

			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		}

		currentTime_left = SDL_GetTicks();
		currentTime_right = SDL_GetTicks();

		return UPDATE_CONTINUE;
	}
}

void ModuleSphere::AddSphere(const Sphere& sphere, int x, int y, COLLIDER_TYPE col_type, Uint32 delay)
{
	Sphere* s = new Sphere(sphere);
	s->born = SDL_GetTicks() + delay;
	s->position.x = x;
	s->position.y = y;
	s->speed.y = 0;
	s->speed.x = 0;
	s->sphere_color = sphere.sphere_color;
	s->collider = App->collision->AddCollider(SDL_Rect{ 0, 0, 12, 12 }, col_type, this);
	s->collider->SetPos(s->position.x / 2 + 2, s->position.y / 2 + 2);
	if (s->position.x >= 160 * SCREEN_SIZE){ active_right[last_sphere_right++] = s; }
	else{ active_left[last_sphere_left++] = s; }

}
void ModuleSphere::SetSphere(const Sphere& sphere, int x, int y, int b_index, COLLIDER_TYPE col_type, Uint32 delay)
{
	Sphere* s = new Sphere(sphere);
	s->born = SDL_GetTicks() + delay;
	s->position.x = x;
	s->position.y = y;
	s->sphere_color = sphere.sphere_color;
	s->collider = App->collision->AddCollider(SDL_Rect{ 0, 0, 12, 12 }, col_type, this);
	s->collider->SetPos(x, y);
	s->pos_board.Empty = false;
	s->board_index = b_index;
	if (s->position.x >= 160 * SCREEN_SIZE)
	{
		active_right[last_sphere_right++] = s;
	}
	else
	{
		active_left[last_sphere_left++] = s;
	}
}

void ModuleSphere::AddExplosion(const Sphere* sphere)
{
	for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
	{
		if (active_explosion[i] == nullptr)
		{
			Particle* p = nullptr;

			switch (sphere->sphere_color)
			{
			case BLUE:
				p = new Particle(explosion_blue);
				break;

			case RED:
				p = new Particle(explosion_red);
				break;

			case GREEN:
				p = new Particle(explosion_green);
				break;

			case ORANGE:
				p = new Particle(explosion_orange);
				break;

			case VIOLET:
				p = new Particle(explosion_violet);
				break;

			case BLACK:
				p = new Particle(explosion_black);
				break;

			case GRAY:
				p = new Particle(explosion_gray);
				break;

			case YELLOW:
				p = new Particle(explosion_yellow);
				break;
			}


			p->position.x = sphere->position.x - 9;
			p->position.y = sphere->position.y - 9;
			p->to_sphere = sphere;
			active_explosion[i] = p;
			break;
		}
	}

}


void ModuleSphere::AddMonster(const Sphere* sphere)
{

	srand(time(NULL));
	int random = 0;
	random = rand() % 2;

	for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
	{
		if (active_monsters[i] == nullptr)
		{
			Particle* p = nullptr;

			switch (sphere->sphere_color)
			{
			case BLUE:
				p = new Particle(monster_blue);
				break;

			case RED:
				p = new Particle(monster_red);
				break;

			case GREEN:
				p = new Particle(monster_green);
				break;

			case ORANGE:
				p = new Particle(monster_orange);
				break;

			case VIOLET:
				p = new Particle(monster_violet);
				break;

			case BLACK:
				p = new Particle(monster_black);
				break;

			case GRAY:
				p = new Particle(monster_gray);
				break;

			case YELLOW:
				p = new Particle(monster_yellow);
				break;
			}

			if (random == 0)
				p->speed.x = -1;
			else p->speed.x = 1;

			p->speed.y = -8;
			p->position.x = sphere->position.x - 9;
			p->position.y = sphere->position.y - 9;
			p->to_sphere = sphere;
			active_monsters[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Sphere::Sphere()
{
	position.SetToZero();
	speed.SetToZero();
}

Sphere::Sphere(const Sphere& s) :
idle(s.idle), position(s.position), speed(s.speed),
fx(s.fx), born(s.born)
{}

bool Sphere::Update()
{
	bool ret = true;


	position.x += speed.x * 2;
	position.y += speed.y * 2;

	if (collider != nullptr)
		collider->SetPos(position.x / 2 + 2, position.y / 2 + 2);

	
	return ret;
}
void ModuleSphere::OnCollision(Collider* c1, Collider* c2)
{
	//LEFT
	if (c1->type == COLLIDER_SPHERE_LEFT)
	{
		for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			if (active_left[i] != nullptr && active_left[i]->collider == c1)
			{

				if (c2->type == COLLIDER_LATERAL_WALL&& currentTime_left - lastTime_left > 200){
					active_left[i]->speed.x *= -1;
					lastTime_left = currentTime_left;
				}

				else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE_LEFT) && active_left[i]->speed.y != 0)
				{
					active_left[i]->speed.x = 0;
					active_left[i]->speed.y = 0;
					App->board->CheckPositionLeft(active_left[last_sphere_left - 1]);
					//todo
					if (App->player->bobblesFromExtra == false){
						allahu_list_left.push_back(active_left[i]);
						active_left[i]->checked = true;
						active_left[i]->CheckBobbleLeft();

						if (allahu_list_left.n_elements >= 3)
						{
							Mix_PlayChannel(-1, App->audio->explosion, 0);
							check_down_left = true;
							App->player->b_destroyed_left += allahu_list_left.n_elements - 3;
							for (i = 0; i < allahu_list_left.n_elements; i++)
							{
								allahu_list_left[i]->doomed = true;
								App->board->board_left[allahu_list_left[i]->board_index]->Empty = true;
								unactive_left[unactive_counter_left++] = allahu_list_left[i];
							}

						}

						for (unsigned int i = 0; i < last_sphere_left; i++)
						{
							if (active_left[i] == nullptr)
								continue;
							if (active_left[i]->checked == true){
								active_left[i]->checked = false;
							}

							if (active_left[i]->doomed == true)
							{

								active_left[i]->collider->to_delete = true;
								AddExplosion(active_left[i]);
								AddMonster(active_left[i]);
								active_left[i]->collider = nullptr;
								active_left[i] = nullptr;
							}
						}
						
						allahu_list_left.clear();

						if (check_down_left == true){
							for (int i = 0; i < App->spheres->last_sphere_left; i++)
							{
								if (active_left[i] == nullptr)
									continue;
								if (App->board->counter_left % 2 == 0)
								{
									if (App->spheres->active_left[i]->board_index < 8)
									{
										allahu_list_left.push_back(active_left[i]);
									}
								}
								else{
									if (App->spheres->active_left[i]->board_index < 7)
									{
										allahu_list_left.push_back(active_left[i]);
									}
								}

							}
							for (int i = 0; i < allahu_list_left.size(); i++){
								if (allahu_list_left[i]->checked == false){
									allahu_list_left[i]->checked = true;
									allahu_list_left[i]->CheckBobbleDownLeft();

								}
							}
							for (int i = App->spheres->last_sphere_left; i >= 0; i--)
							{
								if (active_left[i] == nullptr || active_left[i]->collider == nullptr)
									continue;
								if (App->spheres->active_left[i]->checked == false){
									active_left[i]->collider->to_delete = true;
									active_left[i]->collider = nullptr;
									active_left[i]->speed.y = 7.0f;
									App->board->board_left[active_left[i]->board_index]->Empty = true;
									App->player->b_destroyed_left++;
								}
							}
							for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++)
							{
								if (active_left[i] == nullptr)
									continue;
								if (active_left[i]->checked == true)
								{
									active_left[i]->checked = false;
								}
							}
							allahu_list_left.clear();
							check_down_left = false;
						}
					}

					if (App->player->mystate == POSTUPDATE && App->player2->b_destroyed_right == 0)
					{
						App->player->mystate = PREUPDATE;
						next_sphere_left = true;
						App->player->bobblesFromExtra = false;

						if (App->player->booblesGoDown_left == App->player->booblesCounterDown_left)
						{
							App->board->BoardDownLeft(App->board->counter_left);
							App->player->booblesCounterDown_left = 0;
						}
					}
					if (App->player2->b_destroyed_right > 0)
					{
						App->player->bobblesFromExtra = true;
						App->spheres->ExtraBallsLeft();
						App->player2->b_destroyed_right--;
					}
				}
			}
		}
	}

	else if (c1->type == COLLIDER_SPHERE_RIGHT){
		//RIGHT
		for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			if (active_right[i] != nullptr && active_right[i]->collider == c1)
			{

				if (c2->type == COLLIDER_LATERAL_WALL&& currentTime_right - lastTime_right > 200){
					active_right[i]->speed.x *= -1;
					lastTime_right = currentTime_right;
				}

				else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE_RIGHT) && active_right[i]->speed.y != 0)
				{
					active_right[i]->speed.x = 0;
					active_right[i]->speed.y = 0;
					App->board->CheckPositionRight(active_right[last_sphere_right - 1]);
					if (App->player2->bobblesFromExtra == false){
					allahu_list_right.push_back(active_right[i]);
					active_right[i]->checked = true;
					active_right[i]->CheckBobbleRight();

					if (allahu_list_right.n_elements >= 3)
					{
						Mix_PlayChannel(-1, App->audio->explosion, 0);
						check_down_right = true;
						App->player2->b_destroyed_right += allahu_list_right.n_elements - 3;
						for (i = 0; i < allahu_list_right.n_elements; i++)
						{
							allahu_list_right[i]->doomed = true;
							App->board->board_right[allahu_list_right[i]->board_index]->Empty = true;
							unactive_right[unactive_counter_right++] = allahu_list_right[i];
						}

					}

					for (unsigned int i = 0; i < last_sphere_right; i++)
					{
						if (active_right[i] == nullptr)
							continue;
						if (active_right[i]->checked == true){
							active_right[i]->checked = false;
						}

						if (active_right[i]->doomed == true)
						{
							active_right[i]->collider->to_delete = true;
							AddExplosion(active_right[i]);
							AddMonster(active_right[i]);
							active_right[i]->collider = nullptr;
							active_right[i] = nullptr;
						}
					}
					allahu_list_right.clear();

					if (check_down_right == true)
					{
						for (int i = 0; i < App->spheres->last_sphere_right; i++)
						{
							if (active_right[i] == nullptr)
								continue;
							if (App->spheres->active_right[i]->board_index < 8)
							{
								allahu_list_right.push_back(active_right[i]);
							}
						}

						for (int i = 0; i < allahu_list_right.size(); i++)
						{
							if (allahu_list_right[i]->checked == false)
							{
								allahu_list_right[i]->checked = true;
								allahu_list_right[i]->CheckBobbleDownRight();

							}
						}
						for (int i = App->spheres->last_sphere_right; i > 0; i--)
						{
							if (active_right[i] == nullptr || active_right[i]->collider == nullptr)
								continue;
							if (App->spheres->active_right[i]->checked == false)
							{
								active_right[i]->collider->to_delete = true;
								active_right[i]->collider = nullptr;
								active_right[i]->speed.y = 7.0f;
								App->board->board_right[active_right[i]->board_index]->Empty = true;

							}
						}
						for (unsigned int i = 0; i < App->spheres->last_sphere_right; i++)
						{
							if (active_right[i] == nullptr)
								continue;
							if (active_right[i]->checked == true){
								active_right[i]->checked = false;
							}
						}
						allahu_list_right.clear();
						check_down_right = false;
					}
				}
					if (App->player2->mystate == POSTUPDATE && App->player->b_destroyed_left == 0)
					{
						App->player2->bobblesFromExtra = false;

						App->player2->mystate = PREUPDATE;
						next_sphere_right = true;
						if (App->player2->booblesGoDown_right == App->player2->booblesCounterDown_right)
						{
							App->board->BoardDownRight(App->board->counter_right);
							App->player2->booblesCounterDown_right = 0;

						}
					}
					if (App->player->b_destroyed_left > 0)
					{
						App->player2->bobblesFromExtra = true;

						App->spheres->ExtraBallsRight();
						App->player->b_destroyed_left--;
					}
				}
			}
		}
	}
}

void Sphere::CheckBobbleLeft(){

	unsigned int i;

	for (i = 0; i < App->spheres->last_sphere_left; i++)
	{
		if (App->spheres->active_left[i] == nullptr)
			continue;
		if (position.DistanceTo(App->spheres->active_left[i]->position) <= 18 * SCREEN_SIZE  && sphere_color == App->spheres->active_left[i]->sphere_color && App->spheres->active_left[i]->checked == false)
		{
			App->spheres->active_left[i]->checked = true;
			App->spheres->allahu_list_left.push_back(App->spheres->active_left[i]);
			App->spheres->active_left[i]->CheckBobbleLeft();
		}
	}
}

void Sphere::CheckBobbleRight(){

	unsigned int i;
	for (i = 0; i < App->spheres->last_sphere_right; i++)
	{
		if (App->spheres->active_right[i] == nullptr)
			continue;
		if (position.DistanceTo(App->spheres->active_right[i]->position) <= 18 * SCREEN_SIZE  && sphere_color == App->spheres->active_right[i]->sphere_color && App->spheres->active_right[i]->checked == false)
		{
			App->spheres->active_right[i]->checked = true;
			App->spheres->allahu_list_right.push_back(App->spheres->active_right[i]);
			App->spheres->active_right[i]->CheckBobbleRight();
		}
	}
}


void Sphere::CheckBobbleDownLeft(){

	unsigned int i;
	for (i = 0; i < App->spheres->last_sphere_left; i++){
		if (App->spheres->active_left[i] == nullptr)
			continue;
		if (position.DistanceTo(App->spheres->active_left[i]->position) <= 18 * SCREEN_SIZE  && App->spheres->active_left[i]->checked == false)
		{
			App->spheres->active_left[i]->checked = true;
			App->spheres->bobble_down.push_back(App->spheres->active_left[i]);
			App->spheres->active_left[i]->CheckBobbleDownLeft();
		}
	}
}

void Sphere::CheckBobbleDownRight(){

	unsigned int i;
	for (i = 0; i < App->spheres->last_sphere_right; i++){
		if (App->spheres->active_right[i] == nullptr)
			continue;
		if (position.DistanceTo(App->spheres->active_right[i]->position) <= 18 * SCREEN_SIZE  && App->spheres->active_right[i]->checked == false)
		{
			App->spheres->active_right[i]->checked = true;
			App->spheres->bobble_down.push_back(App->spheres->active_right[i]);
			App->spheres->active_right[i]->CheckBobbleDownRight();
		}
	}
}

void ModuleSphere::ExtraBallsLeft()
{
	int random = rand() % 8;
	int random_x = (rand() % 100) + 28;
	App->spheres->AddSphere(App->spheres->spheres[random], random_x * SCREEN_SIZE, 160 * SCREEN_SIZE, COLLIDER_SPHERE_LEFT);
	App->spheres->active_left[App->spheres->last_sphere_left - 1]->speed.y = -10;
}

void ModuleSphere::ExtraBallsRight()
{
	int random = rand() % 8;
	int random_x = (rand() % 111) + 184;
	App->spheres->AddSphere(App->spheres->spheres[random], random_x * SCREEN_SIZE, 160 * SCREEN_SIZE, COLLIDER_SPHERE_RIGHT);
	App->spheres->active_right[App->spheres->last_sphere_right - 1]->speed.y = -10;
}	

bool Particle::Update()
{
	bool ret = true;
	if (anim.Finished())
		ret = false;

	return ret;
}

void Sphere::ChangeColor(Color new_color)
{
	if (sphere_color == new_color)
		return;
	
	sphere_color = new_color;



	switch (new_color)
	{
	case BLUE:
		idle = App->spheres->spheres[0].idle;
		anim = App->spheres->spheres[0].anim;
		lost = App->spheres->spheres[0].lost;
		break;

	case GRAY:
		idle = App->spheres->spheres[1].idle;
		anim = App->spheres->spheres[1].anim;
		lost = App->spheres->spheres[1].lost;
		break;

	case RED:
		idle = App->spheres->spheres[2].idle;
		anim = App->spheres->spheres[2].anim;
		lost = App->spheres->spheres[2].lost;
		break;

	case YELLOW:
		idle = App->spheres->spheres[3].idle;
		anim = App->spheres->spheres[3].anim;
		lost = App->spheres->spheres[3].lost;
		break;

	case GREEN:
		idle = App->spheres->spheres[4].idle;
		anim = App->spheres->spheres[4].anim;
		lost = App->spheres->spheres[4].lost;
		break;

	case BLACK:
		idle = App->spheres->spheres[5].idle;
		anim = App->spheres->spheres[5].anim;
		lost = App->spheres->spheres[5].lost;
		break;

	case ORANGE:
		idle = App->spheres->spheres[6].idle;
		anim = App->spheres->spheres[6].anim;
		lost = App->spheres->spheres[6].lost;
		break;

	case VIOLET:
		idle = App->spheres->spheres[7].idle;
		anim = App->spheres->spheres[7].anim;
		lost = App->spheres->spheres[7].lost;
		break;
	}


}