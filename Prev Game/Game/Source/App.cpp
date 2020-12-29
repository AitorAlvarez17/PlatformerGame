#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "Wand.h"
#include "Collisions.h"
#include "Player.h"
#include "ObjectManager.h"
#include "Object.h"
#include "CheckPoints.h"
#include "Pathfinding.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "Debug.h"
#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	PERF_START(ptimer);

	input = new Input(true);
	win = new Window(true);
	render = new Render(true);
	tex = new Textures(true);
	audio = new Audio(true);
	scene = new Scene(false);
	checkpoints = new CheckPoints(true);
	map = new Map(false);
	collisions = new Collisions(false);
	player = new Player(false);

	fade = new ModuleFadeToBlack(true);
	pathfinding = new PathFinding(false);
	debug = new Debug(true);
	wand = new Wand(true);
	oManager = new ObjectManager(true);
	ui = new ModuleUI(true);

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(scene);
	AddModule(wand);

	// Render last to swap buffer
	AddModule(player);
	AddModule(oManager);
	AddModule(collisions);
	AddModule(map);
	AddModule(fade);
	AddModule(pathfinding);
	AddModule(debug);
	AddModule(ui);
	AddModule(checkpoints);
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
	configFile.reset();
}

void App::AddModule(Module* module)
{
	//if(module == player)
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	PERF_START(ptimer);

	// Load config from XML
	bool ret = LoadConfig();
	int cap = configApp.attribute("framerate_cap").as_int(-1);
	if (cap > 0) cappedMs = 1000 / cap;

	if (ret == true)
	{
		// Read the title from the config file
		title.create(configApp.child("title").child_value());
		win->SetTitle(title.GetString());

		ListItem<Module*>* item;
		item = modules.start;




		while (item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool App::Start()
{
	PERF_START(ptimer);

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if (ret == true)
		ret = PreUpdate();

	if (ret == true)
		ret = DoUpdate();

	if (ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
bool App::LoadConfig()
{
	bool ret = true;

	pugi::xml_parse_result result = configFile.load_file("config.xml");

	if (result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		config = configFile.child("config");
		configApp = config.child("app");

	}

	return ret;
}

void App::PrepareUpdate()
{
	// Amount of frames since startup
	frameCount++;
	lastSecFrameCount++;
	dt = frameTime.ReadSec();

	//start time
	dt = frameTime.ReadSec();
	frameTime.Start();
}

void App::FinishUpdate()
{
	if (requestLoad == true)
	{
		Load();
	}

	if (requestSave == true)
	{
		LOG("saving....");
		Save();
	}

	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	float averageFps = float(frameCount) / startupTime.ReadSec();
	float secondsSinceStartup = startupTime.ReadSec();
	uint32 lastFrameMs = frameTime.Read();
	uint32 framesOnLastUpdate = prevLastSecFrameCount;

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %02u Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, lastFrameMs, framesOnLastUpdate, dt, secondsSinceStartup, frameCount);

	app->win->SetTitle(title);

	// L08: DONE 2: Use SDL_Delay to make sure you get your capped framerate
	if ((cappedMs > 0) && (lastFrameMs < cappedMs))
	{
		// L08: DONE 3: Measure accurately the amount of time SDL_Delay actually waits compared to what was expected
		PerfTimer pt;
		SDL_Delay(cappedMs - lastFrameMs);
		LOG("We waited for %d milliseconds and got back in %f", cappedMs - lastFrameMs, pt.ReadMs());
	}
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
		{
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
		{
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for (item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if (pModule->active == false)
		{
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while (item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

int App::GetArgc() const
{
	return argc;
}

const char* App::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}

const char* App::GetTitle() const
{
	return title.GetString();
}

const char* App::GetOrganization() const
{
	return organization.GetString();
}

bool App::Load()
{
	bool ret = true;

	pugi::xml_parse_result result = saveGame.load_file("save.xml");

	if (result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		saveState = saveGame.child("saveState");
		if (saveState == NULL)
		{
			LOG("save_state not loading");
		}

		//renderer
		rend = saveState.child("render");
		if (rend == NULL)
		{
			LOG("Renderer not loading");
		}

		//input
		inp = saveState.child("input");
		if (inp == NULL)
		{
			LOG("Input not loading");
		}

		//audio
		au = saveState.child("audio");
		if (au == NULL)
		{
			LOG("Audio not loading");
		}

		//scene
		sce = saveState.child("scene");
		if (sce == NULL)
		{
			LOG("Scene not loading");
		}

		//window
		wi = saveState.child("window");
		if (wi == NULL)
		{
			LOG("window not loading");
		}

		pl = saveState.child("player");
		if (pl == NULL)
		{
			LOG("player not loading");
		}

		en = saveState.child("enemy");
		if (pl == NULL)
		{
			LOG("player not loading");
		}

	}

	app->audio->Load(au);
	app->input->Load(inp);
	app->render->Load(rend);
	app->scene->Load(sce);
	app->win->Load(wi);
	app->player->Load(pl);

	requestLoad = false;

	return ret;
}

bool App::Save()
{

	bool ret = true;
	requestSave = false;
	pugi::xml_document save;
	if (save == NULL)
	{
		LOG("save not loading");
		ret = false;
	}
	else
	{
		pugi::xml_node node = save.append_child("saveState");
		pugi::xml_node i = node.append_child("input");
		pugi::xml_node a = node.append_child("audio");

		pugi::xml_node r = node.append_child("render");
		render->Save(r);

		pugi::xml_node s = node.append_child("scene");
		scene->Save(s);

		pugi::xml_node t = node.append_child("textures");
		pugi::xml_node w = node.append_child("window");

		pugi::xml_node p = node.append_child("player");
		player->Save(p);

		pugi::xml_node e = node.append_child("enemy");

		save.save_file("save.xml");
	}




	return ret;
}