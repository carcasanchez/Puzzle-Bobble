#ifndef __ModuleCollisionSphere_H__
#define __ModuleCollisionSphere_H__

#define MAX_COLLIDERS 200

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_SPHERE,
	COLLIDER_LATERAL_WALL,
	COLLIDER_MAX
};

struct Circle
{
	int postionX, positioY;
	int radius;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Circle(int posX, int posY, int rad, COLLIDER_TYPE type, Module* callback = nullptr) :
		postionX(posX),
		positioY(posY),
		radius(rad),
		callback(callback)
	{}


};


class ModuleCollisionSphere : public Module
{
public:

	ModuleCollisionSphere();
	~ModuleCollisionSphere();

	update_status PreUpdate();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();

	Circle* AddColliderCircle(int positionX, int positionY, int radius, COLLIDER_TYPE type, Module*callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;
};

#endif // __ModuleCollision_H__