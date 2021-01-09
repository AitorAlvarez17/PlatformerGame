#ifndef __ITEM_H__
#define __ITEM_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

enum class ItemType
{
    HEART,
    COIN,
    UKNOWN
};



class Item : public Entity
{
public:

    Item();
    Item(iPoint origin, ItemType type);

    virtual ~Item();

    ItemType GetType();
    //ItemType SetType(ItemType type);

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);



private:
    ItemType iType;
};

#endif // __ITEM_H__
