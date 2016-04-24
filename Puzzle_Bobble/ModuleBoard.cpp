#include"ModuleBoard.h"

ModuleBoard::ModuleBoard()
{
	int x, y;
	int i = 0;
	for (y = 32 * SCREEN_SIZE - 16; i < NUM_SQUARES; y += 14 * SCREEN_SIZE)
	{
		if (i % 2 == 0)
		{
			for (x = 104 * SCREEN_SIZE - 16; x < 216 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)
			{
				board[i].x = x;
				board[i].y = y;

			}
		}

		else
		{
			for (x = 112 * SCREEN_SIZE - 16; x < 208 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)
			{
				board[i].x = x;
				board[i].y = y;
			}
		}
		i++;
	}
}



ModuleBoard::~ModuleBoard(){};

bool ModuleBoard::Start(){ return true; };


bool ModuleBoard::CleanUp()
{
	int i;
	for (i = 0; i < NUM_SQUARES; i++)
	{
		if (board[i].Empty == false)
		{
			board[i].Empty == true;
		}
	}
	return true;
}

void CheckPosition(const Sphere& actual_sphere)
{
	int i = 0;
	for (i = 0; NUMBER_OF_SPHERES; i++)
	{
		
	}

}