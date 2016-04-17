#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_SPHERES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Sphere
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	Collider* collider = nullptr;

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

	Sphere blueSphere;
	Sphere greenSphere;
	Sphere graySphere;
	Sphere blackSphere;
	Sphere redSphere;
	Sphere orangeSphere;
	Sphere yellowSphere;
	Sphere violetSphere;

	void OnCollision(Collider* c1, Collider* c2);



};

#endif // __MODULEPARTICLES_H__