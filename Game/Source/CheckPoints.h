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
	void CheckOut(); 
	void InitLevel2();
	SDL_Rect texRect;
	SDL_Rect coll;
	SDL_Rect tpColl;
	SDL_Rect tpColl2;
	SDL_Rect tpColl3;
	SDL_Rect tpEndLevel;
	
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);


	Point<int> position;
	Point<int> tp1;
	Point<int> tp2;
	Point<int> tp3;
	Point<int> endLevel;
	bool active = true;
	bool regulator = true;
	bool onTp = true;
	bool mapOpen = false;
	bool onColl = false;
	bool createLevel2 = false;
	int winWidth;
	int winHeigh;


private:

	Collider* collider;
	Collider* collidertp1;
	Collider* collidertp2;
	Collider* collidertp3;
	Collider* colliderEndLevel;

	SDL_Texture* renderedOption;

	SDL_Texture* tp1IDLE;
	SDL_Texture* tp1To2;
	SDL_Texture* tp1To3;

	SDL_Texture* tp2IDLE;
	SDL_Texture* tp2To1;
	SDL_Texture* tp2To3;

	SDL_Texture* tp3IDLE;
	SDL_Texture* tp3To1;
	SDL_Texture* tp3To2;

	SDL_Texture* OpenPhrase;
	SDL_Texture* TeleportPhrase;

	bool onArea1;
	bool onArea2;
	bool onArea3;
	bool outArea;
	bool push = false;
	int tpCounter = 1;
	const char* texturePath;


};


#endif


