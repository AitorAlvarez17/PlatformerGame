#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"

#include "DynArray.h"
#include "Point.h"
#include "SString.h"
#include "Render.h"

#include "SDL/include/SDL.h"

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
    Enemy(fPoint origin,EnemyType type);
    virtual ~Enemy();

    EnemyType GetType();
    EnemyType SetType(EnemyType type);

    bool Update(float dt);

    bool Draw(Render* render);

    void SetTexture(SDL_Texture* tex);

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);



private:

    DynArray<iPoint>* path;
    EnemyType eType;
public:
    SDL_Texture* texture;

};

#endif // __ENEMY_H__
