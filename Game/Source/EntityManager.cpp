#include "EntityManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Entity.h"

#include "Collisions.h"

#include "Defs.h"
#include "Log.h"

EntityManager::EntityManager(Collisions* coll, Textures* texture) : Module()
{
	name.Create("entitymanager");
	collisions = coll;
	tex = texture;

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


Player* EntityManager::CreatePlayer(iPoint origin)
{
	Player* ret = nullptr;

	
	ret = new Player(origin);
	
	SDL_Rect Rect;
	Rect.x = origin.x;
	Rect.y = origin.y;
	Rect.w = ret->width;
	Rect.h = ret->height;

	ret->hitbox = collisions->AddCollider(Rect, Collider::Type::PLAYER, this);
	ret->texture = tex->Load("");
	

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

Item* EntityManager::CreateItem(iPoint origin, ItemType iType)
{
	Item* ret = nullptr;

	ret = new Item(origin, iType);

	SDL_Rect Rect;
	Rect.x = origin.x;
	Rect.y = origin.y;
	Rect.w = ret->width;
	Rect.h = ret->height;


	if (iType == ItemType::COIN)
	{
		ret->hitbox = collisions->AddCollider(Rect, Collider::Type::COIN, this);

	}

	if (iType == ItemType::HEART)
	{
		ret->hitbox = collisions->AddCollider(Rect, Collider::Type::HEART, this);

	}


	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] == nullptr)
		{
			entities[i] = ret;
			break;
		}
	}
	/*if (ret != nullptr) entities.Add(ret);*/	

	return ret;
}

Enemy* EntityManager::CreateEnemy(iPoint origin, EnemyType eType, int life, int anim)
{
	Enemy* ret = nullptr;

	ret = new Enemy(origin, eType, life,anim);

	SDL_Rect Rect;
	Rect.x = origin.x;
	Rect.y = origin.y;
	Rect.w = ret->width;
	Rect.h = ret->height;

	ret->hitbox = collisions->AddCollider(Rect, Collider::Type::ENEMY, this);

	
	/*if (ret != nullptr) entities.Add(ret);*/

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] == nullptr)
		{
			entities[i] = ret;
			break;
		}
	}


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

					entities[i]->hitbox->pendingToDelete = true;
					delete entities[i];
					entities[i] = nullptr;
				}

				entities[i]->Update(dt);
			}
			
		}
	
	}

	

	return true;
}

bool EntityManager::Draw(Render * render)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		entities[i];
		if (entities[i] != nullptr && entities[i]->type == EntityType::ITEM)
		{
			SDL_Rect rec = { 0,0,32,32 };
			render->DrawTextureScaled(1, entities[i]->texture, entities[i]->position.x, entities[i]->position.y, &rec);
		}
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

bool EntityManager::LoadState(pugi::xml_node& data)
{
	LOG(" Entity loaded");

	entities[0]->position.x = data.child("player").attribute("position.x").as_float();
	entities[0]->position.y = data.child("player").attribute("position.y").as_float();
	entities[0]->lifes = data.child("player").attribute("lifes").as_int();
	entities[0]->cooldown = data.child("player").attribute("cooldown").as_float();
	entities[0]->godMode = data.child("player").attribute("godMode").as_int();
	entities[1]->position.x = data.child("enemy").attribute("position.x").as_float();
	entities[1]->position.y = data.child("enemy").attribute("position.y").as_float();

	return true;
}

// L02: DONE 8: Create a method to save the state of the renderer
// Save Game State
bool EntityManager::SaveState(pugi::xml_node& data) const
{
	LOG(" Entity saved");
	pugi::xml_node nodeEntities = data.append_child("enemy");
	pugi::xml_node other = data.append_child("player");
	/*for (uint i = 0; i < MAX_ENTITIES; ++i)
	{*/
	other.append_attribute("position.x") = entities[0]->position.x;
	other.append_attribute("position.y") = entities[0]->position.y;
	other.append_attribute("lifes") = entities[0]->lifes;
	other.append_attribute("cooldown") = entities[0]->cooldown;
	other.append_attribute("godMode") = entities[0]->godMode;
	nodeEntities.append_attribute("position.x") = entities[1]->position.x;
	nodeEntities.append_attribute("position.y") = entities[1]->position.y;
	//}

	return true;
}