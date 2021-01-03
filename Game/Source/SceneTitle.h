#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SceneManager.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"
#include "Audio.h"

#include "Animation.h"

class SceneTitle : public Scene
{
public:

    SceneTitle(AudioManager* manager);
    virtual ~SceneTitle();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload();

    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

    bool VsyncConfig();

    bool FullscreenConfig();

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

    Animation* currentAnim = nullptr;
    Animation bgAnim;

    bool credits;
    bool settings;
    bool buffer;

    pugi::xml_document configFile;
    pugi::xml_node config;
    pugi::xml_node configRend;

    AudioManager* aud;
};

#endif // __SCENETITLE_H__
