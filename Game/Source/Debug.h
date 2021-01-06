#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Module.h"
#include "Input.h"
#include "App.h"
#include "ModuleUI.h"

#include "List.h"

class Input;
class App;
class ModuleUI;

class Debug : public Module
{
public:

	Debug(Input* input, Collisions* collisions,App* app, ModuleUI* ui);

	// Destructor
	virtual ~Debug();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();


public:

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

private:

	Input* input;
	App* app;
	Collisions* collisions;
	ModuleUI* ui;
};

#endif // __DEBUG_H__
