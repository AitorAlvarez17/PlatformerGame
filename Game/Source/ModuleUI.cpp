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

bool ModuleUI::Load(Textures* tex)
{
	background_ui = tex->Load(PATH("Assets/Textures/", "hab_ui.png"));
	hab_ui = tex->Load(PATH("Assets/Textures/", "background_ui.png"));

	return true;
}

bool ModuleUI:: Draw(Render* render)
{
	render->DrawTexture(background_ui, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(hab_ui, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);

	return true;
}