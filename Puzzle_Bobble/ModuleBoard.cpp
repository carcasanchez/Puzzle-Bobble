#include"ModuleBoard.h"

ModuleBoard::ModuleBoard()
{
	int x, y;
	int i = 0;
	int j = 0;
	for (y = 32 * SCREEN_SIZE - 16; j < NUM_SQUARES; y += 14 * SCREEN_SIZE)
	{
		if (i % 2 == 0)
		{
			for (x = 24 * SCREEN_SIZE - 16; x < 136 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//112
			{
				board.push_back(new iPoint(x, y));
				//board[j]->x = x;
				//board[j]->y = y;
				j++;
			}
		}

		else
		{
			for (x = 32 * SCREEN_SIZE - 16; x < 128 * SCREEN_SIZE; x += 16 * SCREEN_SIZE)//96
			{
				board.push_back(new iPoint(x, y));
				//board[j]->x = x;
				//board[j]->y = y;
				j++;
				
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
		if (board[i]->Empty == false)
		{
			board[i]->Empty = true;
		}
	}
	return true;
}

void ModuleBoard::CheckPosition(Sphere* actual_sphere)
{
	int i = 0;
	int min_distance;
	int square_index = 0;
	
	min_distance = 100;//esto soluciona el bug de la esquina

	for (i = 0;i< NUM_SQUARES; i++)
	{
		if (board[i]->Empty == true)
		{
			if (board[i]->DistanceTo(actual_sphere->position) < min_distance)
			{
				min_distance = board[i]->DistanceTo(actual_sphere->position);
				square_index = i;
			}
		}
	}
	actual_sphere->position.x = board[square_index]->x;
	actual_sphere->position.y = board[square_index]->y;
	actual_sphere->pos_board.x = board[square_index]->x;
	actual_sphere->pos_board.y = board[square_index]->y;
	board[square_index]->Empty = false;
	actual_sphere->board_index = square_index;
	
}
void ModuleBoard::CreateMap(int number[]){

	int i = 0;
	for (i= 0 ; i < NUM_SQUARES;i++)
	{
		if (number[i] >= 0 && number[i] < 8){
			App->spheres->SetSphere(App->spheres->spheres[number[i]], board[i]->x, board[i]->y, i);
			board[i]->Empty = false;
			}				
		}
}

void ModuleBoard::BoardDown(int &counter){
	int i;
	int x, y;
	y = 32 * SCREEN_SIZE - 16;
	for (i = 0; i < board.size(); i++){
		board[i]->y += 14*SCREEN_SIZE;
	}
	for (i = 0; i < App->spheres->last_sphere_left; i++){
		if (App->spheres->active_left[i] != nullptr){
			App->spheres->active_left[i]->position.y += 14 * SCREEN_SIZE;
		}
	}
	if (counter % 2 == 0){
		x = 32 * SCREEN_SIZE - 16;
		for (i = 0; i < 7; i++){
			board.push_front(new iPoint(x, y));
			x += 16 * SCREEN_SIZE;
		}
		for (i = 0; i < 7; i++)
		{
			
		App->spheres->SetSphere(App->spheres->spheres[5], board[i]->x, board[i]->y, i);
		board[i]->Empty = false;
		}
	}
	else{
		x = 24 * SCREEN_SIZE - 16;
		for (i = 0; i < 8; i++){
			board.push_front(new iPoint(x, y));
			x += 16 * SCREEN_SIZE;
		}
		for (i = 0; i < 8; i++)
		{

			App->spheres->SetSphere(App->spheres->spheres[5], board[i]->x, board[i]->y, i);
			board[i]->Empty = false;
		}
	}
	counter++;

}
bool ModuleBoard::CheckWin()
{
	int i = 0;
	for (i = 0; i < NUM_SQUARES; i++)
	{
		if (board[i]->Empty != true)

			return false;
	}

	return true;
}

