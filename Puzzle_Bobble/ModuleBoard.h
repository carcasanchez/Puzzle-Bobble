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
	void CheckPosition(Sphere* actual_sphere);
	void CreateMap(int number[]);
	bool CleanUp();
	bool CheckWin();
	

public:
	Vector<iPoint*> board;

};

#endif

