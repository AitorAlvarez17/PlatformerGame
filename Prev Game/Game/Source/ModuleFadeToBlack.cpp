#include "ModuleFadeToBlack.h"
#include "Input.h"
#include "App.h"
#include "Render.h"
#include "Window.h"
#include "Log.h"
//#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"



ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled) : Module(startEnabled)
{
	
	
	
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	win.width = app->win->GetWidth();
	win.height = app->win->GetHeight();
	scale = app->win->GetScale();
	screenRect = { 0, 0,  static_cast<int>(win.width * scale), static_cast<int> (win.height * scale) };

	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool ModuleFadeToBlack::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		fadeStep = 1;
	}
	if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		fadeStep = 0;
	}

	if (fadeStep == 1)
	{
		SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(255.0f));
		SDL_RenderFillRect(app->render->renderer, &screenRect);
	}
	return true;
}

bool ModuleFadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	//if (currentStep == Fade_Step::NONE) return true;

	float fadeRatio = (float)frameCount / ((float)maxFadeFrames);

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(fadeRatio * 255.0f));
	SDL_RenderFillRect(app->render->renderer, &screenRect);


	return true;
}

bool ModuleFadeToBlack::FadeToBlack(Module* moduleToDisable, Module* moduleToEnable, float frames)
{
	bool ret = false;

	// If we are already in a fade process, ignore this call
	if(currentStep == Fade_Step::NONE)
	{
		currentStep = Fade_Step::TO_BLACK;
		frameCount = 0;
		maxFadeFrames = 45;

		this->moduleToDisable = moduleToDisable;
		this->moduleToEnable = moduleToEnable;

		ret = true;
	}

	return ret;
}