#ifndef __BOARD_H__
#define __BOARD_H__

#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "ModuleSphere.h"
#include "Application.h"

#define NUM_SQUARES 90

class ModuleBoard : public Module
{
public:
	ModuleBoard();
	~ModuleBoard();
	
	bool Start();
	void CheckPositionLeft(Sphere* actual_sphere);
	void CheckPositionRight(Sphere* actual_sphere);
	void CreateMap(int number[]);
	bool CleanUp();
	bool CheckWin();
	void BoardDown(int &counter);
	int counter = 0;
public:
	Vector<iPoint*> board_left;
	Vector<iPoint*> board_right;
};

#endif

