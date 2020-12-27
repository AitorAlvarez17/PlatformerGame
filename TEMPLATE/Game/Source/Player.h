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

enum PlayerAnim {

    IDLE,
    WALK,
    JUMP,
    FALLING
};

class Player: public Entity
{
public:

    Player();

    bool Start(Textures* tex);

    bool PreUpdate(float dt, Input* input, AudioManager* audio);

    bool Update(Input* input, float dt);

    bool PostUpdate(float dt);

    bool Draw(Render* render);

    void SetTexture(SDL_Texture *tex, Textures* texture);

    void UpdateState(Input* input, AudioManager* audio);

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

    Animation deadAnimR;
    Animation deadAnimL;

public:

    SDL_Texture* texture;   // Player spritesheet

    // TODO: Define all animation properties
    PlayerAnim currentAnim = PlayerAnim::IDLE;//diferentiate --- THIS IS THE STATE!
    Animation* actualAnimation = nullptr;//diferentiate --- THIS IS THE ANIMATION!!

    int width, height;
    //PlayerProperties
    float jumpSpeed = 0.0f;
    bool readyToJump = true;
    bool hitObstacle = false;
    bool isGoingRight = false;


    float vy = 0.0f;
    float speed = 0.0f;
    int jumps = 2;
    float jumpForce = 0.0f;
    float jumpForceValue = 10.0f;
    bool isJumping = false;
    float gravityForce = 30.0f;
    bool push = false;
};

#endif // __PLAYER_H__
