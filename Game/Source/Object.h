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
public:
	SDL_Texture* objText = nullptr;

	Animation* currAnim = nullptr;





	Object(int x, int y, ObjType type,bool startEnabled);
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



	Point<int> position;
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

