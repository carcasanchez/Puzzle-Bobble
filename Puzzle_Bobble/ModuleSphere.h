#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_SPHERES 100
#define NUMBERS_OF_SPHERES 8

struct SDL_Texture;
struct ColliderRect;
enum COLLIDER_TYPE;
enum Color { BLUE, GREEN, GRAY, BLACK, RED, ORANGE, YELLOW, VIOLET };

struct Sphere
{

	Animation anim;
	uint fx = 0;
	iPoint position;
	fPoint speed;
	Uint32 born = 0;
	bool life = true;
	bool fx_played = false;
	Collider* collider = nullptr;
	Color sphere_color;
	Sphere();
	Sphere(const Sphere& p);
	bool Update();
};

class ModuleSphere : public Module
{
public:
	ModuleSphere();
	~ModuleSphere();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddSphere(const Sphere& particle, int x, int y, COLLIDER_TYPE col_type= COLLIDER_SPHERE,  Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Sphere* active[MAX_ACTIVE_SPHERES];
	uint last_sphere = 0;
	

public:

	Sphere spheres[NUMBERS_OF_SPHERES];

	void OnCollision(ColliderRect* c1, ColliderRect* c2);



};

#endif // __MODULEPARTICLES_H__