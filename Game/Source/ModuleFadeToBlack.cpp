#include "ModuleFadeToBlack.h"

#include "App.h"
#include "Render.h"
#include "Log.h"
//#include "ModulePlayer.h"

#include "SDL/include/SDL_render.h"
ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled, pugi::xml_node& config) : Module()
{

}
ModuleFadeToBlack::ModuleFadeToBlack(bool startEnabled, pugi::xml_node& config) : Module()
{
	width = config.child("resolution").attribute("width").as_int(640);
	height = config.child("resolution").attribute("height").as_int(480);
	scale = config.child("resolution").attribute("scale").as_int(1);

	screenRect = {0, 0, width * scale, height * scale};
	firstScreenRect = { 0, 0, width * scale, height * scale };
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{

}

bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");

	// Enable blending mode for transparency
	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

bool ModuleFadeToBlack::Update()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return true;

	if (currentStep == Fade_Step::TO_BLACK)
	{
		++frameCount;
		if (frameCount > maxFadeFrames)
		{
			fadePause = 0;
		//	if (!app->player->stayInLevel)
		//	{
		//		moduleToDisable->Disable();
		//		moduleToEnable->Enable();
		//	}

			currentStep = Fade_Step::FROM_BLACK;
		}
	}
	//else
	//{
	//	/*if (app->player->stayInLevel)
	//	{*/
	//		if (fadePause != 30) fadePause++;

	//		if (fadePause == 30)
	//		{
	//			--frameCount;
	//			if (frameCount <= 0)
	//			{
	//				currentStep = Fade_Step::NONE;
	//			}
	//		/*}*/
		/*} */else{
			--frameCount;
			if (frameCount <= 0)
			{
				currentStep = Fade_Step::NONE;
			}
		}
		
	/*}*/

	return true;
}

bool ModuleFadeToBlack::PostUpdate()
{
	// Exit this function if we are not performing a fade
	if (currentStep == Fade_Step::NONE) return true;

	float fadeRatio = (float)frameCount / ((float)maxFadeFrames);

	// Render the black square with alpha on the screen
	SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 0, (Uint8)(255.0f));
	screenRect.h = firstScreenRect.h * fadeRatio;
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