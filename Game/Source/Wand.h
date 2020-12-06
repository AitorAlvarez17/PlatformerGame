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
	void FireBall();

	SDL_Rect wandColl;
	//Transform
	Point<int> position;

	//Colliders

	Collider* wandCollider;
	
private:

	const char* texturePath;


};


#endif
