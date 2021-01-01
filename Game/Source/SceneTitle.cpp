#include "SceneTitle.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "EntityManager.h"
#include "Log.h"
#include "SDL/include/SDL.h"


SceneTitle::SceneTitle()
{
    // GUI: Initialize required controls for the screen
    btnStart = new GuiButton(1, { 1280/2 - 300/2, 80, 300, 80 }, "START");
    btnStart->SetObserver(this);

    btnContinue = new GuiButton(2, { 1280 / 2 - 300 / 2, 200, 300, 80 }, "CONTINUE");
    btnContinue->SetObserver(this);

    btnSettings = new GuiButton(3, { 1280 / 2 - 300 / 2, 320, 300, 80 }, "SETTINGS");
    btnSettings->SetObserver(this);

    btnCredits = new GuiButton(4, { 1280 / 2 - 300 / 2, 440, 300, 80 }, "CREDITS");
    btnCredits->SetObserver(this); 
    
    btnExit = new GuiButton(5, { 1280/2 - 300/2, 560, 300, 80 }, "EXIT");
    btnExit->SetObserver(this);

    btnBack = new GuiButton(6, { 1280 / 2 - 300 / 2, 560, 300, 80 }, "BACK");
    btnBack->SetObserver(this);

    fullscreen = new GuiCheckBox(7, { 290, 440, 80, 80 }, "fullscreen");
    fullscreen->SetObserver(this);

    Vsync = new GuiCheckBox(8, { 890, 440, 80, 80 }, "Vsync");
    Vsync->SetObserver(this);

    music = new GuiSlider(9, { 1280 / 2 - 600 / 2, 200, 600, 30 }, "music");
    music->SetObserver(this);

    other = new GuiSlider(10, { 1280 / 2 - 600 / 2, 300, 600, 30 }, "other");
    other->SetObserver(this);

    bgAnim.GenerateAnimation({ 0,0,1280,720 }, 3, 1, 0, 0);
    bgAnim.loop = true;
    bgAnim.speed = 0.03f;
   
}

SceneTitle::~SceneTitle()
{
}

bool SceneTitle::Load(Textures* tex)
{
    bg = tex->Load(PATH("Assets/Textures/UI/", "background.png"));
    playText = tex->Load(PATH("Assets/Textures/UI/", "play.png"));
    continueText = tex->Load(PATH("Assets/Textures/UI/", "continue.png"));
    settingsText = tex->Load(PATH("Assets/Textures/UI/", "settings.png"));
    creditsText = tex->Load(PATH("Assets/Textures/UI/", "credits.png"));
    exitText = tex->Load(PATH("Assets/Textures/UI/", "exit.png"));
    backText = tex->Load(PATH("Assets/Textures/UI/", "back.png"));
    
    currentAnim = &bgAnim;
    return false;
}

bool SceneTitle::Update(Input* input, float dt)
{
    if (settings == 0 && credits == 0)
    {
        btnStart->Update(input, dt);
        btnContinue->Update(input, dt);
        btnExit->Update(input, dt);
        btnSettings->Update(input, dt);
        btnCredits->Update(input, dt);
    }
    else
    {
        btnBack->Update(input, dt);
        fullscreen->Update(input, dt);
        Vsync->Update(input, dt);
        music->Update(input, dt);
        other->Update(input, dt);
    }
     
    
     currentAnim->Update();

    return false;
}

bool SceneTitle::Draw(Render* render)
{
   // render->DrawRectangle({ 0, 0, 1280, 720 }, { 100, 200, 200, 255 });
    SDL_Rect rect = currentAnim->GetCurrentFrame();
    render->DrawTexture(bg, 0, 400, &rect);

    if (credits)
    {
        
        render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
        btnBack->Draw(render);
        render->DrawTexture(backText, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
       
    }
    else if (settings)
    {
        render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
        btnBack->Draw(render);
        render->DrawTexture(backText, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        fullscreen->Draw(render);
        Vsync->Draw(render);
        music->Draw(render);
        other->Draw(render);
    }
    else
    {
        btnStart->Draw(render);
        render->DrawTexture(playText, 490, 80, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        btnContinue->Draw(render);
        render->DrawTexture(continueText, 490, 200, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        btnExit->Draw(render);
        render->DrawTexture(exitText, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        btnSettings->Draw(render);
        render->DrawTexture(settingsText, 490, 320, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        btnCredits->Draw(render);
        render->DrawTexture(creditsText, 490, 440, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
    }
    
    return false;
}

bool SceneTitle::Unload()
{
    return false;
}

//----------------------------------------------------------
// Manage GUI events for this screen
//----------------------------------------------------------
bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{
    switch (control->type)
    {
    case GuiControlType::BUTTON:
    {
        if (control->id == 1) TransitionToScene(SceneType::GAMEPLAY);
        else if (control->id == 2) LOG("CONTINUE"); // TODO: Exit request
        else if (control->id == 3) settings = 1;
        else if (control->id == 4) credits = 1;
        else if (control->id == 5) SDL_Quit();
        else if (control->id == 6)
        {
            credits = 0;
            settings = 0;
        }
        else if (control->id == 7) LOG("fullscreen ON");
        else if (control->id == 8) LOG("Vsync ON");
       
           
    }
    default: break;
    }

    return true;
}