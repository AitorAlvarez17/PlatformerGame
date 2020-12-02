#ifndef __COINS_H__
#define __COINS_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Animation;
struct Collider;
struct SDL_Texture;


class Coins : public Module
{
private:
	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;


public:

	Coins(/*int x, int y,*/bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	SDL_Rect coll;
	

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	Animation coinMovement;


	Point<int> position;
	bool active = true;

	int winWidth;
	int winHeigh;

private:

	Collider* collider;

	bool push = false;

	const char* texturePath;


};


#endif

