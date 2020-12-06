#ifndef __WAND_H__
#define __WAND_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "DynArray.h"

struct Animation;
struct Collider;
struct SDL_Texture;


class Wand : public Module
{
private:
	

	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;

public:

	Wand(bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	void UpdateMovement();
	void UpdateAnim();
	void ChangeState();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	//Transform
	fPoint position;

	//Physics
	float speed = 2.0f;
	float gravityForce = 3.0f;
	float health = 20.0f;
	//true = Right, false = left
	bool isMoving= true;

	//Animations
	Animation idleAnim;
	Animation leftAnim;
	Animation rightAnim;

	Animation stunleftAnim;
	Animation stunRightAnim;

	Animation deadLeftAnim;
	Animation deadRightAnim;

	//Colliders
	Collider* enemyCollider;
	Collider* rightWall;
	Collider* leftWall;

private:

	const char* texturePath;


};


#endif
