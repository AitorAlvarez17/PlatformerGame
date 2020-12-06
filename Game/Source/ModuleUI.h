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

	void HealthUi(int lifesleft);

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
	SDL_Texture* singleHeart;
	SDL_Texture* healthUi;


	SDL_Texture* cooldown1;
	SDL_Texture* cooldown2;
	SDL_Texture* cooldown3;
	SDL_Texture* healGUI;
	SDL_Texture* pressH;
	// A ptr to the current animation
	Animation* currentHealthAnim = nullptr;
	Animation oneHeart;
	Animation twoHearts;
	Animation threeHearts;
	Animation fourHearts;
	Animation fiveHearts;
	Animation sixHearts;

	bool onArea1;
	bool onArea2;
	bool onArea3;
	bool outArea;
	bool push = false;
	int tpCounter = 1;
	
	const char* texturePath;


};


#endif


