#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Module.h"
#include "Scene.h"

class GuiButton;

class Input;
class Render;
class Textures;
class AudioManager;
class Window;
class App;
class EntityManager;
class ModuleUI;
class Collisions;
class CheckPoints;
class Debug;

class SceneManager : public Module
{
public:

	SceneManager(Input* input, Render* render, Textures* tex, AudioManager* audio, Window* window, EntityManager* entityManager, App* app, ModuleUI* ui, Collisions* coll, CheckPoints* check, Debug* debug);

	// Destructor
	virtual ~SceneManager();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;
	// Called before quitting
	bool CleanUp();

	bool exitDemand;
private:

	Input* input;
	Render* render;
	Textures* tex; 
	AudioManager * aud;
	Window* win;
	App* app;
	EntityManager* entityManager;
	ModuleUI* ui;
	Collisions* collisions;
	CheckPoints* check;
	Debug* debug;
public:
	Scene* current;
	Scene* next;
private:
	// Required variables to manage screen transitions (fade-in, fade-out)
	bool onTransition;
	bool fadeOutCompleted;
	float transitionAlpha;
};

#endif // __SCENEMANAGER_H__