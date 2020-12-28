#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Module.h"
#include "Input.h"
#include "App.h"

#include "List.h"

class Debug : public Module
{
public:

	Debug();

	// Destructor
	virtual ~Debug();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt, Input* input, App* app);

	// Called before quitting
	bool CleanUp();


public:

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __DEBUG_H__
