#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_SPHERE] = true;
	matrix[COLLIDER_WALL][COLLIDER_LATERAL_WALL] = true;
	matrix[COLLIDER_WALL][COLLIDER_SPHERE] = false;

	matrix[COLLIDER_SPHERE][COLLIDER_WALL] = true;
	matrix[COLLIDER_SPHERE][COLLIDER_SPHERE] = true;
	matrix[COLLIDER_SPHERE][COLLIDER_LATERAL_WALL] = true;
	matrix[COLLIDER_SPHERE][COLLIDER_SPHERE] = true;

	matrix[COLLIDER_LATERAL_WALL][COLLIDER_WALL] = true;
	matrix[COLLIDER_LATERAL_WALL][COLLIDER_SPHERE] = true;
	matrix[COLLIDER_LATERAL_WALL][COLLIDER_LATERAL_WALL] = false;
	matrix[COLLIDER_LATERAL_WALL][COLLIDER_SPHERE] = false;

	matrix[COLLIDER_LOSE][COLLIDER_LOSE] = false;
	matrix[COLLIDER_LOSE][COLLIDER_SPHERE] = true;
	matrix[COLLIDER_LOSE][COLLIDER_WALL] = false;
	matrix[COLLIDER_LOSE][COLLIDER_SPHERE] = false;

}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		case COLLIDER_WALL: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case COLLIDER_LATERAL_WALL: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_SPHERE: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_LOSE: // asuliyo secsy
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new ColliderRect(rect, type, callback);
			break;
		}
	}

	return ret;
}

Collider* ModuleCollision::AddCollider(Circle circ, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new ColliderCircle(circ, type, callback);
			break;
		}
	}

	return ret;
}


bool ModuleCollision::EraseCollider(ColliderRect* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			return true;
		}
	}

	return false;
}

// -----------------------------------------------------

bool ColliderRect::CheckCollision(const Collider* c) const
{
	
	return (rect.x < c->rect.x + c->rect.w &&
		rect.x + rect.w > c->rect.x &&
		rect.y < c->rect.y + c->rect.h &&
		rect.h + rect.y > c->rect.y);
			
}

bool ColliderCircle::CheckCollision(const Collider* c) const
{

	if (c->type==COLLIDER_SPHERE)
		return (circ.GetDistance(c->circ.center) < circ.radius + c->circ.radius);

	else return (rect.x < c->rect.x + c->rect.w &&
		rect.x + rect.w > c->rect.x &&
		rect.y < c->rect.y + c->rect.h &&
		rect.h + rect.y > c->rect.y);
	
}