#include "Enemy.h"
#include "Player.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "Audio.h"

#include "SDL/include/SDL_scancode.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>


Enemy::Enemy(bool startEnabled) : Module(startEnabled)
{
	name.create("enemy");
}

bool Enemy::Awake(pugi::xml_node& config)
{

	return true;
}

bool Enemy::Start()
{
	int pixels = 32;

	position.x = 700;
	position.y = 2850;

	//load texture
	texture = app->tex->Load("Assets/textures/Rock.png");
	if (texture == nullptr)LOG("Invalid enemy Texture");

	leftAnim.loop =  true;
	leftAnim.speed  = 0.2f;
	
	idleAnim.PushBack(SDL_Rect({ 0, 32, 32, 32 }));

	leftAnim.PushBack(SDL_Rect({ 0,32,32,32 }));
	leftAnim.PushBack(SDL_Rect({ 0,64,32,32 }));
	leftAnim.PushBack(SDL_Rect({ 0,96,32,32 }));
	leftAnim.PushBack(SDL_Rect({ 0,128,32,32 }));
	leftAnim.PushBack(SDL_Rect({ 0,168,32,32 }));

	return true;
}


bool Enemy::PreUpdate()
{


	return true;
}

bool Enemy::Update(float dt)
{
	if ((position.x - app->player->position.x) < 30)
	{
		isMoving = true;
	}
	else { currentAnim = &idleAnim; }
	if (isMoving) {

		position.x -= speed;
		currentAnim = &leftAnim;
	}

	return true;
}

bool Enemy::PostUpdate()
{
	//SDL_Rect enemyRect = currentanim;
	//app->render->DrawTexture(texture, position.x, position.y, &enemyRect);

		app->render->DrawTexture(texture, position.x, position.y, &currentAnim->GetCurrentFrame());
	


	return true;
}