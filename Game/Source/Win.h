#ifndef __WIN_H__
#define __WIN_H__

#include "Entity.h"
#include "Point.h"
#include "SString.h"



class Win : public Entity
{
public:

    Win();
    Win(iPoint origin);

    virtual ~Win();

    //ItemType SetType(ItemType type);

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);

    bool active = false;

private:

};

#endif // __DEATH_H__
