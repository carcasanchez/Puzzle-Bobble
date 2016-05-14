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
#include "SDL/include/SDL_timer.h"

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
	App->collision->AddCollider(SDL_Rect{ 160, 15, 8, 194 }, COLLIDER_LATERAL_WALL);	//Right
	App->collision->AddCollider(SDL_Rect{ 304, 16, 8, 194 }, COLLIDER_LATERAL_WALL);	//Left
	App->collision->AddCollider(SDL_Rect{ 165, 16, 144, 8 }, COLLIDER_WALL);			//Top

	//LEFT PLAYER
	App->collision->AddCollider(SDL_Rect{ 144, 24, 8, 194 }, COLLIDER_LATERAL_WALL);	//Right 136
	App->collision->AddCollider(SDL_Rect{ 7, 24, 8, 194 }, COLLIDER_LATERAL_WALL);		//Left
	App->collision->AddCollider(SDL_Rect{ 7, 16, 144, 8 }, COLLIDER_WALL);				//Top

	///////////////////////////////////////////////////////////////////////////////////
	LOG("Loading particles");
	graphics = App->textures->Load("Game/Sprites.png");


	spheres[0].idle.PushBack({ 11, 196, 16, 16 });
	spheres[0].idle.PushBack({ 31, 196, 16, 16 });
	spheres[0].idle.PushBack({ 51, 196, 16, 16 });
	spheres[0].idle.PushBack({ 11, 196, 16, 16 });

	spheres[0].idle.loop = false;
	spheres[0].idle.speed = 0.3f;

	spheres[0].anim.PushBack({ 71, 196, 16, 16 });
	spheres[0].anim.PushBack({ 92, 196, 16, 16 });
	spheres[0].anim.PushBack({ 112, 196, 16, 16 });
	spheres[0].anim.PushBack({ 132, 196, 16, 16 });
	spheres[0].anim.PushBack({ 152, 196, 16, 16 });
	spheres[0].anim.PushBack({ 172, 196, 16, 16 });
	spheres[0].anim.loop = false;
	spheres[0].anim.speed = 0.3f;

	spheres[0].monster.PushBack({ 462, 195, 20, 19 });
	spheres[0].monster.PushBack({ 486, 195, 20, 19 });
	spheres[0].monster.PushBack({ 510, 195, 20, 19 });
	spheres[0].monster.PushBack({ 534, 195, 20, 19 });
	spheres[0].monster.PushBack({ 534, 195, 20, 19 });
	spheres[0].monster.speed = 0.3f;

	explosion_blue.anim.PushBack({ 198, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 231, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 264, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 297, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 330, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 363, 188, 32, 31 });
	explosion_blue.anim.PushBack({ 396, 188, 32, 31 });
	explosion_blue.anim.loop = false;
	explosion_blue.anim.speed = 0.3f;

	spheres[0].sphere_color = BLUE;

	/////////////////////////////

	spheres[1].idle.PushBack({ 11, 222, 16, 16 });
	spheres[1].idle.PushBack({ 31, 222, 16, 16 });
	spheres[1].idle.PushBack({ 51, 222, 16, 16 });
	spheres[1].idle.PushBack({ 11, 222, 16, 16 });
	spheres[1].idle.loop = false;
	spheres[1].idle.speed = 0.3f;

	spheres[1].anim.PushBack({ 71, 222, 16, 16 });
	spheres[1].anim.PushBack({ 92, 222, 16, 16 });
	spheres[1].anim.PushBack({ 112, 222, 16, 16 });
	spheres[1].anim.PushBack({ 132, 222, 16, 16 });
	spheres[1].anim.PushBack({ 152, 222, 16, 16 });
	spheres[1].anim.PushBack({ 172, 222, 16, 16 });
	spheres[1].anim.loop = false;
	spheres[1].anim.speed = 0.3f;

	explosion_gray.anim.PushBack({ 198, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 231, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 264, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 297, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 330, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 363, 220, 32, 31 });
	explosion_gray.anim.PushBack({ 396, 220, 32, 31 });
	explosion_gray.anim.speed = 0.3f;
	explosion_gray.anim.loop = false;

	spheres[1].monster.PushBack({ 462, 226, 20, 19 });
	spheres[1].monster.PushBack({ 486, 226, 20, 19 });
	spheres[1].monster.PushBack({ 510, 226, 20, 19 });
	spheres[1].monster.PushBack({ 534, 226, 20, 19 });
	spheres[1].monster.speed = 0.3f;

	spheres[1].sphere_color = GRAY;


	//////////////////////////////
	spheres[2].idle.PushBack({ 11, 248, 16, 16 });

	spheres[2].idle.loop = false;
	spheres[2].idle.speed = 0.3f;

	spheres[2].anim.PushBack({ 71, 248, 16, 16 });
	spheres[2].anim.PushBack({ 92, 248, 16, 16 });
	spheres[2].anim.PushBack({ 112, 248, 16, 16 });
	spheres[2].anim.PushBack({ 132, 248, 16, 16 });
	spheres[2].anim.PushBack({ 152, 248, 16, 16 });
	spheres[2].anim.PushBack({ 172, 248, 16, 16 });
	spheres[2].anim.loop = false;
	spheres[2].anim.speed = 0.3f;

	explosion_red.anim.PushBack({ 198, 252, 32, 31 });
	explosion_red.anim.PushBack({ 231, 252, 32, 31 });
	explosion_red.anim.PushBack({ 264, 252, 32, 31 });
	explosion_red.anim.PushBack({ 297, 252, 32, 31 });
	explosion_red.anim.PushBack({ 330, 252, 32, 31 });
	explosion_red.anim.PushBack({ 363, 252, 32, 31 });
	explosion_red.anim.PushBack({ 396, 252, 32, 31 });
	explosion_red.anim.speed = 0.3f;
	explosion_red.anim.loop = false;

	spheres[2].monster.PushBack({ 462, 256, 20, 19 });
	spheres[2].monster.PushBack({ 486, 256, 20, 19 });
	spheres[2].monster.PushBack({ 510, 256, 20, 19 });
	spheres[2].monster.PushBack({ 534, 256, 20, 19 });
	spheres[2].monster.speed = 0.3f;

	spheres[2].sphere_color = RED;

	////////////////////
	spheres[3].idle.PushBack({ 11, 274, 16, 16 });
	spheres[3].idle.PushBack({ 31, 274, 16, 16 });
	spheres[3].idle.PushBack({ 51, 274, 16, 16 });
	spheres[3].idle.PushBack({ 11, 274, 16, 16 });
	spheres[3].idle.loop = false;
	spheres[3].idle.speed = 0.3f;

	spheres[3].anim.PushBack({ 71, 274, 16, 16 });
	spheres[3].anim.PushBack({ 92, 274, 16, 16 });
	spheres[3].anim.PushBack({ 112, 274, 16, 16 });
	spheres[3].anim.PushBack({ 132, 274, 16, 16 });
	spheres[3].anim.PushBack({ 152, 274, 16, 16 });
	spheres[3].anim.PushBack({ 172, 274, 16, 16 });
	spheres[3].anim.loop = false;
	spheres[3].anim.speed = 0.3f;

	explosion_yellow.anim.PushBack({ 198, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 231, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 264, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 297, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 330, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 363, 284, 32, 31 });
	explosion_yellow.anim.PushBack({ 396, 284, 32, 31 });
	explosion_yellow.anim.speed = 0.3f;
	explosion_yellow.anim.loop = false;

	spheres[3].monster.PushBack({ 462, 286, 20, 19 });
	spheres[3].monster.PushBack({ 486, 286, 20, 19 });
	spheres[3].monster.PushBack({ 510, 286, 20, 19 });
	spheres[3].monster.PushBack({ 534, 286, 20, 19 });
	spheres[3].monster.speed = 0.3f;

	spheres[3].sphere_color = YELLOW;
	///////////////////////////////////////////

	spheres[4].idle.PushBack({ 11, 300, 16, 16 });
	spheres[4].idle.PushBack({ 31, 300, 16, 16 });
	spheres[4].idle.PushBack({ 51, 300, 16, 16 });
	spheres[4].idle.PushBack({ 11, 300, 16, 16 });

	spheres[4].idle.loop = false;
	spheres[4].idle.speed = 0.3f;

	spheres[4].anim.PushBack({ 71, 300, 16, 16 });
	spheres[4].anim.PushBack({ 92, 300, 16, 16 });
	spheres[4].anim.PushBack({ 112, 300, 16, 16 });
	spheres[4].anim.PushBack({ 132, 300, 16, 16 });
	spheres[4].anim.PushBack({ 152, 300, 16, 16 });
	spheres[4].anim.PushBack({ 172, 300, 16, 16 });
	spheres[4].anim.loop = false;
	spheres[4].anim.speed = 0.3f;

	explosion_green.anim.PushBack({ 198, 316, 32, 31 });
	explosion_green.anim.PushBack({ 231, 316, 32, 31 });
	explosion_green.anim.PushBack({ 264, 316, 32, 31 });
	explosion_green.anim.PushBack({ 297, 316, 32, 31 });
	explosion_green.anim.PushBack({ 330, 316, 32, 31 });
	explosion_green.anim.PushBack({ 363, 316, 32, 31 });
	explosion_green.anim.PushBack({ 396, 316, 32, 31 });
	explosion_green.anim.loop = false;
	explosion_green.anim.speed = 0.3f;

	spheres[4].monster.PushBack({ 462, 317, 20, 19 });
	spheres[4].monster.PushBack({ 486, 317, 20, 19 });
	spheres[4].monster.PushBack({ 510, 317, 20, 19 });
	spheres[4].monster.PushBack({ 534, 317, 20, 19 });
	spheres[4].monster.speed = 0.3f;

	spheres[4].sphere_color = GREEN;

	/////////////////////////////////

	spheres[5].idle.PushBack({ 11, 326, 16, 16 });
	spheres[5].idle.PushBack({ 31, 326, 16, 16 });
	spheres[5].idle.PushBack({ 51, 326, 16, 16 });
	spheres[5].idle.PushBack({ 11, 326, 16, 16 });

	spheres[5].idle.loop = true;
	spheres[5].idle.speed = 0.3f;

	spheres[5].anim.PushBack({ 71, 326, 16, 16 });
	spheres[5].anim.PushBack({ 92, 326, 16, 16 });
	spheres[5].anim.PushBack({ 112, 326, 16, 16 });
	spheres[5].anim.PushBack({ 132, 326, 16, 16 });
	spheres[5].anim.PushBack({ 152, 326, 16, 16 });
	spheres[5].anim.PushBack({ 172, 326, 16, 16 });
	spheres[5].anim.loop = false;
	spheres[5].anim.speed = 0.3f;

	explosion_black.anim.PushBack({ 198, 348, 32, 31 });
	explosion_black.anim.PushBack({ 231, 348, 32, 31 });
	explosion_black.anim.PushBack({ 264, 348, 32, 31 });
	explosion_black.anim.PushBack({ 297, 348, 32, 31 });
	explosion_black.anim.PushBack({ 330, 348, 32, 31 });
	explosion_black.anim.PushBack({ 363, 348, 32, 31 });
	explosion_black.anim.PushBack({ 396, 348, 32, 31 });
	explosion_black.anim.loop = false;
	explosion_black.anim.speed = 0.3f;

	spheres[5].monster.PushBack({ 462, 349, 20, 19 });
	spheres[5].monster.PushBack({ 486, 349, 20, 19 });
	spheres[5].monster.PushBack({ 510, 349, 20, 19 });
	spheres[5].monster.PushBack({ 534, 349, 20, 19 });
	spheres[5].monster.speed = 0.3f;

	spheres[5].sphere_color = BLACK;
	/////////////////////

	spheres[6].idle.PushBack({ 11, 352, 16, 16 });
	spheres[6].idle.PushBack({ 31, 352, 16, 16 });
	spheres[6].idle.PushBack({ 51, 352, 16, 16 });
	spheres[6].idle.PushBack({ 11, 352, 16, 16 });

	spheres[6].idle.loop = false;
	spheres[6].idle.speed = 0.3f;

	spheres[6].anim.PushBack({ 71, 352, 16, 16 });
	spheres[6].anim.PushBack({ 92, 352, 16, 16 });
	spheres[6].anim.PushBack({ 112, 352, 16, 16 });
	spheres[6].anim.PushBack({ 132, 352, 16, 16 });
	spheres[6].anim.PushBack({ 152, 352, 16, 16 });
	spheres[6].anim.PushBack({ 172, 352, 16, 16 });
	spheres[6].anim.loop = false;
	spheres[6].anim.speed = 0.3f;

	explosion_orange.anim.PushBack({ 198, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 231, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 264, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 297, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 330, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 363, 380, 32, 31 });
	explosion_orange.anim.PushBack({ 396, 380, 32, 31 });
	explosion_orange.anim.speed = 0.3f;
	explosion_orange.anim.loop = false;

	spheres[6].monster.PushBack({ 462, 380, 20, 19 });
	spheres[6].monster.PushBack({ 486, 380, 20, 19 });
	spheres[6].monster.PushBack({ 510, 380, 20, 19 });
	spheres[6].monster.PushBack({ 534, 380, 20, 19 });
	spheres[6].monster.speed = 0.3f;

	spheres[6].sphere_color = ORANGE;

	///////////////////////

	spheres[7].idle.PushBack({ 11, 378, 16, 16 });
	spheres[7].idle.PushBack({ 31, 378, 16, 16 });
	spheres[7].idle.PushBack({ 51, 378, 16, 16 });
	spheres[7].idle.PushBack({ 11, 378, 16, 16 });
	spheres[7].idle.loop = false;
	spheres[7].idle.speed = 0.3f;

	spheres[7].anim.PushBack({ 71, 378, 16, 16 });
	spheres[7].anim.PushBack({ 92, 378, 16, 16 });
	spheres[7].anim.PushBack({ 112, 378, 16, 16 });
	spheres[7].anim.PushBack({ 132, 378, 16, 16 });
	spheres[7].anim.PushBack({ 152, 378, 16, 16 });
	spheres[7].anim.PushBack({ 172, 378, 16, 16 });
	spheres[7].anim.loop = false;
	spheres[7].anim.speed = 0.3f;

	explosion_violet.anim.PushBack({ 198, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 231, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 264, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 297, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 330, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 363, 412, 32, 31 });
	explosion_violet.anim.PushBack({ 396, 412, 32, 31 });
	explosion_violet.anim.speed = 0.3f;
	explosion_violet.anim.loop = false;

	spheres[7].monster.PushBack({ 462, 410, 20, 19 });
	spheres[7].monster.PushBack({ 486, 410, 20, 19 });
	spheres[7].monster.PushBack({ 510, 410, 20, 19 });
	spheres[7].monster.PushBack({ 534, 410, 20, 19 });
	spheres[7].monster.speed = 0.3f;

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

		currentTime_left = SDL_GetTicks();
		currentTime_right = SDL_GetTicks();


		return UPDATE_CONTINUE;
	}
}

