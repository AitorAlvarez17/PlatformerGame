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
	FIREBALL,

	MAX
};



class Object : public Module
{
public:
	SDL_Texture* objText = nullptr;

	Animation* currAnim = nullptr;





	Object(int x, int y, ObjType otype,bool startEnabled);
	Object(int x, int y,int dir, ObjType otype, bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void OnCollision(Collider* a, Collider* b);
	void SetToDelete();
	void Draw();
	SDL_Rect coll;
	SDL_Rect objRect;
	

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	Animation objMov;
	Animation objMovR;
	Animation objMovL;



	Point<int> position;
	int direction = 0;
	float speed = 0.0f;
	bool active = true;

	bool pendingToDelete = false;

	int winWidth;
	int winHeigh;
	ObjType type;



	Collider* collider;

	bool push = false;

	const char* texturePath;


};


#endif

