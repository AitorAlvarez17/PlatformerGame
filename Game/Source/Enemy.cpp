#include "Enemy.h"

#include "Pathfinding.h"

#define DEFAULT_PATH_LENGTH 50

Enemy::Enemy(fPoint origin) : Entity(EntityType::ENEMY)
{
    path = PathFinding::GetInstance()->CreatePath(iPoint(0, 0), iPoint(0, 0));
    position = origin;
}

Enemy::~Enemy()
{
}
