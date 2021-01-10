#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Module.h"
#include "Input.h"
#include "App.h"
#include "ModuleUI.h"
#include "EntityManager.h"
#include "Entity.h"

#include "List.h"

class Input;
class App;
class ModuleUI;
class EntityManager;
class Entity;

class Debug : public Module
{
public:

	Debug(Input* input, Collisions* collisions, App* app, ModuleUI* ui, EntityManager* entity);

	// Destructor
	virtual ~Debug();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Start();

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();


public:

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
	int bufferPlayer;

	int gravBuffer;
	int frCapBuffer;
	bool frCap = true;

private:

	Input* input;
	App* app;
	Collisions* collisions;
	ModuleUI* ui;
	EntityManager* eManager;
};

#endif // __DEBUG_H__
