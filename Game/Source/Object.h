#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct Animation;
struct Collider;
struct SDL_Texture;


enum class ObjType
{
	NONE = -1,
	COIN,
	HEART,
	WEAPON,

	MAX
};



class Object : public Module
{
private:
	SDL_Texture* texture = nullptr;

	Animation* currentAnim = nullptr;


public:

	Object(/*int x, int y,*/bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	void SetToDelete();
	void Draw();
	SDL_Rect coll;
	SDL_Rect rect;
	

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	Animation coinMovement;


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

