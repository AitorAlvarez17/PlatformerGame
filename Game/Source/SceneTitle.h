#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "Scene.h"
#include "SceneManager.h"
#include "GuiButton.h"
#include "GuiCheckBox.h"
#include "GuiSlider.h"

#include "Animation.h"

class SceneTitle : public Scene
{
public:

    SceneTitle();
    virtual ~SceneTitle();

    bool Load(Textures* tex);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    bool Unload();

    // Declare on mouse click event
    bool OnGuiMouseClickEvent(GuiControl* control);

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
    GuiSlider* other;

    SDL_Texture* bg;
    SDL_Texture* playText;
    SDL_Texture* continueText;
    SDL_Texture* settingsText;
    SDL_Texture* creditsText;
    SDL_Texture* exitText;
    SDL_Texture* backText;

    Animation* currentAnim = nullptr;
    Animation bgAnim;

    bool credits;
    bool settings;
};

#endif // __SCENETITLE_H__
