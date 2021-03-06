#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "Animation.h"
#include "Input.h"
#include "Render.h"
#include "Audio.h"
#include "Textures.h"
#include "Map.h"

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

    Player(iPoint origin, AudioManager* manager);

    bool Update(Input* input, float dt);

    void Draw(Render* render);

    void SetTexture(SDL_Texture* tex);

    void FixedUpdate(Input* input, float dt);
    
    void UpdateAnim(PlayerAnim previousState, PlayerAnim newState);

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);

    void HealAbility();

    void FireballAbility();

    SDL_Rect GetBounds();

    SDL_Rect GetBoundsScaled();

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

    AudioManager* aud;
public:

    SDL_Texture* texture;   // Player spritesheet

    PlayerAnim currentAnim = PlayerAnim::IDLE;//diferentiate --- THIS IS THE STATE!
    Animation* actualAnimation = nullptr;//diferentiate --- THIS IS THE ANIMATION!!

    //PlayerProperties
    iPoint prevPos;

    int maxLifes = 4;
    int jumps = 2;
    float delayUi = 2;
    int lifes = 3;
    int coins = 0;;
    int vy = 0;
    int max = 0;

    float cooldown;
    float hitCooldown;
    float fireCooldown;

    int godMode = -1;
    int tpIndex;

    bool onColl = false;
    bool onTp = true;
    bool mapOpen = false;
    bool hitted = false;
    bool isDead = false;
    bool floor = false;

    int tpCounter = 1;

    bool onArea1;
    bool onArea2;
    bool onArea3;
    bool outArea;

    bool isGoingRight = false;

};

#endif // __PLAYER_H__
