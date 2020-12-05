#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Animation;
struct Collider;
struct SDL_Texture;	

enum PlayerState {

	IDLE,
	RUNNING,
	JUMPING,
	ATTACK,
	DOUBLE_JUMPING,
	FALLING,
	DYING
};

class Player : public Module
{
private:
	PlayerState playerState = PlayerState::IDLE;
	SDL_Texture* texture = nullptr;
	
	Animation* currentAnim = nullptr;

	bool isGoingRight = false;
	unsigned int jumpsLeft = 2;
	
public:

	Player(bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	SDL_Rect coll;
	void UpdateState();
	void UpdateLogic(float dt);
	void ChangeState(PlayerState previous, PlayerState next);
	void Reload();


	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

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
	

	fPoint position;

	float vy = 0.0f;
	float speed = 0.0f;
	int jumps = 2;
	bool lvl1 = false;
	bool isDead = false;
	int lifes = 3;

	int winWidth;
	int winHeigh;

private:

	Point<int> spawnLevel1;
	Point<int> spawnLevel2;
	int jumpForce = 0;
	float jumpForceValue = 10.0f;
	
	const char* jumpFxPath;

	float gravityForce = 3.0f;

	Collider* collider;

	bool isJumping;
	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool push = false;
	
	const char* texturePath;

	
};


#endif