void ModuleSphere::AddSphere(const Sphere& sphere, int x, int y, COLLIDER_TYPE col_type, Uint32 delay)
{
	//LEFT
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

		/*for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			if (active_left[i] != nullptr && active_left[i]->collider == c1)
			{

				if (c2->type == COLLIDER_LATERAL_WALL)
					active_left[i]->speed.x *= -1;

				else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE_LEFT) && active_left[i]->speed.y != 0)
				{
					active_left[i]->speed.x = 0;
					active_left[i]->speed.y = 0;
					App->board->CheckPositionLeft(active_left[last_sphere_left - 1]);
					//todo
					check_down_left = allahu_bobble_left(i);

					if (check_down_left == true){
						boobbledown_left();

					}

					if (App->player->mystate == POSTUPDATE){
						App->player->mystate = PREUPDATE;
						next_sphere_left = true;
					}
			//		App->board->BoardDown(App->board->counter);
				
				}
			}
		}
	
	*/
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

					allahu_list_left.push_back(active_left[i]);
					active_left[i]->checked = true;
					active_left[i]->CheckBobbleLeft();

					if (allahu_list_left.n_elements >= 3)
					{
						check_down_left = true;
						for (i = 0; i < allahu_list_left.n_elements; i++)
						{
							allahu_list_left[i]->doomed = true;

							App->board->board_left[allahu_list_left[i]->board_index]->Empty = true;
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
							active_left[i]->collider = nullptr;
							active_left[i] = nullptr;
						}
					}
					allahu_list_left.clear();

					if (check_down_left == true){
						for (int i = 0; i < App->spheres->last_sphere_left; i++){
							if (active_left[i] == nullptr)
								continue;
							if (App->board->counter % 2 == 0){
								if (App->spheres->active_left[i]->board_index < 8){
									allahu_list_left.push_back(active_left[i]);
								}
							else{
									if (App->spheres->active_left[i]->board_index < 7){
										allahu_list_left.push_back(active_left[i]);
									}
								}
							}
						}
						for (int i = 0; i < allahu_list_left.size(); i++){
							if (allahu_list_left[i]->checked == false){
								allahu_list_left[i]->checked = true;
								allahu_list_left[i]->CheckBobbleDownLeft();

							}
						}
						for (int i = App->spheres->last_sphere_left; i > 0; i--){
							if (active_left[i] == nullptr || active_left[i]->collider == nullptr)
								continue;
							if (App->spheres->active_left[i]->checked == false){
								active_left[i]->collider->to_delete = true;
								active_left[i]->collider = nullptr;
								active_left[i]->speed.y = 7.0f;
								App->board->board_left[active_left[i]->board_index]->Empty = true;

							}
						}
						for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++)
						{
							if (active_left[i] == nullptr)
								continue;
							if (active_left[i]->checked == true){
								active_left[i]->checked = false;
							}
						}
						allahu_list_left.clear();
						check_down_left = false;
					}

					if (App->player->mystate == POSTUPDATE){
						App->player->mystate = PREUPDATE;
						next_sphere_left = true;
						App->board->BoardDown(App->board->counter);

					}
				}
			}
		}
	}

	else if (c1->type == COLLIDER_SPHERE_RIGHT){
		//RIGHT
	/*	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			if (active_right[i] != nullptr && active_right[i]->collider == c1)
			{

				if (c2->type == COLLIDER_LATERAL_WALL)
					active_right[i]->speed.x *= -1;

				else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE_RIGHT) && active_right[i]->speed.y != 0)
				{
					active_right[i]->speed.x = 0;
					active_right[i]->speed.y = 0;

					App->board->CheckPositionRight(active_right[last_sphere_right - 1]);
					check_down_right = allahu_bobble_right(i);

					if (check_down_right == true){
						boobbledown_right();

					}
					if (App->player2->mystate == POSTUPDATE){
						App->player2->mystate = PREUPDATE;
						next_sphere_right = true;
					}
				}
			}
		}*/
		for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		{
			if (active_right[i] != nullptr && active_right[i]->collider == c1)
			{

				if (c2->type == COLLIDER_LATERAL_WALL&& currentTime_right - lastTime_right > 1000){
					active_right[i]->speed.x *= -1;
					lastTime_right = currentTime_right;
				}

				else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE_RIGHT) && active_right[i]->speed.y != 0)
				{
					active_right[i]->speed.x = 0;
					active_right[i]->speed.y = 0;
					App->board->CheckPositionRight(active_right[last_sphere_right - 1]);
					//todo

					allahu_list_right.push_back(active_right[i]);
					active_right[i]->checked = true;
					active_right[i]->CheckBobbleRight();

					if (allahu_list_right.n_elements >= 3)
					{
						check_down_right = true;
						for (i = 0; i < allahu_list_right.n_elements; i++)
						{
							allahu_list_right[i]->doomed = true;

							App->board->board_right[allahu_list_right[i]->board_index]->Empty = true;
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
							active_right[i]->collider = nullptr;
							active_right[i] = nullptr;
						}
					}
					allahu_list_right.clear();

					if (check_down_right == true){
						for (int i = 0; i < App->spheres->last_sphere_right; i++){
							if (active_right[i] == nullptr)
								continue;
							if (App->spheres->active_right[i]->board_index < 8){
								allahu_list_right.push_back(active_right[i]);
							}
						}

						for (int i = 0; i < allahu_list_right.size(); i++){
							if (allahu_list_right[i]->checked == false){
								allahu_list_right[i]->checked = true;
								allahu_list_right[i]->CheckBobbleDownRight();

							}
						}
						for (int i = App->spheres->last_sphere_right; i > 0; i--){
							if (active_right[i] == nullptr || active_right[i]->collider == nullptr)
								continue;
							if (App->spheres->active_right[i]->checked == false){
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

					if (App->player2->mystate == POSTUPDATE){
						App->player2->mystate = PREUPDATE;
						next_sphere_right = true;
					}
				}
			}
		}
	}
}
bool ModuleSphere::allahu_bobble_left(int i){

	allahu_list_left.push_back(active_left[i]);
	active_left[i]->checked = true;
	active_left[i]->CheckBobbleLeft();
	if (allahu_list_left.n_elements >= 3)
	{
		
		for (i = 0; i < allahu_list_left.n_elements; i++)
		{
			allahu_list_left[i]->doomed = true;

			App->board->board_left[allahu_list_left[i]->board_index]->Empty = true;
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
				active_left[i]->collider = nullptr;
				active_left[i] = nullptr;
			}
		}
		allahu_list_left.clear();
		return true;
	}
	else{
		allahu_list_left.clear();

		return false;
	}
}
void ModuleSphere::boobbledown_left(){

		for (int i = 0; i < App->spheres->last_sphere_left; i++){
			if (active_left[i] == nullptr)
				continue;
			if (App->spheres->active_left[i]->board_index < 8){
				allahu_list_left.push_back(active_left[i]);
			}
		}

		for (int i = 0; i < allahu_list_left.size(); i++){
			if (allahu_list_left[i]->checked == false){
				allahu_list_left[i]->checked = true;
				allahu_list_left[i]->CheckBobbleDownLeft();

			}
		}
		for (int i = App->spheres->last_sphere_left; i > 0; i--){
			if (active_left[i] == nullptr || active_left[i]->collider == nullptr)
				continue;
			if (App->spheres->active_left[i]->checked == false){
				active_left[i]->collider->to_delete = true;
				active_left[i]->collider = nullptr;
				active_left[i]->speed.y = 7.0f;
				App->board->board_left[active_left[i]->board_index]->Empty = true;

			}
		}
		for (unsigned int i = 0; i < App->spheres->last_sphere_left; i++)
		{
			if (active_left[i] == nullptr)
				continue;
			if (active_left[i]->checked == true){
				active_left[i]->checked = false;
			}
		}
		allahu_list_left.clear();
		check_down_left = false;
	
}

