#include "ModuleUI.h"
#include "App.h"
#include "Render.h"

#include "Defs.h"
#include "Log.h"

ModuleUI::ModuleUI(Render* rend, Textures* tex, SceneManager* sManager) : Module()
{
	name.Create("debug");
	lifes = 3;
	drawLifes = 0;
	this->rend = rend;
	this->tex = tex;
	this->sManager = sManager;
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
	}
	saveCoroutine += dt;

	if (saveCoroutine > 3.0f)
		saveCoroutine = 3.0f;
	if (cantSummon <= 1.5)
	{
		cantSummon += dt;
	}
	if (cantSummon > 1.5)
	{
		cantSummon = 1.5;
	}

	
	return true;
}

bool ModuleUI::Load(Textures* tex)
{
	//background_ui = tex->Load(PATH("Assets/Textures/", "hab_ui.png"));
	//hab_ui = tex->Load(PATH("Assets/Textures/", "background_ui.png"));
	save_feedback = tex->Load(PATH("Assets/Textures/UI/", "autosave_feedback.png"));
	hearth = tex->Load(PATH("Assets/Textures/UI/", "hearth_ui.png"));
	healthBackground = tex->Load(PATH("Assets/Textures/UI/", "health_background.png"));

	cd1 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_1.png"));
	cd2 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_2.png"));
	cd3 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_3.png"));
	cd4 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_4.png"));
	cd5 = tex->Load(PATH("Assets/Textures/UI/", "cooldown_5.png"));

	healHab = tex->Load(PATH("Assets/Textures/UI/", "heal_gui.png"));
	fireHab = tex->Load(PATH("Assets/Textures/UI/", "fireball_gui.png"));
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
	int margin = 4;
	render->DrawTexture(healthBackground, 0, 15, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	if (lifes != 0)
	{
		int maxLifes = lifes;
		for (int i = 0; i < maxLifes; i++)
		{
			//LOG("lifes loading: %d", i);
			render->DrawTexture(hearth, (15 + (40*i)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);


		}
	}

	return false;
}
/*
void ModuleUI::WeaponUI(Render* render)
{
	//HEAL
	int margin = 3;
	render->DrawTexture(healHab, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	render->DrawTexture(fireHab, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
	//app->render->DrawTexture(pressH, camaraPosx + margin + 64, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
	if (maxLifes)
	{
		if (cantSummon < 1.5)
		{
			render->DrawTexture(cantSummonUi, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}

		return;
	}
	if (app->player->cooldown < app->player->maxCooldown) // HEAL
	{
		float cd = 3;
		if (cd < 1)
		{
			render->DrawTexture(cd1, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (cd < 2 && cd > 1)
		{
			render->DrawTexture(cd2, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (cd < 3 && cd > 2)
		{
			render->DrawTexture(cd3, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
	}
	if (app->player->fireCooldown < app->player->fireMaxCooldown)	//FIREBALL
	{
		float fireCd = 5;
		if (fireCd < 1)
		{
			render->DrawTexture(cd5, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (fireCd < 2 && fireCd > 1)
		{
			render->DrawTexture(cd4, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (fireCd < 3 && fireCd > 2)
		{
			render->DrawTexture(cd3, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (fireCd < 4 && fireCd > 3)
		{
			render->DrawTexture(cd2, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
		else if (fireCd < 5 && fireCd > 4)
		{
			render->DrawTexture(cd1, (15 + (40)) + margin, 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
		}
	}


	

}*/