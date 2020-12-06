#include "Debug.h"
#include "ModuleUI.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Player.h"
#include "Scene.h"
#include "Log.h"
#include "Animation.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>



ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
	name.create("moduleui");
}

bool ModuleUI::Awake(pugi::xml_node& config)
{
	//texturePath = config.child("texture").child_value();

	return true;
}

bool ModuleUI::Start()
{
	bool ret = true;
	int pixels = 24;

	fontPath = "Assets/UI/font.png";

	camaraPosx = -(app->render->camera.x) / 2;
	camaraPosy = -(app->render->camera.y) / 2;
	LOG("Loading Coin textures");

	char lookupTable[] = { "0123456789.,\"!'-�ABCDEFGHIJKLMNOPQRSTUVWXYZ.    " };
	font = Load(fontPath, lookupTable, 3);

	scoreTitle = app->tex->Load("Assets/UI/GoldText.png");
	healthTitle = app->tex->Load("Assets/UI/HealthText.png");
	singleHeart = app->tex->Load("Assets/UI/heart.png");
	healthUi = app->tex->Load("Assets/UI/healthAnim.png");

	//WAND GUI Textures
	cooldown1 = app->tex->Load("Assets/UI/Cooldown1.png");
	cooldown2 = app->tex->Load("Assets/UI/Cooldown2.png");
	cooldown3 = app->tex->Load("Assets/UI/Cooldown3.png");
	cooldown4 = app->tex->Load("Assets/UI/Cooldown4.png");
	cooldown5 = app->tex->Load("Assets/UI/Cooldown5.png");
	healGUI = app->tex->Load("Assets/UI/HealGUI.png");
	goldUi = app->tex->Load("Assets/textures/coin.png");
	cantSummon = app->tex->Load("Assets/UI/cant.png");
	fireballGUI = app->tex->Load("Assets/UI/FireBallGUI.png");

	//pressH = app->tex->Load("Assets/UI/PressH.png");

	if (healthUi == nullptr)LOG("TEXTURE NOT FOUNDED");

	//Heart Gui Animations

	oneHeart.GenerateAnimation({ 0,0,0,32 }, 5);
	oneHeart.speed = 0.3f;
	oneHeart.loop = true;

	twoHearts.GenerateAnimation({ 0,32,0,32 },5);
	twoHearts.speed = 0.3f;
	twoHearts.loop = true;

	threeHearts.GenerateAnimation({ 0,64,32,32 }, 5);
	threeHearts.speed = 0.3f;
	threeHearts.loop = true;

	fourHearts.GenerateAnimation({ 0,96,32,32 }, 5);
	fourHearts.speed = 0.3f;
	fourHearts.loop = true;

	fiveHearts.GenerateAnimation({ 0,128,32,32 }, 5);
	fiveHearts.speed = 0.3f;
	fiveHearts.loop = true;

	//texRect = { 0, 0, 640, 480};


	return ret;
}

bool ModuleUI::PreUpdate()
{


	return true;
}

bool ModuleUI::Update(float dt)
{
	write = true;
	LOG("%f", cantSumon);
	if (cantSumon <= 1.5)
	{
		cantSumon += dt;
	}
	if (cantSumon > 1.5)
	{
		cantSumon = 1.5;
	}


	return true;

}

bool ModuleUI::PostUpdate()
{
	BlitText(600, 2846, font, "LEVEL", false);
	/*app->render->DrawTexture(healthTitle, camaraPosx + 3, camaraPosy + 3);
	app->render->DrawTexture(scoreTitle, camaraPosx + ((app->render->camera.w) / 2.5), camaraPosy + 5);*/
	if (app->scene->playing == true)
	{
		HealthUi(app->player->lifes);
		WandUi();
		GoldUi();
		Draw();
	}
	
	return true;
}

void ModuleUI::Draw()
{

	int margin = 3;
	if (app->player->lifes !=0)
	{
		int maxLifes = app->player->lifes;
		for (int i = 1; i <= maxLifes; i++) 
		{
			//LOG("lifes loading: %d", i);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 65 + (24*i), camaraPosy *2 + 8, 0, 0, 0, 0, 0, false);


		}
		/*int life = app->player->lifes;
		if (life == 1)
		{
			
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
		}
		else if (life == 2)
		{
			LOG("%d", life);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90+24, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
		}
		else if (life == 3)
		{
			LOG("%d", life);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90, camaraPosy + camaraPosy +9, 0, 0, 0, 0, 0, false);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90 + 24, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
			app->render->DrawTexture(singleHeart, camaraPosx + margin + 90 + 24 + 24, camaraPosy + camaraPosy + 9, 0, 0, 0, 0, 0, false);
		}*/
	}
	app->render->DrawTexture(healthTitle, camaraPosx + margin, camaraPosy + 3, 0, 0, 0, 0, 0, false);
	app->render->DrawTexture(scoreTitle, camaraPosx + ((app->win->GetWidth()) / 2.5), camaraPosy + 5, 0, 0, 0, 0, 0, false);

	//Draw Heart Gui
	//heartRect = currentHealthAnim->GetCurrentFrame();
	//app->render->DrawTexture(healthUi, 600, 2840, &heartRect);

	
}

