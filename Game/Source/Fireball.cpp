#include "Fireball.h"

#define DEFAULT_RANGE 5
Fireball::Fireball(iPoint origin, int rang, bool dir) : Entity(EntityType::FIREBALL)
{
	direction = dir;
	
	//Set Properties
	if (dir) position.x = origin.x + 64;
	else position.x = origin.x - 32;

	if (rang != 0) range = rang * 64;
	else range = DEFAULT_RANGE * 64;

	position.y = origin.y;

	width = 64;
	height = 64;

	//Animation
	rightAnim.GenerateAnimation({ 0,0,32,32 }, 0, 2, 0, 0);
	rightAnim.loop = true;
	rightAnim.speed = 0.2f;

	leftAnim.GenerateAnimation({ 0,32,32,32 }, 0, 2, 0, 0);
	leftAnim.loop = true;
	leftAnim.speed = 0.2f;

	currentAnim = &leftAnim;
}

bool Fireball::Update(float dt)
{
#define SPEED 120.0f

	if (counter > range)
	{
		pendingToDelete = true;;
		return true;
	}

	if (direction)
	{
		position.x += SPEED * dt;
		currentAnim = &rightAnim;

	}
	else
	{
		position.x -= SPEED * dt;
		currentAnim = &leftAnim;
	}

	counter += SPEED * dt;
	hitbox->rect = { position.x,position.y,width,height };
	return true;
}

void Fireball::Draw(Render* render)
{
	// animation state and animation frame
	currentAnim->Update();

	SDL_Rect rec = currentAnim->GetCurrentFrame();

	if (direction == true) render->DrawTextureScaled(2, texture, position.x, position.y, &rec);	
	else render->DrawTextureScaled(2, texture, position.x, position.y, &rec);

	render->DrawRectangle({ position.x,position.y, 32,32 }, { 255,255,255,255 }, true);

}

void Fireball::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Fireball::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}
	OnCollision(c2);
	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.


}

void Fireball::OnCollision(Collider* c1)
{
	if (c1->type == Collider::Type::ENEMY)
	{
		pendingToDelete = true;
	}
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}



