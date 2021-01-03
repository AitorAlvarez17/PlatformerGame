#ifndef __WAND_H__
#define __WAND_H__

#include "Player.h"
#include "Input.h"

#include "SDL/include/SDL.h"

class Textures;

class Wand 
{
public:

    Wand(Player* player);

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

    Player* wandPlayer;

    bool isGoingRight = true;
};
#endif // __WAND_H__