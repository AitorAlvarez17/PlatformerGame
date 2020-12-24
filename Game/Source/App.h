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
class ModuleUI;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class Collisions;
class Player;
class CheckPoints;
class ModuleFadeToBlack;
class Intro;
class PathFinding;
class Wand;
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
	Collisions* collisions;
	Player* player;
	ModuleUI* ui;
	ModuleFadeToBlack* fade;
	Intro* menu;
	PathFinding* pathfinding;
	Debug* debug;
	Wand* wand;
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
	float dt = 0.0f;
private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module*> modules;

	// xml_document to store the config file and
	// xml_node(s) to read specific branches of the xml
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;

	//Load Files
	pugi::xml_document saveGame;
	pugi::xml_node saveState;
	pugi::xml_node rend;//load the render
	pugi::xml_node inp;//load the input
	pugi::xml_node sce;//load the scene
	pugi::xml_node wi;//load the window
	pugi::xml_node au;//load the audio
	pugi::xml_node pl;//load the player
	pugi::xml_node en;//load the enemy

	bool requestLoad = false;
	bool requestSave = false;

	//PerfTimer ptimer;

	//Timer startupTime;
	//Timer frameTime;
	//Timer lastFrameTime;

	//uint32 lastFrame = 0;
	//uint32 prevFrame = 0;

	//uint64 frameCount = 0;

	//float dt = 0.0f;
	//float frameDelay = -1;
	PerfTimer ptimer;
	uint64 frameCount = 0;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	uint32 lastSecFrameCount = 0;
	uint32 prevLastSecFrameCount = 0;
	//float dt = 0.0f;

	int	cappedMs = -1;
};

extern App* app;

#endif	// __APP_H__