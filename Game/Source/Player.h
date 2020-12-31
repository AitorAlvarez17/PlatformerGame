#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Textures.h"

#include "Point.h"
#include "SString.h"

#include "SDL/include/SDL.h"

class Textures;

enum PlayerAnim {

    IDLE,
    WALK,
    JUMP,
    FALLING
};

class Player: public Entity
{
public:

    Player(fPoint origin);

    bool Update(Input* input, float dt);

    bool Draw(Render* render);

    void SetTexture(SDL_Texture* tex);

    void UpdateState(Input* input);

    void UpdateLogic(float dt, Input* input);

    void ChangeState(PlayerAnim lastAnim, PlayerAnim nextAnim);


    SDL_Rect GetBounds();

    Animation idleAnimR;
    Animation idleAnimL;

    Animation runRightAnim;
    Animation runLeftAnim;

    Animation jumpRightAnim;
    Animation jumpLeftAnim;

    Animation fallRightAnim;
    Animation fallLeftAnim;
    
    Animation damageAnimR;
    Animation damageAnimL;

    Animation deadAnimR;
    Animation deadAnimL;

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim = PlayerAnim::IDLE;//diferentiate --- THIS IS THE STATE!
    Animation* actualAnimation = nullptr;//diferentiate --- THIS IS THE ANIMATION!!

    int width, height;

    //PlayerProperties
    int jumps = 2;
    float vy = 0.0f;

    bool isGoingRight = false;
    bool isJumping = false;


};

#endif // __PLAYER_H__
