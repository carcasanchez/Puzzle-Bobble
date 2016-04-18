#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 200

#include "Module.h"

struct SDL_Rect;
class Circle;

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_SPHERE,
	COLLIDER_LATERAL_WALL,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;


	bool to_delete = false;
	/*COLLIDER_TYPE type;
	Module* callback = nullptr;*/
		

	virtual void SetPos(int x, int y);
	virtual bool CheckCollision() const;
	
	virtual void SetPos();
};



struct ColliderRect : public Collider
{
public:

	

	
	COLLIDER_TYPE type;
	Module* callback = nullptr;

	ColliderRect(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	

	bool CheckCollision(const SDL_Rect& r) const;

};

struct ColliderCirc : public Collider
{

public:

	Circle circ;


	COLLIDER_TYPE type;
	Module* callback = nullptr;

	ColliderCirc(Circle circle, COLLIDER_TYPE type, Module* callback = nullptr) :
		circ(circle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		circ.center.x = x;
		circ.center.y = y;
	}



	bool CheckCollision(const Circle& c) const;

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

	
	bool EraseCollider(Collider* collider);
	void DebugDraw();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback);
	Collider* AddCollider(Circle circ, COLLIDER_TYPE type, Module* callback);

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;



};

#endif // __ModuleCollision_H__