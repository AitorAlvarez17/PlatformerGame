#include "SceneTitle.h"

#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"
#include "EntityManager.h"
#include "App.h"
#include "Log.h"
#include "SDL/include/SDL.h"


SceneTitle::SceneTitle(AudioManager* manager, Window* window, App* app, Input* input, EntityManager* eManager)
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

    btnBack = new GuiButton(6, { 1280 / 2 - 300 / 2, 520, 300, 80 }, "BACK");
    btnBack->SetObserver(this);

    fullscreen = new GuiCheckBox(7, { 320, 400, 80, 80 }, "fullscreen");
    fullscreen->SetObserver(this);

    Vsync = new GuiCheckBox(8, { 880, 400, 80, 80 }, "Vsync");
    Vsync->SetObserver(this);

    music = new GuiSlider(9, { 1280 / 2 - 600 / 2, 170, 600, 30 }, "music");
    music->SetObserver(this);

    fxVolume = new GuiSlider(10, { 1280 / 2 - 600 / 2, 270, 600, 30 }, "other");
    fxVolume->SetObserver(this);

    bgAnim.GenerateAnimation({ 0,0,1280,720 }, 3, 1, 0, 0);
    bgAnim.loop = true;
    bgAnim.speed = 0.03f;
   
    if (app->firstSaved != true)
    {
        btnContinue->Deactivate();
    }

    buffer = true;
    this->aud = manager;
    this->win = window;
    this->app = app;
    this->input = input;
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
    creditsUi = tex->Load(PATH("Assets/Textures/UI/", "credits_panel.png"));
    marginsUi = tex->Load(PATH("Assets/Textures/UI/", "margins_ui.png"));
    marginsButtonUi = tex->Load(PATH("Assets/Textures/UI/", "margins_ui_button.png"));
    marginsSlidersUi = tex->Load(PATH("Assets/Textures/UI/", "margins_ui_music_and_fx.png"));
    
    currentAnim = &bgAnim;
    return false;
}

bool SceneTitle::Update(Input* input, float dt)
{
    if (settings && buffer)
    {
        music->slider.x = ((aud->volumeMusic * music->bounds.w / 100) + music->bounds.x) - music->bounds.w / 100;
        fxVolume->slider.x = ((aud->volumeFx * music->bounds.w / 100) + music->bounds.x) - music->bounds.w / 100;
        if (aud->fullscreenCheck)
        {
            fullscreen->checked = true;
        }
        else
        {
            fullscreen->checked = false;
        }
        if (aud->vsyncCheck)
        {
            Vsync->checked = true;
        }
        else
        {
            Vsync->checked = false;
        }
        //full screen STORED is aud->fullscreenCheck);
        //full screen checked is fullscreen->checked);
        buffer = 0;
    }
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
        fxVolume->Update(input, dt);
    }
     
    
     currentAnim->Update();

    return false;
}

