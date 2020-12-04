#include "App.h"
#include "Animation.h"
#include "ObjectManager.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Input.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "Scene.h"
#include "Player.h"
#include "Object.h"
#include "Log.h"


#define SPAWN_MARGIN 50


ObjectManager::ObjectManager(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
		objects[i] = nullptr;
}

bool ObjectManager::Start()
{
	
	coinTex = app->tex->Load("Assets/textures/coinAnim.png");
	heartTex = app->tex->Load("Assets/textures/heartAnim.png");

	return true;
}

bool ObjectManager::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr && objects[i]->pendingToDelete)
		{
			delete objects[i];
			objects[i] = nullptr;
		}
	}

	return true;
}

bool ObjectManager::Update(float dt)
{

	HandleBallsSpawn();

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
			objects[i]->Update(dt);
	}

	HandleBallsDespawn();

	return true;

}

bool ObjectManager::PostUpdate()
{

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
			objects[i]->Draw();
	}

	return true;
}

// Called before quitting
bool ObjectManager::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			delete objects[i];
			objects[i] = nullptr;
		}

	}

	return true;
}

bool ObjectManager::AddObject(ObjType type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (spawnQueue[i].type == ObjType::NONE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;

			ret = true;
			break;
		}
	}

	return ret;
}


void ObjectManager::HandleBallsSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (spawnQueue[i].type != ObjType::NONE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			LOG("Spawning object at %d", spawnQueue[i].x);

			SpawnObj(spawnQueue[i]);
			spawnQueue[i].type = ObjType::NONE; // Removing the newly spawned enemy from the queue
		}
	}
}

void ObjectManager::HandleBallsDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
		{
			if (active == false)
			{
				objects[i]->SetToDelete();
			}
		}
	}
}

void ObjectManager::SpawnObj(const ObjSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] == nullptr)
		{

			switch (info.type)
			{
			case ObjType::COIN:
				objects[i] = new Object(info.x, info.y, ObjType::COIN,true);
				objects[i]->Start();
				break;
			case ObjType::HEART:
				objects[i] = new Object(info.x, info.y, ObjType::HEART, true);
				objects[i]->Start();
				break;

			default:
				break;
			}
			
			break;
		}
	}
}


void ObjectManager::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{

		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::ROPE)
		//{
		//	coins[i]->OnCollision(c2);
		//	delete Balls[i];
		//	Balls[i] = nullptr;

		//	break;
		//}

		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_A) {
		//	App->balls->Balls[i]->position.y += 5;
		//	coins[i]->Ball_vx *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_D) {

		//	coins[i]->Ball_vx *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::FLOOR) {

		//	App->balls->Balls[i]->OnCollision(c2);

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::TOP) {

		//	coins[i]->Ball_vy *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTT) {

		//	App->balls->Balls[i]->OnCollision(c2);

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTD) {
		//	App->balls->Balls[i]->position.y += 5;
		//	Balls[i]->Ball_vy *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTR) {

		//	coins[i]->Ball_vx *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTL) {

		//	Balls[i]->Ball_vx *= -1;
		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTT2) {

		//	App->balls->Balls[i]->OnCollision(c2);

		//}
	}
}

int ObjectManager::GetTilePosx(int x) {

	int Tx = 0;
	Tx = x / 8;


	return Tx;
}
int ObjectManager::GetTilePosy(int y) {

	int Ty = 0;
	Ty = y / 8;
	return Ty;

}





bool ObjectManager::checkRemainingBalls()
{
	int counter = 0;
	for (int i = 0; i < MAX_OBJECTS; ++i)
	{
	/*	if (Balls[i] != nullptr)
		{
			return update_status::UPDATE_CONTINUE;
			break;
			counter = 0;
		}
		else if (Balls[i] == nullptr)
		{
			counter++;
			if (counter == MAX_BALLS) {
				App->fade->FadeToBlack((Module*)App->scene, (Module*)App->win, 60);
			}

		}
		else {
			LOG("ERROR");
		}*/
	}
	return true;
}

