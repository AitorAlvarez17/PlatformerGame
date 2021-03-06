#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class AudioManager;
class EntityManager;
class SceneManager;
class Debug;
class ModuleUI;
class Collisions;
class CheckPoints;

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

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	void SaveGameRequest() const;

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

private:

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

	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	AudioManager* audio;
	EntityManager* entityManager;
	SceneManager* sceneManager;
	Debug* debug;
	ModuleUI* ui;
	Collisions* collisions;
	CheckPoints* checkPoints;

	mutable bool firstSaved = false;
	bool newGame;

	int	cappedMs = -1;

private:

	pugi::xml_document saveGame;
	pugi::xml_document save;
	pugi::xml_node saveState;
	pugi::xml_node rend;//load the render
	pugi::xml_node inp;//load the input
	pugi::xml_node sce;//load the scene
	pugi::xml_node wi;//load the window
	pugi::xml_node au;//load the audio
	pugi::xml_node pl;//load the player
	pugi::xml_node en;//load the enemy
	pugi::xml_node ent;//load the entities of the map

	int argc;
	char** args;
	
	SString title;
	SString organization;

	List<Module *> modules;

	// L01: DONE 2: Create new variables from pugui namespace
	// NOTE: Redesigned LoadConfig() to avoid storing this variables
	//pugi::xml_document configFile;
	//pugi::xml_node config;
	//pugi::xml_node configApp;

	mutable bool saveGameRequested;
	bool loadGameRequested;
	

	// L07: DONE 4: Calculate some timing measures
	// required variables are provided:
	PerfTimer ptimer;
	uint64 frameCount = 0;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	uint32 lastSecFrameCount = 0;
	uint32 prevLastSecFrameCount = 0;
	float dt = 0.0f;
};

#endif	// __APP_H__