bool SceneTitle::Draw(Render* render)
{
   // render->DrawRectangle({ 0, 0, 1280, 720 }, { 100, 200, 200, 255 });
    SDL_Rect rect = currentAnim->GetCurrentFrame();
    render->camera.x = 0;
    render->camera.y = 0;
    render->DrawTexture(bg, 0, 0, &rect);
    
    if (credits)
    {
        render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
        render->DrawTexture(marginsUi, 100, 50, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        btnBack->Draw(render);
        render->DrawTexture(marginsButtonUi, btnBack->bounds.x, btnBack->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        render->DrawTexture(backText, btnBack->bounds.x, btnBack->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        render->DrawTexture(creditsUi, 93, -70, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
       
    }
    else if (settings)
    {
        //BG
        render->DrawRectangle({ 100, 50, 1080, 620 }, { 100, 200, 200, 255 });
        render->DrawTexture(marginsUi, 100, 50, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        //BACK
        btnBack->Draw(render);
        render->DrawTexture(marginsButtonUi, btnBack->bounds.x, btnBack->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        render->DrawTexture(backText, btnBack->bounds.x, btnBack->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        //SLIDERS AND CHECK
        render->DrawRectangle({ fullscreen->bounds.x - 2, fullscreen->bounds.y - 2, fullscreen->bounds.w + 4, fullscreen->bounds.h + 4 }, { 0, 0, 0, 255 });//PURE UI
        fullscreen->Draw(render);
        render->DrawRectangle({ Vsync->bounds.x - 2, Vsync->bounds.y - 2, Vsync->bounds.w + 4, Vsync->bounds.h + 4 }, { 0, 0, 0, 255 });//PURE UI
        Vsync->Draw(render);
        //SLIDERS
        music->Draw(render);
        render->DrawTexture(marginsSlidersUi, music->bounds.x - 20, music->bounds.y - 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        fxVolume->Draw(render);
        render->DrawTexture(marginsSlidersUi, fxVolume->bounds.x - 20, fxVolume->bounds.y - 20, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
    }
    else
    {
        //START
        btnStart->Draw(render);
        render->DrawTexture(marginsButtonUi, btnStart->bounds.x, btnStart->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        render->DrawTexture(playText, 490, 80, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        //CONTINUE
        btnContinue->Draw(render);
        render->DrawTexture(marginsButtonUi, btnContinue->bounds.x, btnContinue->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        render->DrawTexture(continueText, 490, 200, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        //EXIT TEXT
        btnExit->Draw(render);
        render->DrawTexture(marginsButtonUi, btnExit->bounds.x, btnExit->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        render->DrawTexture(exitText, 490, 560, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        //SETTINGS 
        btnSettings->Draw(render);
        render->DrawTexture(marginsButtonUi, btnSettings->bounds.x, btnSettings->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
        render->DrawTexture(settingsText, 490, 320, 0, 0, 0, 0, 0, SDL_FLIP_NONE);
        //CREDITS
        btnCredits->Draw(render);
        render->DrawTexture(marginsButtonUi, btnCredits->bounds.x, btnCredits->bounds.y, 0, 0, 0, 0, 0, SDL_FLIP_NONE);//PURE UI
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
        aud->PlayFx(8, 0);
        if (control->id == 1)
        {
            app->newGame = true;
            TransitionToScene(SceneType::GAMEPLAY);
        }
        else if (control->id == 2)
        {
            TransitionToScene(SceneType::GAMEPLAY);
        }
        else if (control->id == 3)
        {
            settings = 1;
        }
        else if (control->id == 4) credits = 1;
        else if (control->id == 5) input->windowEvents[WE_QUIT] = 1;
        else if (control->id == 6)
        {
            credits = 0;
            settings = 0;
            
        }
        else if (control->id == 7) LOG("fullscreen ON");
        else if (control->id == 8) LOG("Vsync ON");
       
           
    }
    case GuiControlType::CHECKBOX:
    {
        aud->PlayFx(8, 0);
        if (control->id == 7)
        {
            //FULLSCREEN
            if (fullscreen->checked)
            {
                win->ChangeFullscreen(fullscreen->checked);
                aud->fullscreenCheck = 1;
                //fullscreen changed to aud->fullscreenCheck);
                //LOG("ON");
            }
            else
            {
                win->ChangeFullscreen(fullscreen->checked);
                aud->fullscreenCheck = 0;
                //fullscreen changed to aud->fullscreenCheck);
                //LOG("OFF");
            }
            
        }
        else if (control->id == 8)
        {
            //VSYNC
            if (Vsync->checked)
            {
                SDL_GL_SetSwapInterval(1);
                //SDL_HINT_RENDER_VSYNC "SDL_RENDER_VSYNC"
                aud->vsyncCheck = 1;
                //LOG("OFF");
            }
            else
            {
                SDL_GL_SetSwapInterval(0);
                aud->vsyncCheck = 0;
                //LOG("ON");
            }
            
        };
    }
    case GuiControlType::SLIDER:
    {
        aud->PlayFx(8, 0);
        if (control->id == 9)
        {
            //mixmusic = music->value;
            aud->VolumeMusic(music->value);
            aud->volumeMusic = music->value;
        }
        else if (control->id == 10)
        {
            //fxmusic = music->value
            aud->VolumeFx(fxVolume->value);
            aud->volumeFx = fxVolume->value;
        }
    }
    default: break;
    }

    return true;
}

bool SceneTitle::VsyncConfig(int checked)
{
    pugi::xml_parse_result result = configFile.load_file("config.xml");

    if (result == NULL)
    {
        LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
        return false;
    }
    else
    {

        config = configFile.child("config");
        configRend = config.child("renderer");

        
        if (checked)config.child("renderer").child("vsync").attribute("value").set_value(true);
        else config.child("renderer").child("vsync").attribute("value").set_value(false);

        LOG("%d", config.child("renderer").child("vsync").attribute("value").as_bool(false));
    }
    //LOG("%d", config.child("vsync").attribute("value").as_bool(false));
    return true;
}

bool SceneTitle::FullscreenConfig(int checked)
{
    bool ret = true;

    pugi::xml_parse_result result = configFile.load_file("config.xml");

    if (result == NULL)
    {
        LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
        return false;
    }
    else
    {
        config = configFile.child("config");
        configRend = config.child("app");

        if (checked)config.child("window").child("fullscreen").attribute("value").as_bool(true);
        else config.child("window").child("fullscreen").attribute("value").as_bool(false);
        
    }

    return true;

}