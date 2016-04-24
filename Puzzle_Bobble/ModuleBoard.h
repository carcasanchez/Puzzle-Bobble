#ifndef __BOARD_H__
#define __BOARD_H__

#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "ModuleSphere.h"

#define NUM_SQUARES 90

class ModuleBoard : public Module
{
public:
	ModuleBoard();
	~ModuleBoard();

	bool Start();
	void CheckPosition( Sphere& actual_sphere);
	bool CleanUp();

public:
	iPoint board[NUM_SQUARES];

};

#endif

