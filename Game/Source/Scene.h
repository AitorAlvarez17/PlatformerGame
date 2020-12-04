#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	enum GameplayState
		{
			TITLE_SCREEN,
			PLAYING,
			GAME_OVER_SCREEN
		};

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();


	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&);

	void LoadLevel(SString name);


	void ChangeGameplayState(GameplayState newState);
	void FadeToNewState(GameplayState newState);

public:

	bool gameStarted = false;
	bool gameOver = false;
	SString currentLevel;
	GameplayState gameplayState = TITLE_SCREEN;

private:

	SDL_Texture* img;
	SDL_Texture* bgTexture;
	SDL_Texture* bgTexture2;
	float currentFade = 0.0f;
	bool fading = false;
	GameplayState targetState = gameplayState;
	SDL_Rect fullScreenRect;
};

#endif // __SCENE_H__