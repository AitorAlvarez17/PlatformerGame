#include "CheckPoints.h"
#include "Log.h"
#include <math.h>




CheckPoints::CheckPoints(Input* input, Render* render, Collisions* collisions, AudioManager* audio, App* app, EntityManager* eManager, ModuleUI* ui)
{
	name.Create("checkpoints");
	this->input = input;
	this->rend = render;
	this->col = collisions;
	this->aud = audio;
	this->app = app;
	this->eManager = eManager;
	this->ui = ui;
}

CheckPoints::~CheckPoints()
{}

bool CheckPoints::Awake(pugi::xml_node& config)
{
	return true;
}

bool CheckPoints::Start()
{
	bool ret = true;

	

	return ret;
}

bool CheckPoints::PreUpdate()
{
	return true;
}

bool CheckPoints::Load(Textures* tex)
{

	

	return false;

}
bool CheckPoints::Update(float dt)
{
	return true;
}

bool CheckPoints::PostUpdate()
{
	return true;
}

void CheckPoints::CheckOut()
{
	/*if (player->coll.x != tp1.x)
	{
		//LOG("out");
	}
	else if (player->coll.x == tp1.x)
	{
		//LOG("in");
	}*/

}

void CheckPoints::OnCollision(Collider* a, Collider* b) {

}

bool CheckPoints::SaveState(pugi::xml_node& savedGame)
{
	return true;
}

bool CheckPoints::LoadState(pugi::xml_node& savedPlayer)
{
	return true;
}



