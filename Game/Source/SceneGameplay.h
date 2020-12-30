#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"

#include "Map.h"
#include "Player.h"
#include "GuiButton.h"
#include "GuiSlider.h"

class SceneGameplay : public Scene
{
public:

    SceneGameplay();
    virtual ~SceneGameplay();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload();

    bool OnGuiMouseClickEvent(GuiControl* control);

 
private:

    Map* map;
    Player* player;

    SDL_Rect camera;

    bool menu;
    bool settings;
    
    GuiButton* btnResume;
    GuiButton* btnSettings;
    GuiButton* btnBackToTitle;
    GuiButton* btnExit;
    GuiButton* btnBack;

    SDL_Texture* playerText;
    SDL_Texture* playText;
    SDL_Texture* continueText;
    SDL_Texture* settingsText;
    SDL_Texture* title;
    SDL_Texture* exitText;
    SDL_Texture* backText;
    SDL_Texture* habUi;
    SDL_Texture* backgroundUi;
    SDL_Texture* healthNameUi;

    SDL_Texture* healthBackground;
    SDL_Texture* moneyBackgroundUi;
};

#endif // __SCENEGAMEPLAY_H__
