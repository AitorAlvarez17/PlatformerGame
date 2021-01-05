#include "EntityManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Item.h"

#include "Collisions.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager(Collisions* coll) : Module()
{
	name.Create("entitymanager");
	collisions = coll;

}

// Destructor
EntityManager::~EntityManager()
{
}

// Called before render is available
bool EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity Manager");
	bool ret = true;

	return ret;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	if (!active) return true;

	return true;
}


Player* EntityManager::CreatePlayer(fPoint origin)
{
	Player* ret = nullptr;

	
	ret = new Player(origin);
	
	SDL_Rect Rect;
	Rect.x = origin.x;
	Rect.y = origin.y;
	Rect.w = ret->width;
	Rect.h = ret->height;

	// Created entities are added to the list
	/*if (ret != nullptr) entities.Add(ret);*/

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] == nullptr)
		{
			entities[i] = ret;
			break;
		}
	}

	

	ret->hitbox = collisions->AddCollider(Rect, Collider::Type::PLAYER, this);

	return ret;
}

Entity* EntityManager::CreateItem(fPoint origin, ItemType iType)
{
	Item* ret = nullptr;

	ret = new Item(origin, iType);

	SDL_Rect Rect;
	Rect.x = origin.x;
	Rect.y = origin.y;
	Rect.w = ret->width;
	Rect.h = ret->height;


	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] == nullptr)
		{
			entities[i] = ret;
			break;
		}
	}
	/*if (ret != nullptr) entities.Add(ret);*/

	ret->hitbox = collisions->AddCollider(Rect, Collider::Type::COIN, this);
	

	return ret;
}

Entity* EntityManager::CreateEnemy(fPoint origin, EnemyType eType)
{
	Enemy* ret = nullptr;

	ret = new Enemy(origin, eType);

	SDL_Rect Rect;
	Rect.x = origin.x;
	Rect.y = origin.y;
	Rect.w = ret->width;
	Rect.h = ret->height;
	
	/*if (ret != nullptr) entities.Add(ret);*/

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] == nullptr)
		{
			entities[i] = ret;
			break;
		}
	}

	ret->hitbox = collisions->AddCollider(Rect, Collider::Type::ENEMY, this);

	return ret;
}


bool EntityManager::Update(float dt)
{
	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	return true;
}

bool EntityManager::UpdateAll(float dt, bool doLogic)
{
	
	if (doLogic)
	{
		for (uint i = 0; i < MAX_ENTITIES; ++i)
		{
			if (entities[i] != nullptr)
			{
				if (entities[i]->pendingToDelete)
				{
					delete entities[i];
					entities[i] = nullptr;
				}

				entities[i]->Update(dt);
			}
			
		}
		
		// TODO: Update all entities 
	}

	

	return true;
}

void EntityManager::OnCollision(Collider* a, Collider* b)
{
	/*for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		Entity* c = entities[i];
		if (c->hitbox == a && entities[i] != nullptr)
		{
			c->OnCollision(b);
		}

	}*/
}

int EntityManager::GetTilePosx(int x) {

	int Tx = 0;
	Tx = x / 8;


	return Tx;
}

int EntityManager::GetTilePosy(int y) {

	int Ty = 0;
	Ty = y / 8;
	return Ty;

}