bool ModuleSphere::allahu_bobble_right(int i){

	allahu_list_right.push_back(active_right[i]);
	active_right[i]->checked = true;
	active_right[i]->CheckBobbleRight();
	if (allahu_list_right.n_elements >= 3)
	{

		for (i = 0; i < allahu_list_right.n_elements; i++)
		{
			allahu_list_right[i]->doomed = true;

			App->board->board_right[allahu_list_right[i]->board_index]->Empty = true;
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
				active_right[i]->collider = nullptr;
				active_right[i] = nullptr;
			}
		}
		allahu_list_right.clear();
		return true;
	}
	else{
		allahu_list_left.clear();

		return false;
	}
}
void ModuleSphere::boobbledown_right(){

	for (int i = 0; i < App->spheres->last_sphere_right; i++){
		if (active_right[i] == nullptr)
			continue;
		if (App->spheres->active_right[i]->board_index < 8){
			allahu_list_right.push_back(active_right[i]);
		}
	}

	for (int i = 0; i < allahu_list_right.size(); i++){
		if (allahu_list_right[i]->checked == false){
			allahu_list_right[i]->checked = true;
			allahu_list_right[i]->CheckBobbleDownRight();

		}
	}
	for (int i = App->spheres->last_sphere_right; i > 0; i--){
		if (active_right[i] == nullptr || active_right[i]->collider == nullptr)
			continue;
		if (App->spheres->active_right[i]->checked == false){
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

bool Particle::Update()
{
	bool ret = true;
	if (anim.Finished())
		ret = false;

	return ret;
}