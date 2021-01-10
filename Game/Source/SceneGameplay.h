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
#include "Fireball.h"
#include "App.h"
#include "Collisions.h"
#include "ModuleUI.h"
#include "Debug.h"
#include "Font.h"

class SceneGameplay : public Scene
{
public:

    SceneGameplay(AudioManager* manager, Window* win, EntityManager* eManager, Input* input, ModuleUI* ui, Collisions* coll, App* app, CheckPoints* check, Debug* debug);
    virtual ~SceneGameplay();

    bool Load(Textures* tex);

    bool PreUpdate();

    bool Update(Input* input, float dt);

    bool PostUpdate(Input* input, float dt);

    bool Draw(Render* render);

    bool DrawWand(Render* render);

    bool DrawMoney(Render* render);

    bool DrawMenu(Render* render);

    bool DrawHealth(Render* render);

    bool DrawTp(Render* render);

    bool Unload();

    bool CleanUp();

    void DebugCheckPoints(int debug);

    bool OnGuiMouseClickEvent(GuiControl* control);

private:

    Map* map;
    Player* player;
    Win* end;
    Enemy* enemy;
    Enemy* enemy2;
    Fireball* fireball;
    EntityManager* eManager;
    PathFinding* path;
    Collisions* collisions;
    App* app;
    CheckPoints* check;
    Tp* tp;
    Tp* tp2;
    Tp* tp3;
    SavePoint* save;
    Debug* debug;
    
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
    SDL_Texture* fireballTex;
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
    SDL_Texture* saveFeedback;
    SDL_Texture* coinUi;

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

    SDL_Texture* openPhrase;
    SDL_Texture* teleportPhrase;

    SDL_Texture* healthBackground;
    SDL_Texture* moneyBackgroundUi;

    SDL_Texture* wint;
    SDL_Texture* lose;


    SDL_Texture* x;

    SDL_Texture* cd1;
    SDL_Texture* cd2;
    SDL_Texture* cd3;

    SDL_Texture* number;

    SDL_Texture* font1Tex;
    Font* font1;

    int coins;
    int debugCheckPoints;

    int capped = -1;

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
