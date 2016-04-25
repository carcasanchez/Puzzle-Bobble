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
	//////////////////////////////////////Collision scenary/////////////////////////////////////////////

	App->collision->AddCollider(SDL_Rect{ 224, 24, 8, 194 }, COLLIDER_LATERAL_WALL);//Right
	App->collision->AddCollider(SDL_Rect{ 88, 24, 8, 194 }, COLLIDER_LATERAL_WALL);//Left
	App->collision->AddCollider(SDL_Rect{ 88, 16, 144, 8 }, COLLIDER_WALL);//Top
	
	///////////////////////////////////////////////////////////////////////////////////
	LOG("Loading particles");
	graphics = App->textures->Load("Sprites.png");

	spheres[0].anim.PushBack({ 12, 260, 16, 16 });
	spheres[0].anim.PushBack({ 32, 260, 16, 16 });
	spheres[0].anim.PushBack({ 52, 260, 16, 16 });
	spheres[0].anim.PushBack({ 72, 260, 16, 16 });
	spheres[0].anim.PushBack({ 92, 260, 16, 16 });
	spheres[0].anim.PushBack({ 113, 260, 16, 16 });
	spheres[0].anim.PushBack({ 133, 260, 16, 16 });
	spheres[0].anim.PushBack({ 153, 260, 16, 16 });
	spheres[0].anim.PushBack({ 173, 260, 16, 16 });
	spheres[0].anim.PushBack({ 193, 260, 16, 16 });
	spheres[0].anim.loop = false;
	spheres[0].anim.speed = 0.3f;
	spheres[0].sphere_color = BLUE;

	spheres[1].anim.PushBack({ 318, 260, 16, 16 });
	spheres[1].anim.PushBack({ 338, 260, 16, 16 });
	spheres[1].anim.PushBack({ 358, 260, 16, 16 });
	spheres[1].anim.PushBack({ 378, 260, 16, 16 });
	spheres[1].anim.PushBack({ 398, 260, 16, 16 });
	spheres[1].anim.PushBack({ 419, 260, 16, 16 });
	spheres[1].anim.PushBack({ 439, 260, 16, 16 });
	spheres[1].anim.PushBack({ 459, 260, 16, 16 });
	spheres[1].anim.PushBack({ 479, 260, 16, 16 });
	spheres[1].anim.PushBack({ 499, 260, 16, 16 });
	spheres[1].anim.loop = false;
	spheres[1].anim.speed = 0.3f;
	spheres[1].sphere_color = GREEN;


	spheres[2].anim.PushBack({ 12, 286, 16, 16 });
	spheres[2].anim.PushBack({ 32, 286, 16, 16 });
	spheres[2].anim.PushBack({ 52, 286, 16, 16 });
	spheres[2].anim.PushBack({ 72, 286, 16, 16 });
	spheres[2].anim.PushBack({ 92, 286, 16, 16 });
	spheres[2].anim.PushBack({ 113, 286, 16, 16 });
	spheres[2].anim.PushBack({ 133, 286, 16, 16 });
	spheres[2].anim.PushBack({ 153, 286, 16, 16 });
	spheres[2].anim.PushBack({ 173, 286, 16, 16 });
	spheres[2].anim.PushBack({ 193, 286, 16, 16 });
	spheres[2].anim.loop = false;
	spheres[2].anim.speed = 0.3f;
	spheres[2].sphere_color = GRAY;


	spheres[3].anim.PushBack({ 318, 286, 16, 16 });
	spheres[3].anim.PushBack({ 338, 286, 16, 16 });
	spheres[3].anim.PushBack({ 358, 286, 16, 16 });
	spheres[3].anim.PushBack({ 378, 286, 16, 16 });
	spheres[3].anim.PushBack({ 398, 286, 16, 16 });
	spheres[3].anim.PushBack({ 419, 286, 16, 16 });
	spheres[3].anim.PushBack({ 439, 286, 16, 16 });
	spheres[3].anim.PushBack({ 459, 286, 16, 16 });
	spheres[3].anim.PushBack({ 479, 286, 16, 16 });
	spheres[3].anim.PushBack({ 499, 286, 16, 16 });
	spheres[3].anim.loop = false;
	spheres[3].anim.speed = 0.3f;
	spheres[3].sphere_color = BLACK;


	spheres[4].anim.PushBack({ 12, 312, 16, 16 });
	spheres[4].anim.PushBack({ 32, 312, 16, 16 });
	spheres[4].anim.PushBack({ 92, 312, 16, 16 });
	spheres[4].anim.PushBack({ 113, 312, 16, 16 });
	spheres[4].anim.PushBack({ 133, 312, 16, 16 });
	spheres[4].anim.PushBack({ 153, 312, 16, 16 });
	spheres[4].anim.PushBack({ 173, 312, 16, 16 });
	spheres[4].anim.PushBack({ 193, 312, 16, 16 });
	spheres[4].anim.loop = false;
	spheres[4].anim.speed = 0.3f;
	spheres[4].sphere_color = RED;


	spheres[5].anim.PushBack({ 318, 312, 16, 16 });
	spheres[5].anim.PushBack({ 338, 312, 16, 16 });
	spheres[5].anim.PushBack({ 358, 312, 16, 16 });
	spheres[5].anim.PushBack({ 378, 312, 16, 16 });
	spheres[5].anim.PushBack({ 398, 312, 16, 16 });
	spheres[5].anim.PushBack({ 419, 312, 16, 16 });
	spheres[5].anim.PushBack({ 439, 312, 16, 16 });
	spheres[5].anim.PushBack({ 459, 312, 16, 16 });
	spheres[5].anim.PushBack({ 479, 312, 16, 16 });
	spheres[5].anim.PushBack({ 499, 312, 16, 16 });
	spheres[5].anim.loop = false;
	spheres[5].anim.speed = 0.3f;
	spheres[5].sphere_color = ORANGE;


	spheres[6].anim.PushBack({ 12, 338, 16, 16 });
	spheres[6].anim.PushBack({ 32, 338, 16, 16 });
	spheres[6].anim.PushBack({ 52, 338, 16, 16 });
	spheres[6].anim.PushBack({ 72, 338, 16, 16 });
	spheres[6].anim.PushBack({ 92, 338, 16, 16 });
	spheres[6].anim.PushBack({ 113, 338, 16, 16 });
	spheres[6].anim.PushBack({ 133, 338, 16, 16 });
	spheres[6].anim.PushBack({ 153, 338, 16, 16 });
	spheres[6].anim.PushBack({ 173, 338, 16, 16 });
	spheres[6].anim.PushBack({ 193, 338, 16, 16 });
	spheres[6].anim.loop = false;
	spheres[6].anim.speed = 0.3f;
	spheres[6].sphere_color = YELLOW;

	spheres[7].anim.PushBack({ 318, 338, 16, 16 });
	spheres[7].anim.PushBack({ 338, 338, 16, 16 });
	spheres[7].anim.PushBack({ 358, 338, 16, 16 });
	spheres[7].anim.PushBack({ 378, 338, 16, 16 });
	spheres[7].anim.PushBack({ 398, 338, 16, 16 });
	spheres[7].anim.PushBack({ 419, 338, 16, 16 });
	spheres[7].anim.PushBack({ 439, 338, 16, 16 });
	spheres[7].anim.PushBack({ 459, 338, 16, 16 });
	spheres[7].anim.PushBack({ 479, 338, 16, 16 });
	spheres[7].anim.PushBack({ 499, 338, 16, 16 });
	spheres[7].anim.loop = false;
	spheres[7].anim.speed = 0.3f;
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

		if (s->Update() == false)
		{
			delete s;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= s->born)
		{
			App->render->Blit(graphics, s->position.x, s->position.y, &(s->anim.GetCurrentFrame()));
			if (s->fx_played == false)
			{
				s->fx_played = true;
			
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleSphere::AddSphere(const Sphere& sphere, int x, int y, COLLIDER_TYPE col_type, Uint32 delay)
{
	Sphere* s = new Sphere(sphere);
	s->born = SDL_GetTicks() + delay;
	s->position.x = 310;
	s->position.y = 370;
	s->speed.y = App->player->orientationy;
	s->speed.x = App->player->orientationx;
	s->sphere_color = sphere.sphere_color;
	s->collider = App->collision->AddCollider(s->anim.GetCurrentFrame(), col_type, this);
	s->collider->SetPos(310, 370);

	active[last_sphere++] = s;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Sphere::Sphere()
{
	position.SetToZero();
	speed.SetToZero();
}

Sphere::Sphere(const Sphere& s) :
anim(s.anim), position(s.position), speed(s.speed),
fx(s.fx), born(s.born)
{}

bool Sphere::Update()
{
	bool ret = true;


	position.x += speed.x * 2;
	position.y += speed.y * 2;

	collider->SetPos(position.x/2, position.y/2);


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

				App->spheres->allahu_list.push_back(active[i]);
				active[i]->checked = true;
				active[i]->CheckBobble();
				
				if (allahu_list.n_elements >= 3)
				{
					for (i = 0; i < allahu_list.n_elements; i++)
					{
						allahu_list[i]->position.x = 0;
						allahu_list[i]->position.y = 0;
						allahu_list[i]->pos_board->Empty = true;
					}
				}

				for (int i = 0; i < last_sphere; i++)
				{
					if (active[i]->checked == true){ active[i]->checked = false; }
				}
				allahu_list.clear();
				next_sphere = true;
			}
		}
	}
}

void Sphere::CheckBobble(){

	int i;

	for (i = 0; i < App->spheres->last_sphere; i++)
	{
		if (position.DistanceTo(App->spheres->active[i]->position)<= 18*SCREEN_SIZE  && sphere_color == App->spheres->active[i]->sphere_color && App->spheres->active[i]->checked == false)
		{
			App->spheres->active[i]->checked = true;
			App->spheres->allahu_list.push_back(App->spheres->active[i]);
			App->spheres->active[i]->CheckBobble();
		}
	}


}