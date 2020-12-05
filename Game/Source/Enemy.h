#ifndef __ENEMY_H__
#define __ENEMY_

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "DynArray.h"

struct Animation;
struct Collider;
struct SDL_Texture;

enum EnemyType {
	GROUND,
	FLYING,

};

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
	void OnCollision(Collider* a, Collider* b);
	//bool Load(pugi::xml_node&);
	//bool Save(pugi::xml_node&);

	//Transform
	Point<int> position;

	//Physics
	int speed = 2;
	float gravityForce = 3.0f;

	//true = Right, false = left
	bool isMoving= true;
	bool isMovingRight = true;

	Animation idleAnim;
	Animation leftAnim;
	Animation rightAnim;

	Collider* enemyCollider;
	Collider* rightWall;
	Collider* leftWall;

private:


	//bool canFly = false;


};


#endif
