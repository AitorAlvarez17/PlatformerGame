#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Textures.h"
#include "Render.h"
#include "SceneManager.h"
#include "SceneGameplay.h"
#include "Scene.h"

#include "List.h"

class ModuleUI : public Module
{
public:

	ModuleUI(Render* rend, Textures* tex, SceneManager* sManager);

	// Destructor
	virtual ~ModuleUI();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Start();
	bool Update(float dt);

	bool Load(Textures* tex);

	bool Draw(Render* render);
	// Called before quitting
	bool CleanUp();

	bool DrawHealth(Render* rend);
	void WeaponUI(Render* rend);


public:

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
	int saveCoroutine;

	int lifes;
	int maxLifes = 4;
	float cantSummon;
	bool drawLifes;

	SDL_Texture* background_ui;
	SDL_Texture* hab_ui;
	SDL_Texture* save_feedback;
	SDL_Texture* hearth;
	SDL_Texture* healthBackground;

	SDL_Texture* cd1;
	SDL_Texture* cd2;
	SDL_Texture* cd3;
	SDL_Texture* cd4;
	SDL_Texture* cd5;

	SDL_Texture* healHab;
	SDL_Texture* fireHab;

	SDL_Texture* cantSummonUi;
private:


	Render* rend;
	Textures* tex;
	SceneManager* sManager;
};

#endif // __MODULEUI_H__
