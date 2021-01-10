#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Point.h"
#include "SString.h"
#include "Collider.h"
#include "Collisions.h"

class Collider;
enum class EntityType
{
    PLAYER,
    ENEMY,
    ITEM,   //coin o lo que sea, se cambaiara en el momento.
    DEATH,
    WIN,
    MAP,
    FIREBALL,
    TP,
    SAVEPOINT,

    UNKNOWN
};

class Entity
{
public:

    Entity(EntityType type) : type(type), active(true) {}

    virtual bool Update(float dt)
    {
        return true;
    }

    virtual void OnCollision(Collider* c1, Collider* c2)
    {

    }

    virtual void OnCollision(Collider* c1)
    {

    }

    virtual void Draw(Render* render)
    {
       
    }

public:

    EntityType type;
    bool active = true;
    bool pendingToDelete = false;
    int width, height;
    //SString name;         // Entity name identifier?
    //uint32 id;            // Entity identifier?

    int lifes;
    float cooldown;
    int godMode;

    Collider* hitbox;

    // Possible properties, it depends on how generic we
    // want our Entity class, maybe it's not renderable...
    iPoint position;        // Use a float instead?
    bool renderable = false;
    SDL_Texture* texture;
};

#endif // __ENTITY_H__