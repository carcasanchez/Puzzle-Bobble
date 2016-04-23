#ifndef __MODULE_H__
#define __MODULE_H__
#include "Globals.h"
struct Collider;


class Module
{
private:
	bool enabled = true;

public:
	virtual ~Module() {}

	virtual bool Init()					{ return true; }
	virtual bool Start()					{ return true; }
	virtual update_status PreUpdate()		{ return update_status::UPDATE_CONTINUE; }
	virtual update_status Update()		{ return update_status::UPDATE_CONTINUE; }
	virtual update_status PostUpdate() 	{ return update_status::UPDATE_CONTINUE; }
	virtual bool CleanUp()				{ return true; }

	bool IsEnabled() const				{ return enabled; }

	void Enable()
	{
		if (enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true)
		{
			enabled = false;
			CleanUp();
		}
	}

	virtual void OnCollision(Collider*, Collider*) {}

};

#endif // __MODULE_H__