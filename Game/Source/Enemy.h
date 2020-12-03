#ifndef __ENEMY_H__
#define __ENEMY_

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Animation;
struct Collider;
struct SDL_Texture;
//enum EnemyState {
//
//	IDLE,
//	RUNNING,
//	JUMPING,
//	ATTACK,
//	DOUBLE_JUMPING,
//	FALLING,
//	DYING
//};

class Enemy : public Module
{
private:
//	EnemyState enemyState = EnemyState::IDLE;

	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;

public:

	Enemy(bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	SDL_Rect coll;
	SDL_Rect rect;

	Animation idleAnimR;
	Animation idleAnimL;

	Animation runRightAnim;
	Animation runLeftAnim;

	Animation jumpRightAnim;
	Animation jumpLeftAnim;

	Animation fallRightAnim;
	Animation fallLeftAnim;

	Animation deadAnimR;
	Animation deadAnimL;


	Point<int> position;

	bool active = true;
	bool pendingToDelete = false;
	bool isDead = false;

	unsigned int speed = 7;
	int winWidth;
	int winHeigh;

private:

	Collider* collider;
	Collider* leftWall;
	Collider* RightWall;

	bool isMovingRight = true;

	bool push = false;

	const char* texturePath;

	float gravityForce = 3.0f;


};


#endif
