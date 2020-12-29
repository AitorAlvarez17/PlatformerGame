#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Point.h"
#include "Animation.h"

#define MAX_FONTS 100
#define MAX_FONT_CHARS 256

struct Animation;
struct Collider;
struct SDL_Texture;

struct Font
{
	// Lookup table. All characters displayed in the same order as the texture
	char table[MAX_FONT_CHARS];

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint charW, charH;
};
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
	int Load(const char* texturePath, const char* characters, uint rows = 1);
	void Draw();
	void BlitText(int x, int y, int fontIndex, const char* text, bool useCamera) const;
	void HealthUi(int lifesleft);
	void WandUi();
	void IntToString(char* buffer, int k, int length);
	void GoldUi(); 
	void SaveUI();

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

	int font = -1;

	float cantSumon;
	float standardCooldownUI;
private:

	SDL_Texture* renderedOption;

	//GUI TEXTURES
	SDL_Texture* scoreTitle;
	SDL_Texture* healthTitle;
	SDL_Texture* singleHeart;
	SDL_Texture* healthUi;
	SDL_Texture* goldUi;
	//FIRE AND HEAL TEXTURES
	SDL_Rect heartRect;
	SDL_Texture* cooldown1;
	SDL_Texture* cooldown2;
	SDL_Texture* cooldown3;
	SDL_Texture* cooldown4;
	SDL_Texture* cooldown5;
	SDL_Texture* cantSummon;
	SDL_Texture* autosave;


	SDL_Texture* healGUI;
	//SDL_Texture* pressH;
	SDL_Texture* fireballGUI;


	// LIFES ANIMATION
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
	const char* fontPath;
	int k = 0;


	Font fonts[MAX_FONTS];
};


#endif


