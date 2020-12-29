#ifndef __WARRIOR_H__
#define __WARRIOR_

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "DynArray.h"

struct Animation;
struct Collider;
struct SDL_Texture;

enum EnemyState{
	ENEMYIDLE,
	ENEMYWALKING,
	ENEMYRUNNING,
	ENEMYSTUN,
	ENEMYDYING,

};

class Enemy : public Module
{
private:
	EnemyState eState = EnemyState::ENEMYWALKING;

	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;

public:

	Enemy(int x, int y,bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	void UpdateMovement();
	void UpdateAnim();
	void ChangeState();
	void SetToDelete();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	//Transform
	fPoint position;

	//Physics
	float speed = 2.0f;
	float gravityForce = 2.0f;
	float vy = 0.0f;
	float health = 20.0f;
	//true = Right, false = left
	bool isMoving= true;
	bool isDead = false;
	

	

	//Animations
	Animation idleAnim;
	Animation leftAnim;
	Animation rightAnim;

	Animation stunLeftAnim;
	Animation stunRightAnim;

	Animation deadLeftAnim;
	Animation deadRightAnim;

	//Colliders
	Collider* enemyCollider;
	Collider* rightWall;
	Collider* leftWall;

	bool pendingToDelete = false;

private:

	const char* texturePath;


};


#endif