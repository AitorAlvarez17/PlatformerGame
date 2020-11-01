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
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);

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

	Animation deadAnimRight;
	Animation deadAnimLeft;

	Point<int> position;

private:
	unsigned int speed = 3;
	unsigned int jumpForce = 0;
	unsigned int jumpForceValue = 45;

	unsigned int gravityForce = 11;
	unsigned int gravityForceValue = 11;

	Collider* collider;

	bool canMoveRight = true;
	bool canMoveLeft = true;
	bool canMoveUp = true;
	bool canMoveDown = true;
	bool flat = false;


};


#endif
