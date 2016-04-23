#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

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
{//////////////////////////////////////Collision scenary/////////////////////////////////////////////

	App->collision->AddCollider(SDL_Rect{ 224, 24, 8, 194 }, COLLIDER_LATERAL_WALL);//Left
	App->collision->AddCollider(SDL_Rect{ 88, 24, 8, 194 }, COLLIDER_LATERAL_WALL);//Right
	App->collision->AddCollider(SDL_Rect{ 88, 16, 144, 8 }, COLLIDER_WALL);//Top
	

	/*

	////////////////////////////////////Collision sphere//////////////////////////////////////////
	App->collision->AddCollider({ 96, 24, 16, 16 }, COLLIDER_SPHERE);//1
	App->collision->AddCollider({ 112, 24, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 128, 24, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 144, 24, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 160, 24, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 176, 24, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 192, 24, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 208, 24, 16, 16 }, COLLIDER_SPHERE);
	
	App->collision->AddCollider({ 104, 38, 16, 16 }, COLLIDER_SPHERE);//2
	App->collision->AddCollider({ 120, 38, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 136, 38, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 152, 38, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 168, 38, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 184, 38, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 200, 38, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 96, 52, 16, 16 }, COLLIDER_SPHERE);//3
	App->collision->AddCollider({ 112, 52, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 128, 52, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 144, 52, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 160, 52, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 176, 52, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 192, 52, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 208, 52, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 104, 66, 16, 16 }, COLLIDER_SPHERE);//4
	App->collision->AddCollider({ 120, 66, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 136, 66, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 152, 66, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 168, 66, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 184, 66, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 200, 66, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 96, 80, 16, 16 }, COLLIDER_SPHERE);//5
	App->collision->AddCollider({ 112, 80, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 128, 80, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 144, 80, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 160, 80, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 176, 80, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 192, 80, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 208, 80, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 104, 94, 16, 16 }, COLLIDER_SPHERE);//6
	App->collision->AddCollider({ 120, 94, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 136, 94, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 152, 94, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 168, 94, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 184, 94, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 200, 94, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 96, 108, 16, 16 }, COLLIDER_SPHERE);//7
	App->collision->AddCollider({ 112, 108, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 128, 108, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 144, 108, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 160, 108, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 176, 108, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 192, 108, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 208, 108, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 104, 122, 16, 16 }, COLLIDER_SPHERE);//8
	App->collision->AddCollider({ 120, 122, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 136, 122, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 152, 122, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 168, 122, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 184, 122, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 200, 122, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 96, 136, 16, 16 }, COLLIDER_SPHERE);//9
	App->collision->AddCollider({ 112, 136, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 128, 136, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 144, 136, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 160, 136, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 176, 136, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 192, 136, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 208, 136, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 104, 150, 16, 16 }, COLLIDER_SPHERE);//10
	App->collision->AddCollider({ 120, 150, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 136, 150, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 152, 150, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 168, 150, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 184, 150, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 200, 150, 16, 16 }, COLLIDER_SPHERE);

	App->collision->AddCollider({ 96, 164, 16, 16 }, COLLIDER_SPHERE);//1
	App->collision->AddCollider({ 112, 164, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 128, 164, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 144, 164, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 160, 164, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 176, 164, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 192, 164, 16, 16 }, COLLIDER_SPHERE);
	App->collision->AddCollider({ 208, 164, 16, 16 }, COLLIDER_SPHERE);
	*/

	///////////////////////////////////////////////////////////////////////////////////
	LOG("Loading particles");
	graphics = App->textures->Load("Sprites.png");
	//blueSphere
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
	spheres[0].anim.loop = true;
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
	spheres[1].anim.loop = true;
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
	spheres[2].anim.loop = true;
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
	spheres[3].anim.loop = true;
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
	spheres[4].anim.loop = true;
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
	spheres[5].anim.loop = true;
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
	spheres[6].anim.loop = true;
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
	spheres[7].anim.loop = true;
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
fx(s.fx), born(s.born), life(s.life)
{}

bool Sphere::Update()
{
	bool ret = true;

	if (life == false)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x * 2;
	position.y += speed.y * 2;

	collider->SetPos(position.x/2, position.y/2);


	return ret;
}
void ModuleSphere::OnCollision(ColliderRect* c1, ColliderRect* c2)
{

	for (uint i = 0; i < MAX_ACTIVE_SPHERES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{

			active[i]->speed.x *= -1;
			active[i]->speed.y *= -1;

		}
	}

}