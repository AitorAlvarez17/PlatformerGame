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
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

}

bool ObjectManager::Start()
{
	
	coinTex = app->tex->Load("Assets/textures/coin_anim.png");
	heartTex = app->tex->Load("Assets/textures/heart_anim.png");
	fireBallTex = app->tex->Load("Assets/textures/fireball_sprite.png");

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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ObjectManager::Update(float dt)
{

	HandleObjectsSpawn();

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
			objects[i]->Update(dt);
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update(dt);
	}

	HandleObjectsDespawn();

	return true;

}

bool ObjectManager::PostUpdate()
{

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (objects[i] != nullptr)
			objects[i]->Draw();
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->PostUpdate();
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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}

	}

	return true;
}

bool ObjectManager::AddObject(ObjType type, int x, int y, int dir)
{
	bool ret = false;

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (spawnQueue[i].type == ObjType::NONE)
		{
			if (type == ObjType::FIREBALL)
			{
				spawnQueue[i].type = type;
				spawnQueue[i].x = x;
				spawnQueue[i].y = y;
				spawnQueue[i].dir = dir;

			}
			else
			{
				spawnQueue[i].type = type;
				spawnQueue[i].x = x;
				spawnQueue[i].y = y;
				spawnQueue[i].dir = 0;

			}

			ret = true;
			break;

		}
	}

	return ret;
}


bool ObjectManager::AddEnemy( int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemySpawnQueue[i].type == ObjType::NONE)
		{

			enemySpawnQueue[i].type = ObjType::ENEMY;
			enemySpawnQueue[i].x = x;
			enemySpawnQueue[i].y = y;

			ret = true;
			break;
		}

	}

	return ret;
}

void ObjectManager::HandleObjectsSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (spawnQueue[i].type != ObjType::NONE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			LOG("Spawning object at %d", spawnQueue[i].x);

			SpawnObj(spawnQueue[i]);
			spawnQueue[i].type = ObjType::NONE; // Removing the newly spawned object from the queue
		}
	}
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemySpawnQueue[i].type != ObjType::NONE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			LOG("Spawning Enemy at %d", enemySpawnQueue[i].x);

			SpawnEnemy(enemySpawnQueue[i]);
			enemySpawnQueue[i].type = ObjType::NONE; // Removing the newly spawned enemy from the queue
		}
	}
}

void ObjectManager::HandleObjectsDespawn()
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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (active == false)
			{
				enemies[i]->SetToDelete();
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
			case ObjType::FIREBALL:
				objects[i] = new Object(info.x, info.y, info.dir, ObjType::FIREBALL, true);
				objects[i]->Start();
				break;

			default:
				break;
			}
			
			break;
		}
	}
}
void ObjectManager::SpawnEnemy(const EnemySpawnPoint& info)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{
			enemies[i] = new Enemy(info.x, info.y,true);
			enemies[i]->Start();

			break;
		}
	}

}

void ObjectManager::OnCollision(Collider* c1, Collider* c2)
{
	
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




