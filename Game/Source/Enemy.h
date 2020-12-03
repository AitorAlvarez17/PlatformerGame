#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Animation;
struct Collider;
struct SDL_Texture;
enum EnemyState {

	IDLE,
	RUNNING,
	JUMPING,
	ATTACK,
	DOUBLE_JUMPING,
	FALLING,
	DYING
};

class Enemy : public Module
{
private:
	EnemyState enemyState = EnemyState::IDLE;

	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;


public:

	Enemy(bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

private:


};


#endif
