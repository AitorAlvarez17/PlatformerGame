#include "Fireball.h"

Fireball::Fireball(iPoint origin, bool isRight) : Entity(EntityType::FIREBALL)
{
	position = origin;

	isGoingRight = isRight;

}

bool Fireball::Update(float dt, Input* input)
{



	return true;
}

void Fireball::Draw(Render* render)
{

}

void Fireball::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

