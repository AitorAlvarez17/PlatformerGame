#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "Item.h"
#include "Enemy.h"
#include "Player.h"
#include "Collisions.h"

#include "List.h"

#define MAX_ENTITIES 100

class EntityManager : public Module
{
public:

	EntityManager();

	EntityManager(Collisions* coll);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Player* CreatePlayer(fPoint origin);
	Entity* CreateItem(fPoint origin,ItemType iType);
	Entity* CreateEnemy(fPoint origin, EnemyType eType);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

	bool UpdateAll(float dt, bool doLogic);

public:


	Collisions* collisions;
	Entity* entities[MAX_ENTITIES] = { nullptr };

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __ENTITYMANAGER_H__
