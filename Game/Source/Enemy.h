#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Animation.h"

#include "DynArray.h"
#include "Point.h"
#include "SString.h"
#include "Render.h"
#include "Player.h"

#include "Pathfinding.h"

#include "SDL/include/SDL.h"

enum class EnemyType
{
	WALKING,
	FLYING,
	UKNOWN
};

enum class EnemyState
{
	IDLE,
	WALK,
	JUMP,
	FALL,
	HIT,
	DEAD
};

class Enemy : public Entity
{
public:

	Enemy();
	Enemy(iPoint origin, EnemyType type, int life, int anim);

	virtual ~Enemy();

	bool Update(float dt);

	void UpdateLogic(float dt);

	bool Draw(Render* render);

	void SetTexture(SDL_Texture* tex);

	void UpdatePath(Map* map, Input* input, Player* player, float dt);

	void DrawPath();

	void OnCollision(Collider* c1, Collider* c2);

	void OnCollision(Collider* c1);

	void UpdateAnim(EnemyState newState);

	void SetAnim(int i);

	SDL_Rect GetBounds();

	EnemyType GetType() { return this->eType; }

	EnemyType SetType(EnemyType type) { eType = type; }

	void UpdateState(iPoint pos);

	//SDL_Texture* texture;   // Enemy spritesheet

	EnemyType eType = EnemyType::UKNOWN;
	EnemyState eState = EnemyState::WALK;
	Animation* actualAnimation = nullptr;

	int hasPath = -1;
private:

	//Animations
	Animation idleAnimR;
	Animation idleAnimL;

	Animation runRightAnim;
	Animation runLeftAnim;

	Animation jumpRightAnim;
	Animation jumpLeftAnim;

	Animation fallRightAnim;
	Animation fallLeftAnim;

	Animation attackAnimR;
	Animation attackAnimL;

	Animation damageAnimR;
	Animation damageAnimL;

	Animation deadAnimR;
	Animation deadAnimL;

	PathFinding* ePath;

	DynArray<iPoint> newPath; // Enemy's Path

	//Enemy Properties
	int lifes = 1;
	int counter = 0;
	bool goingRight = false;

};

#endif // __ENEMY_H__
