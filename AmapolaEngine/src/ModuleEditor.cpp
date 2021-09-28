#include "Globals.h"
#include "Application.h"
#include "Application.h"
#include "ModuleEditor.h"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init()
{
	LOG("Creating Editor Context");
	bool ret = true;


	return ret;
}

// -----------------------------------------------------------------
bool ModuleEditor::Start()
{
	LOG("Setting up the editor");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleEditor::CleanUp()
{
	LOG("Cleaning editor");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleEditor::Update(float dt)
{

	return UPDATE_CONTINUE;
}