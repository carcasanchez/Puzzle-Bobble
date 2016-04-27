#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 200

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_SPHERE,
	COLLIDER_LATERAL_WALL,
	COLLIDER_LOSE,
	COLLIDER_MAX
};




struct Collider
{
	SDL_Rect rect;
	Circle circ;

	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	Collider(COLLIDER_TYPE type, Module* callback = nullptr) :
		type(type),
		callback(callback)
	{}

	

	virtual bool CheckCollision(const Collider* c) const = 0;
	virtual void SetPos(int x, int y) = 0;

};


struct ColliderRect : public Collider
{
	

	ColliderRect(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) : Collider(type, callback)
	{
		rect = rectangle;
	}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	bool CheckCollision(const Collider* c) const;


};

struct ColliderCircle : public Collider
{
	
	
	ColliderCircle(Circle circle, COLLIDER_TYPE type, Module* callback = nullptr) : Collider(type, callback)
	{
		circ = circle;
		rect.x = circle.origin.x;
		rect.y = circle.origin.y;
		rect.h = rect.w = circle.radius*2;

	}

	void SetPos(int x, int y)
	{
		circ.center.x = x;
		circ.center.y = y;
	}

	bool CheckCollision(const Collider* c) const;

};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	//update_status PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = nullptr);
	Collider* AddCollider(Circle circ, COLLIDER_TYPE type, Module*callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__