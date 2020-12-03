#include "Enemy.h"
#include "Debug.h"
#include "App.h"
#include "Input.h"
#include "Animation.h"
#include "Textures.h"
#include "Window.h"
#include "Render.h"
#include "Collisions.h"
#include "SDL/include/SDL_scancode.h"
#include "Audio.h"
#include "../Defs.h"
#include "../Log.h"
#include <math.h>

Enemy::Enemy(bool startEnabled) : Module(startEnabled)
{
}

bool Enemy::Awake(pugi::xml_node&)
{
    return false;
}

bool Enemy::Start()
{
    return false;
}

bool Enemy::PreUpdate()
{
    return false;
}

bool Enemy::Update(float dt)
{
    return false;
}

bool Enemy::PostUpdate()
{
    return false;
}
