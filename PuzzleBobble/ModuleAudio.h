#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__



#include "Module.h"
#include "Globals.h"

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
};



#endif //__ModuleAudio_H__