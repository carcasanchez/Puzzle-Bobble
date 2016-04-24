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

void ModuleBoard::CheckPosition(Sphere* actual_sphere)
{
	int i = 0;
	int min_distance;
	int square_index;
	
	min_distance = board[0].DistanceTo(actual_sphere->position);

	for (i = 0;i< NUM_SQUARES; i++)
	{
		if (board[i].Empty == true)
		{
			if (board[i].DistanceTo(actual_sphere->position) < min_distance)
			{
				min_distance = board[i].DistanceTo(actual_sphere->position);
				square_index = i;
			}
		}
	}
	actual_sphere->position = board[square_index];
	board[square_index].Empty = false;
}