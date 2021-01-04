#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SceneManager.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "Input.h"
#include "GuiSlider.h"
#include "App.h"
#include "Audio.h"

#include "Animation.h"

class SceneTitle : public Scene
{
public:

    SceneTitle(AudioManager* manager, Window* window, App* app, Input* input);
    virtual ~SceneTitle();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload();

    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

    bool VsyncConfig(int checked);

    bool FullscreenConfig(int checked);

private:

    GuiButton* btnStart;
    GuiButton* btnExit;
    GuiButton* btnContinue;
    GuiButton* btnCredits;
    GuiButton* btnSettings;
    GuiButton* btnBack;

    GuiCheckBox* fullscreen;
    GuiCheckBox* Vsync;

    GuiSlider* music;
    GuiSlider* fxVolume;

    SDL_Texture* bg;
    SDL_Texture* playText;
    SDL_Texture* continueText;
    SDL_Texture* settingsText;
    SDL_Texture* creditsText;
    SDL_Texture* exitText;
    SDL_Texture* backText;
    SDL_Texture* creditsUi;
    SDL_Texture* marginsUi;
    SDL_Texture* marginsButtonUi;
    SDL_Texture* marginsSlidersUi;


    Animation* currentAnim = nullptr;
    Animation bgAnim;

    bool credits;
    bool settings;
    bool buffer;

    pugi::xml_document configFile;
    pugi::xml_node config;
    pugi::xml_node configRend;

    AudioManager* aud;
    Window* win;
    App* app;
    Input* input;
};

#endif // __SCENETITLE_H__
