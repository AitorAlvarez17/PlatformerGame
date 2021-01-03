#include "Enemy.h"

#include "Pathfinding.h"

#define DEFAULT_PATH_LENGTH 50

Enemy::Enemy(fPoint origin) : Entity(EntityType::ENEMY)
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

Enemy::~Enemy()
{
}
