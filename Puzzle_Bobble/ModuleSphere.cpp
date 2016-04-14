#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
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
	LOG("Loading particles");
	graphics = App->textures->Load("Sprites.png");

	blueSphere.anim.PushBack({ 12, 260, 16, 16 });
	blueSphere.anim.PushBack({ 32, 260, 16, 16 });
	blueSphere.anim.PushBack({ 52, 260, 16, 16 });
	blueSphere.anim.PushBack({ 72, 260, 16, 16 });
	blueSphere.anim.PushBack({ 92, 260, 16, 16 });
	blueSphere.anim.PushBack({ 113, 260, 16, 16 });
	blueSphere.anim.PushBack({ 133, 260, 16, 16 });
	blueSphere.anim.PushBack({ 153, 260, 16, 16 });
	blueSphere.anim.PushBack({ 173, 260, 16, 16 });
	blueSphere.anim.PushBack({ 193, 260, 16, 16 });
	blueSphere.anim.loop = true;
	blueSphere.anim.speed = 0.3f;

	greenSphere.anim.PushBack({ 318, 260, 16, 16 });
	greenSphere.anim.PushBack({ 338, 260, 16, 16 });
	greenSphere.anim.PushBack({ 358, 260, 16, 16 });
	greenSphere.anim.PushBack({ 378, 260, 16, 16 });
	greenSphere.anim.PushBack({ 398, 260, 16, 16 });
	greenSphere.anim.PushBack({ 419, 260, 16, 16 });
	greenSphere.anim.PushBack({ 439, 260, 16, 16 });
	greenSphere.anim.PushBack({ 459, 260, 16, 16 });
	greenSphere.anim.PushBack({ 479, 260, 16, 16 });
	greenSphere.anim.PushBack({ 499, 260, 16, 16 });
	blueSphere.anim.loop = true;
	blueSphere.anim.speed = 0.3f;

	graySphere.anim.PushBack({ 12, 286, 16, 16 });
	graySphere.anim.PushBack({ 32, 286, 16, 16 });
	graySphere.anim.PushBack({ 52, 286, 16, 16 });
	graySphere.anim.PushBack({ 72, 286, 16, 16 });
	graySphere.anim.PushBack({ 92, 286, 16, 16 });
	graySphere.anim.PushBack({ 113, 286, 16, 16 });
	graySphere.anim.PushBack({ 133, 286, 16, 16 });
	graySphere.anim.PushBack({ 153, 286, 16, 16 });
	graySphere.anim.PushBack({ 173, 286, 16, 16 });
	graySphere.anim.PushBack({ 193, 286, 16, 16 });
	graySphere.anim.loop = true;
	graySphere.anim.speed = 0.3f;

	blackSphere.anim.PushBack({ 318, 286, 16, 16 });
	blackSphere.anim.PushBack({ 338, 286, 16, 16 });
	blackSphere.anim.PushBack({ 358, 286, 16, 16 });
	blackSphere.anim.PushBack({ 378, 286, 16, 16 });
	blackSphere.anim.PushBack({ 398, 286, 16, 16 });
	blackSphere.anim.PushBack({ 419, 286, 16, 16 });
	blackSphere.anim.PushBack({ 439, 286, 16, 16 });
	blackSphere.anim.PushBack({ 459, 286, 16, 16 });
	blackSphere.anim.PushBack({ 479, 286, 16, 16 });
	blackSphere.anim.PushBack({ 499, 286, 16, 16 });
	blackSphere.anim.loop = true;
	blackSphere.anim.speed = 0.3f;

	redSphere.anim.PushBack({ 12, 312, 16, 16 });
	redSphere.anim.PushBack({ 32, 312, 16, 16 });
	redSphere.anim.PushBack({ 92, 312, 16, 16 });
	redSphere.anim.PushBack({ 113, 312, 16, 16 });
	redSphere.anim.PushBack({ 133, 312, 16, 16 });
	redSphere.anim.PushBack({ 153, 312, 16, 16 });
	redSphere.anim.PushBack({ 173, 312, 16, 16 });
	redSphere.anim.PushBack({ 193, 312, 16, 16 });
	redSphere.anim.loop = true;
	redSphere.anim.speed = 0.3f;
	redSphere.life = 1000;

	orangeSphere.anim.PushBack({ 318, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 338, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 358, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 378, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 398, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 419, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 439, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 459, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 479, 312, 16, 16 });
	orangeSphere.anim.PushBack({ 499, 312, 16, 16 });
	orangeSphere.anim.loop = true;
	orangeSphere.anim.speed = 0.3f;

	yellowSphere.anim.PushBack({ 12, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 32, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 52, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 72, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 92, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 113, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 133, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 153, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 173, 338, 16, 16 });
	yellowSphere.anim.PushBack({ 193, 338, 16, 16 });
	yellowSphere.anim.loop = true;
	yellowSphere.anim.speed = 0.3f;

	violetSphere.anim.PushBack({ 318, 338, 16, 16 });
	violetSphere.anim.PushBack({ 338, 338, 16, 16 });
	violetSphere.anim.PushBack({ 358, 338, 16, 16 });
	violetSphere.anim.PushBack({ 378, 338, 16, 16 });
	violetSphere.anim.PushBack({ 398, 338, 16, 16 });
	violetSphere.anim.PushBack({ 419, 338, 16, 16 });
	violetSphere.anim.PushBack({ 439, 338, 16, 16 });
	violetSphere.anim.PushBack({ 459, 338, 16, 16 });
	violetSphere.anim.PushBack({ 479, 338, 16, 16 });
	violetSphere.anim.PushBack({ 499, 338, 16, 16 });
	violetSphere.anim.loop = true;
	violetSphere.anim.speed = 0.3f;
	

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

void ModuleSphere::AddSphere(const Sphere& sphere, int x, int y, Uint32 delay)
{
	Sphere* s = new Sphere(sphere);
	s->born = SDL_GetTicks() + delay;
	s->position.x = x;
	s->position.y = y;
	s->speed.y = App->player->orientationy;
	s->speed.x = App->player->orientationx;


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

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x*2;
	position.y += speed.y * 2;

	return ret;
}