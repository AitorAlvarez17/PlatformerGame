#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Textures.h"
#include "Render.h"

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

	bool Load(Textures* tex);

	bool Draw(Render* render);
	// Called before quitting
	bool CleanUp();


public:

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;


private:

	SDL_Texture* background_ui;
	SDL_Texture* hab_ui;
};

#endif // __MODULEUI_H__
