#ifndef __ENTITYMANAGER_H__
#define __ENTITYMANAGER_H__

#include "Module.h"
#include "Entity.h"
#include "Item.h"
#include "Enemy.h"
#include "Fireball.h"
#include "Player.h"
#include "Collisions.h"
#include "SavePoint.h"

#include "List.h"
#include "Tp.h"

#define MAX_ENTITIES 100

class EntityManager : public Module
{
public:

	EntityManager();

	EntityManager(Collisions* coll, Textures* texture);

	// Destructor
	virtual ~EntityManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	bool Update(float dt);

	bool Draw(Render* render);

	// Called before quitting
	bool CleanUp();

	// Additional methods
	Player* CreatePlayer(iPoint origin);
	Item* CreateItem(iPoint origin,ItemType iType);
	Enemy* CreateEnemy(iPoint origin, EnemyType eType, int life, int anim);
	Tp* CreateTp(iPoint origin, int n);
	SavePoint* CreateSavePoint(iPoint origin);
	Fireball* CreateFireball(iPoint origin, int range, bool dir);

	void OnCollision(Collider* a, Collider* b);


	void DestroyEntity(Entity* entity);

	void AddEntity(Entity* entity);

	bool UpdateAll(float dt, bool doLogic);

	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	int GetTilePosx(int x);
	int GetTilePosy(int y);

public:


	Collisions* collisions;
	Textures* tex;

	Entity* entities[MAX_ENTITIES] = { nullptr };

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __ENTITYMANAGER_H__
