#include "ModuleUI.h"
#include "App.h"

#include "Defs.h"
#include "Log.h"

ModuleUI::ModuleUI() : Module()
{
	name.Create("debug");
}

// Destructor
ModuleUI::~ModuleUI()
{}

// Called before render is available
bool ModuleUI::Awake(pugi::xml_node& config)
{
	LOG("Loading Debug Module");
	bool ret = true;

	return ret;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	if (!active) return true;

	return true;
}

bool ModuleUI::Update(float dt)
{
	
	return true;
}

