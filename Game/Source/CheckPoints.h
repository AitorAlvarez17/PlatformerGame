#ifndef __CHECKPOINTS_H__
#define __CHECKPOINTS_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"

struct Animation;
struct Collider;
struct SDL_Texture;


class CheckPoints : public Module
{
private:
	SDL_Texture* texture = nullptr;



public:

	CheckPoints(bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	SDL_Rect coll;
	SDL_Rect tpColl;
	SDL_Rect tpColl2;
	SDL_Rect tpColl3;

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);


	Point<int> position;
	Point<int> tp1;
	Point<int> tp2;
	Point<int> tp3;
	bool active = true;
	bool regulator = true;
	bool onTp = true;

	int winWidth;
	int winHeigh;

private:

	Collider* collider;
	Collider* collidertp1;
	Collider* collidertp2;
	Collider* collidertp3;

	bool push = false;
	int tpcounter = 3;
	const char* texturePath;


};


#endif


