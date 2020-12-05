#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"

struct Animation;
struct Collider;
struct SDL_Texture;


class ModuleUI : public Module
{
private:
	SDL_Texture* texture = nullptr;



public:

	ModuleUI(bool startEnabled);
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void Draw();


	bool active = true;
	bool regulator = true;
	bool onTp = true;
	bool mapOpen = false;
	bool onColl = false;
	bool write = false;

	int winWidth;
	int winHeigh;

	int camaraPosx;
	int camaraPosy;


private:

	SDL_Texture* renderedOption;

	SDL_Texture* scoreTitle;
	SDL_Texture* healthTitle;

	bool onArea1;
	bool onArea2;
	bool onArea3;
	bool outArea;
	bool push = false;
	int tpCounter = 1;
	
	const char* texturePath;


};


#endif


