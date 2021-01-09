#ifndef __SCENEGAMEPLAY_H__
#define __SCENEGAMEPLAY_H__

#include "Scene.h"
#include "Audio.h"
#include "Window.h"
#include "Map.h"
#include "Player.h"
#include "Input.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "EntityManager.h"
#include "Pathfinding.h"
#include "Item.h"
#include "Collisions.h"
#include "ModuleUI.h"

class SceneGameplay : public Scene
{
public:

    SceneGameplay(AudioManager* manager, Window* win, EntityManager* eManager, Input* input, ModuleUI* ui, Collisions* coll);
    virtual ~SceneGameplay();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool DrawWand(Render* render);

    bool DrawMoney(Render* render);

    bool DrawMenu(Render* render);

    bool DrawHealth(Render* render);

    bool Unload();

    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    Map* map;
    Player* player;
    Enemy* enemy;
    Enemy* enemy2;
    EntityManager* eManager;
    PathFinding* path;
    Collisions* collisions;
    
    SDL_Rect camera;

    bool menu;
    bool settings;
    bool credits;
    bool buffer; //for load and save sliders

    GuiButton* btnResume;
    GuiButton* btnSettings;
    GuiButton* btnBackToTitle;
    GuiButton* btnExit;
    GuiButton* btnBack;

    //Parallax BG
    SDL_Texture* olympus;
    SDL_Texture* clouds;

    //GUI
    SDL_Texture* playerText;
    SDL_Texture* enemyText;
    SDL_Texture* playText;
    SDL_Texture* continueText;
    SDL_Texture* settingsText;
    SDL_Texture* title;
    SDL_Texture* exitText;
    SDL_Texture* backText;
    SDL_Texture* habUi;
    SDL_Texture* backgroundUi;
    SDL_Texture* healthNameUi;
    SDL_Texture* marginsUi;
    SDL_Texture* marginsButtonUi;
    SDL_Texture* marginsSlidersUi;
    SDL_Texture* healHab;
    SDL_Texture* fireHab;
    SDL_Texture* hearth;
    SDL_Texture* cantSummonUi;
   

    SDL_Texture* healthBackground;
    SDL_Texture* moneyBackgroundUi;

    SDL_Texture* zero;
    SDL_Texture* one;
    SDL_Texture* two;
    SDL_Texture* three;
    SDL_Texture* four;
    SDL_Texture* five;
    SDL_Texture* six;
    SDL_Texture* seven;
    SDL_Texture* eight;
    SDL_Texture* nine;
    SDL_Texture* x;

    SDL_Texture* cd1;
    SDL_Texture* cd2;
    SDL_Texture* cd3;

    SDL_Texture* number;

    int coins;


    GuiCheckBox* fullscreen;
    GuiCheckBox* Vsync;

    GuiSlider* music;
    GuiSlider* fxVolume;

    AudioManager* aud;
    Window* win;
    Input* input;
    ModuleUI* ui;
};

#endif // __SCENEGAMEPLAY_H__
