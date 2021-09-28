#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();


private:


public:


private:


};
