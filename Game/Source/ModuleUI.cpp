#include "ModuleUI.h"
#include "App.h"
#include "Render.h"

#include "Defs.h"
#include "Log.h"

ModuleUI::ModuleUI(Render* rend, Textures* tex, SceneManager* sManager, EntityManager* eManager) : Module()
{
	name.Create("moduleUI");
	lifes = 3;
	drawLifes = 0;
	this->rend = rend;
	this->tex = tex;
	this->sManager = sManager;
	this->eManager = eManager;
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

bool ModuleUI::Start()
{
	Load(tex);

	return true;
}

// Called before quitting
bool ModuleUI::CleanUp()
{
	if (!active) return true;

	return true;
}

bool ModuleUI::Update(float dt)
{
	if (sManager->current->name == "GAMEPLAY")
	{
		DrawHealth(rend);
		WeaponUI(rend);

	}

	return true;
}

bool ModuleUI::Load(Textures* tex)
{
	cd1 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_1.png"));
	cd2 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_2.png"));
	cd3 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_3.png"));
	cd4 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_4.png"));
	cd5 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_5.png"));

	cantSummonUi = tex->Load(PATH("Assets/Textures/UI/", "cant.png"));

	return false;
}

bool ModuleUI::Draw(Render* render)
{
	return false;
}

bool ModuleUI::DrawHealth(Render* render)
{

	return false;
}

void ModuleUI::WeaponUI(Render* render)
{
	int margin = 3;
}