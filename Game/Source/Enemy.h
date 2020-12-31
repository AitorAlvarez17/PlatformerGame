#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

#include "DynArray.h"
#include "Point.h"
#include "SString.h"

enum class EnemyType
{
    WALKING,
    FLYING,
    UKNOWN

};

class Enemy : public Entity
{
public:

    Enemy();
    Enemy(fPoint origin);
    virtual ~Enemy();
    EnemyType GetType();
    EnemyType SetType(EnemyType type);

private:

    DynArray<iPoint>* path;
    EnemyType eType;

};

#endif // __ENEMY_H__
