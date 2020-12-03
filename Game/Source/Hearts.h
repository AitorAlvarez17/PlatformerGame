#ifndef __HEARTS_H__
#define __HEARTS_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Animation;
struct Collider;
struct SDL_Texture;


class Hearts : public Module
{
private:
	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;


public:

	Hearts(/*int x, int y,*/bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	void SetToDelete();
	SDL_Rect coll;
	SDL_Rect rect;


	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	Animation heartMovement;


	Point<int> position;
	bool active = true;

	bool pendingToDelete = false;

	int winWidth;
	int winHeigh;

private:

	Collider* collider;

	bool push = false;

	const char* texturePath;


};


#endif


