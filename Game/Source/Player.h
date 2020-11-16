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
	bool isDead;
public:
	Player(bool startEnabled);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	SDL_Rect coll;
	void UpdateState();
	void UpdateLogic();
	void ChangeState(PlayerState previous, PlayerState next);
	

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
	float vy = 0.0f;
	unsigned int speed = 5;
	int jumps = 2;

private:
	
	int jumpForce = 0;
	int jumpForceValue = 12;
	
	float gravityForce = 1.0f;

	Collider* collider;

	bool isJumping;
	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool push = false;
	

	int winWidth;
	int winHeigh;
};


#endif