void ModuleUI::HealthUi(int lifesLeft)
{
	switch (lifesLeft)
	{
	case (1):
	{
		currentHealthAnim = &oneHeart;
		return;
	}
	case (2):
	{
		currentHealthAnim = &twoHearts;
		return;
	}
	case (3):
	{
		currentHealthAnim = &threeHearts;
		return;
	}
	case(4):
	{
		currentHealthAnim = &fourHearts;
		return;
	}
	case (5):
	{
		currentHealthAnim = &fiveHearts;
		return;
	}
	
	}
	currentHealthAnim->Update();
	
}

void ModuleUI::WandUi()
{
	//HEAL
	int margin = 3;
	app->render->DrawTexture(healGUI, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
	app->render->DrawTexture(fireballGUI, camaraPosx + margin + 560, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
	//app->render->DrawTexture(pressH, camaraPosx + margin + 64, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
	if (app->player->maxLifes)
	{
		if(cantSumon < 1.5)
		{
			app->render->DrawTexture(cantSummon, camaraPosx + 8, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		
		return;
	}
	if (app->player->cooldown < app->player->maxCooldown) // HEAL
	{
		float cd = app->player->cooldown;
		if (cd < 1)
		{
			app->render->DrawTexture(cooldown3, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (cd < 2 && cd > 1)
		{
			app->render->DrawTexture(cooldown2, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (cd < 3 && cd > 2)
		{
			app->render->DrawTexture(cooldown1, camaraPosx + margin + 5, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
	} 
	if (app->player->fireCooldown < app->player->fireMaxCooldown)	//FIREBALL
	{
		float fireCd = app->player->fireCooldown;
		if (fireCd < 1)
		{
			app->render->DrawTexture(cooldown5, camaraPosx + margin + 560, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (fireCd < 2 && fireCd > 1)
		{
			app->render->DrawTexture(cooldown4, camaraPosx + margin + 560, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (fireCd < 3 && fireCd > 2)
		{
			app->render->DrawTexture(cooldown3, camaraPosx + margin + 560, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (fireCd < 4 && fireCd > 3)
		{
			app->render->DrawTexture(cooldown2, camaraPosx + margin + 560, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
		else if (fireCd < 5 && fireCd > 4)
		{
			app->render->DrawTexture(cooldown1, camaraPosx + margin + 560, camaraPosy + ((app->render->camera.h) / 2.5), 0, 0, 0, 0, 0, false);
		}
	}


}

void ModuleUI::GoldUi()
{

	int maxGold = app->player->goldScore;
	for (int i = 0; i < maxGold; i++)
	{
		//LOG("lifes loading: %d", i);
		app->render->DrawTexture(goldUi, camaraPosx + ((app->win->GetWidth()) / 2.5) + 83, camaraPosy + 10 + (24 * i), 0, 0, 0, 0, 0, false);

	}



}

void ModuleUI::BlitText(int x, int y, int font_id, const char* text, bool useCamera) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].texture == nullptr)
	{
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect spriteRect;
	uint len = strlen(text);

	spriteRect.w = font->char_w;
	spriteRect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		uint charIndex = 0;

		// Find the location of the current character in the lookup table
		for (uint j = 0; j < font->totalLength; ++j)
		{
			if (font->table[j] == text[i])
			{
				charIndex = j;
				break;
			}
		}

		// Retrieve the position of the current character in the sprite
		spriteRect.x = spriteRect.w * (charIndex % font->columns);
		spriteRect.y = spriteRect.h * (charIndex / font->columns);

		app->render->DrawTexture(font->texture, x, y, &spriteRect, 1.0f, 0.0f, INT_MAX, INT_MAX, useCamera);

		// Advance the position where we blit the next character
		x += spriteRect.w;
	}
}

int ModuleUI::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		return id;
	}

	SDL_Texture* tex = app->tex->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].texture == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		return id;
	}

	Font& font = fonts[id];

	font.texture = tex;
	font.rows = rows;

	// TODO 1: Finish storing font data

	// totalLength ---	length of the lookup table
	// table ---------  All characters displayed in the same order as the texture
	// columns -------  Amount of chars per row of the texture
	// char_w --------	Width of each character
	// char_h --------	Height of each character

	strcpy_s(fonts[id].table, MAX_FONT_CHARS, characters);
	font.totalLength = strlen(characters);
	font.columns = fonts[id].totalLength / rows;

	uint tex_w, tex_h;
	app->tex->GetSize(tex, tex_w, tex_h);
	font.char_w = tex_w / font.columns;
	font.char_h = tex_h / font.rows;


	k++;

	return id;
}


