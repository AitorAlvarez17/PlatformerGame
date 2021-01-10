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

    Fireball(iPoint origin, int rang, bool dir); // Right = true, Left = false.

    bool Update(float dt);

    void Draw(Render* render);

    void SetTexture(SDL_Texture* tex);

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);

private:

    //Animation
    Animation* currentAnim;

    Animation rightAnim;
    Animation leftAnim;

    //Properties
    bool direction = false; 
    int range = 0;
    int counter = 0;
};
#endif // __WAND_H__