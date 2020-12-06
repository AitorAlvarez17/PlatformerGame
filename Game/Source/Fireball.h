#ifndef __FIREBALL_H__
#define __FIREBALL_

#include "Module.h"
#include "Point.h"
#include "Animation.h"

struct Animation;
struct Collider;
struct SDL_Texture;

class Fireball : public Module
{
private:

	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;

public:

	Fireball(bool startEnabled, fPoint spawnPos, float direction, float ballRange);
	//Fireball(fPoint spawnPos, float direction, float ballRange);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	void UpdateAnim();
	void ChangeState();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);
	void Cooldown();

	//Transform
	fPoint position;

	//Physics
	float speed = 1.0f;
	float gravityForce = 0.0f;
	float range = 0.0f;
	float directionX;

	//Animations
	Animation rightFireball;
	Animation leftFireball;

	//Collider
	Collider* fireballCollider;


private:

	const char* texturePath;

	bool direction = false;


};


#endif

