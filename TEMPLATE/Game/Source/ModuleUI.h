#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"

#include "List.h"

class ModuleUI : public Module
{
public:

	ModuleUI();

	// Destructor
	virtual ~ModuleUI();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();


public:

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __MODULEUI_H__
