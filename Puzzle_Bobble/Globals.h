#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#include "SDL\include\SDL_rect.h"
#include <math.h>
#include "Point.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

enum States { FIRST, PREUPDATE, UPDATE, POSTUPDATE };

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

class Circle
{
public:

	iPoint origin;
	iPoint center;
	int radius;

	Circle(){};
	Circle(int or_x, int or_y, int center_x, int center_y, int radius)
	{
		origin.x = or_x;
		origin.y = or_y;
		center.x = center_x;
		center.y = center_y;
		this->radius = radius;
	}

	~Circle(){};

	float GetDistance(iPoint other) const
	{
		float x = center.x - other.x;
		float y = center.y - other.x;

		return sqrt(pow(x, 2) + pow(y, 2));
	}



};



typedef unsigned int uint;

// Configuration -----------
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define SCREEN_SIZE 2
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define REN_VSYNC 1
#define SPEED 5
#define MAX_EXPLOSIONS 50


#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

#endif // __GLOBALS_H__
