#ifndef __WAND_H__
#define __WAND_H__

#include "Player.h"
#include "Input.h"
#include "Entity.h"

#include "SDL/include/SDL.h"

class Textures;

class Fireball : public Entity
{
public:

    Fireball(iPoint origin, bool isRight);

    bool Update(float dt, Input* input);

    bool Load(Textures* tex);

    bool Draw(Render* render);

    void Ability();

    void Attack();

public:

    //WandProperties
    float abilityCool = 0.0f;
    float attackCool = 0.0f;

    int lifes;
    int maxLifes;

    bool isGoingRight = true;
};
#endif // __WAND_H__