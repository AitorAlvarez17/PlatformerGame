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

	//cooldown = 0.0f;
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

	/*if (cantSummon <= 1.5)
	{
		cantSummon += dt;
	}
	if (cantSummon > 1.5)
	{
		cantSummon = 1.5;
	}*/

	
	return true;
}

bool ModuleUI::Load(Textures* tex)
{
	//background_ui = tex->Load(PATH("Assets/Textures/", "hab_ui.png"));
	//hab_ui = tex->Load(PATH("Assets/Textures/", "background_ui.png"));
	save_feedback = tex->Load(PATH("Assets/Textures/UI/", "autosave_feedback.png"));

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
	render->DrawTexture(save_feedback, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//render->DrawTexture(background_ui, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//render->DrawTexture(hab_ui, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);

	return false;
}

bool ModuleUI::DrawHealth(Render* render)
{
	

	return false;
}

void ModuleUI::WeaponUI(Render* render)
{
	//HEAL
	int margin = 3;
	
}