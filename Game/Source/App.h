#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "PerfTimer.h"
#include "Timer.h"


#include "PugiXml/src/pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class Collisions;
class Player;
class Enemy;
class Coins;
class CheckPoints;
class ModuleFadeToBlack;
class Intro;
class PathFinding;
class Debug;
class ObjectManager;

class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// L02: TODO 1: Create methods to request Load / Save

private:

	// Load config file
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();


	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// L02: TODO 5: Declare methods to load/save game

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	Map* map;
	CheckPoints* checkpoints;
	PathFinding* pathfinding;
	Collisions* collisions;
	Player* player;
	Enemy* enemy;
	ModuleFadeToBlack* fade;
	Intro* menu;
	Debug* debug;
	Coins* coin;
	ObjectManager* oManager;

	bool Load();
	bool Save();

	void RequestSave() 
	{
		requestSave = true;
	}

	void RequestLoad() 
	{
		requestLoad = true;

	}

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module*> modules;

	// L01: DONE 2: Create new variables from pugui namespace:
	// xml_document to store the config file and
	// xml_node(s) to read specific branches of the xml
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;
	//pugi::xml_document save;
	uint frames;


	// L02: TODO 1: Create required variables to request load / save and 
	// the filename for save / load
	pugi::xml_document saveGame;
	pugi::xml_node saveState;
	pugi::xml_node rend;//variable que carga las cosas en renderer
	pugi::xml_node inp;//carga en input
	pugi::xml_node sce;//carga en scene
	pugi::xml_node wi;//carga en window
	pugi::xml_node au;//carga en audio
	pugi::xml_node pl;//carga en player


	//PREGUNTASELO A RAM�N
	bool requestLoad = false;
	bool requestSave = false;

	PerfTimer ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastFrameTime;

	uint32 lastFrame = 0;
	uint32 prevFrame = 0;

	uint64 frameCount = 0;

	float dt = 0.0f;
	float frameDelay = -1;

};

extern App* app;

#endif	// __APP_H__