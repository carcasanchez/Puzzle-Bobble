#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleBoard.h"

#include "ModuleSphere.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

Particle::Particle()
{};

ModuleSphere::ModuleSphere()
{
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
		active[i] = nullptr;
}

ModuleSphere::~ModuleSphere()
{}

// Load assets
bool ModuleSphere::Start()
{

	for (uint i = 0; i < MAX_EXPLOSIONS; ++i)
		active_explosion[i] = nullptr;

	
	//////////////////////////////////////Collision scenary/////////////////////////////////////////////

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

	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleSphere::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		Sphere* s = active[i];

		if (s == nullptr)
			continue;

		if (s->Update() == false  || (s->speed.y>0 && s->position.y>SCREEN_HEIGHT*SCREEN_SIZE))
		{
			delete s;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= s->born)
		{
			App->render->Blit(graphics, s->position.x, s->position.y, &(s->idle.GetCurrentFrame()));
			if (s->fx_played == false)
			{
				s->fx_played = true;
			
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

	return UPDATE_CONTINUE;
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
	s->collider = App->collision->AddCollider(SDL_Rect{0, 0, 12, 12 }, col_type, this);
	s->collider->SetPos(310, 370);
	active[last_sphere++] = s;
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
	active[last_sphere++] = s;
	s->board_index = b_index;
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
			
			
			p->position.x = sphere->position.x-9;
			p->position.y = sphere->position.y-9;
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

	if (collider!=nullptr)
		collider->SetPos(position.x/2 +2 , position.y/2 +2);


	return ret;
}
void ModuleSphere::OnCollision(Collider* c1, Collider* c2)
{

	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{

			if (c2->type == COLLIDER_LATERAL_WALL)
				active[i]->speed.x *= -1;

			else if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_SPHERE) && active[i]->speed.y != 0)
			{
				active[i]->speed.x = 0;
				active[i]->speed.y = 0;
				App->board->CheckPosition(active[last_sphere-1]);
				//todo

				allahu_list.push_back(active[i]);
				active[i]->checked = true;
				active[i]->CheckBobble();
				
				if (allahu_list.n_elements >= 3)
				{
					check_down = true;
					for (i = 0; i < allahu_list.n_elements; i++)
					{
						allahu_list[i]->doomed = true;
					
						App->board->board[allahu_list[i]->board_index].Empty = true;	
					}

				}

				for (unsigned int i = 0; i < last_sphere; i++)
				{
					if (active[i] == nullptr)
						continue;
					if (active[i]->checked == true){
						active[i]->checked = false;
					}
					
					if (active[i]->doomed == true)
					{

						active[i]->collider->to_delete=true;
					    AddExplosion(active[i]);
						active[i]->collider = nullptr;
						active[i]=nullptr;
					}
				}
				allahu_list.clear();
				
				if (check_down == true){
					for (int i = 0; i < App->spheres->last_sphere; i++){
						if (active[i] == nullptr)
							continue;
						if (App->spheres->active[i]->board_index < 8){
							allahu_list.push_back(active[i]);
						}
					}

					for (int i = 0; i < allahu_list.size(); i++){
						if (allahu_list[i]->checked == false){
							allahu_list[i]->checked = true;
							allahu_list[i]->CheckBobbleDown();

						}
					}
					for (int i = App->spheres->last_sphere; i > 0; i--){
						if (active[i] == nullptr || active[i]->collider == nullptr)
							continue;
						if (App->spheres->active[i]->checked == false){
							active[i]->collider->to_delete = true; 
							active[i]->collider = nullptr;
							active[i]->speed.y = 7.0f;
							App->board->board[active[i]->board_index].Empty = true;
							
						}
					}
					for (unsigned int i = 0; i < App->spheres->last_sphere; i++)
					{
						if (active[i] == nullptr)
							continue;
						if (active[i]->checked == true){
							active[i]->checked = false;
						}
					}
					allahu_list.clear();
					check_down = false;
				}

				if (App->player->mystate == POSTUPDATE){
					App->player->mystate = PREUPDATE;
					next_sphere = true;
				}
			}	
		}
	}
}

void Sphere::CheckBobble(){
	
	unsigned int i;

	for (i = 0; i < App->spheres->last_sphere; i++)
	{
		if (App->spheres->active[i] == nullptr)
			continue;
		if (position.DistanceTo(App->spheres->active[i]->position)<= 18*SCREEN_SIZE  && sphere_color == App->spheres->active[i]->sphere_color && App->spheres->active[i]->checked == false)
		{
			App->spheres->active[i]->checked = true;
			App->spheres->allahu_list.push_back(App->spheres->active[i]);
			App->spheres->active[i]->CheckBobble();
		}
	}
}


void Sphere::CheckBobbleDown(){
	unsigned int i;

	for (i = 0; i < App->spheres->last_sphere; i++){
		if (App->spheres->active[i] == nullptr)
			continue;
		if (position.DistanceTo(App->spheres->active[i]->position) <= 18 * SCREEN_SIZE  && App->spheres->active[i]->checked == false)
		{
			App->spheres->active[i]->checked = true;
			App->spheres->bobble_down.push_back(App->spheres->active[i]);
			App->spheres->active[i]->CheckBobbleDown();
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