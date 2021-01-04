#include "Enemy.h"

#include "Pathfinding.h"

#define DEFAULT_PATH_LENGTH 50

Enemy::Enemy(fPoint origin, EnemyType type) : Entity(EntityType::ENEMY)
{
   // path = PathFinding::GetInstance()->CreatePath(iPoint(0, 0), iPoint(0, 0));
    position = origin;


	//set the width and the height to the requested value depending on the Enemy etc...


	width = 32;
	height = 32;



	//hitbox->rect.x = origin.x;
	//hitbox->rect.y = origin.y;
	//hitbox->rect.w = width;
	//hitbox->rect.h = height;

}

bool Enemy::Update(float dt)
{

	return true;
}

bool Enemy::Draw(Render* render)
{

	return true;
}

void Enemy::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

Enemy::~Enemy()
{
}
