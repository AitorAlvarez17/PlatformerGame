#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Animation.h"

#include "DynArray.h"
#include "Point.h"
#include "SString.h"
#include "Render.h"

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
	HIT,
	DEAD
};

class Enemy : public Entity
{
public:

	Enemy();
	Enemy(fPoint origin, EnemyType type);

	virtual ~Enemy();

	SDL_Rect GetBounds();

	EnemyType GetType();

	EnemyType SetType(EnemyType type);

	bool Update(float dt);

	bool Draw(Render* render);

	void SetTexture(SDL_Texture* tex);

	void CreatePath(Map* map, iPoint pos);

	void OnCollision(Collider* c1, Collider* c2);

	void OnCollision(Collider* c1);

	void SetAnim(int i);

	void FixedUpdate(Input* input, float dt);

	void UpdateAnim(EnemyState previousState, EnemyState newState);

	SDL_Texture* texture;   // Enemy spritesheet

    EnemyType eType = EnemyType::UKNOWN; 
	EnemyState eState = EnemyState::WALK;
	Animation* actualAnimation = nullptr;

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

public:
	const DynArray<iPoint> *newPath;
	bool goingRight = false;
};

#endif // __ENEMY_H__
