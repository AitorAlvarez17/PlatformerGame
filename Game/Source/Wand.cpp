#include "Wand.h"
#include "Player.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "PathFinding.h"
#include "Player.h"
#include "Map.h"

#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "Audio.h"

#include "SDL/include/SDL_scancode.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>


Wand::Wand(bool startEnabled) : Module(startEnabled)
{
	name.create("enemy");
}

bool Wand::Awake(pugi::xml_node& config)
{
	LOG("Loading Wand config");
	bool ret = true;

	return ret;
}

bool Wand::Start()
{
	int pixels = 32;

	return true;
}

bool Wand::PreUpdate()
{

	return true;
}

bool Wand::Update(float dt)
{


	return true;
}

bool Wand::PostUpdate()
{
	

	return true;
}

void Wand::OnCollision(Collider* a, Collider* b) {


}


bool Wand::Save(pugi::xml_node& savedGame)
{
	

	return true;
}

bool Wand::Load(pugi::xml_node& savedPlayer)
{

	return true;
}