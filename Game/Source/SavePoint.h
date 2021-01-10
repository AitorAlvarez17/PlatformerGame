#ifndef __SAVEPOINT_H__
#define __SAVEPOINT_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

class SavePoint : public Entity
{
public:

    SavePoint();
    SavePoint(iPoint origin);

    virtual ~SavePoint();

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);



private:
};

#endif // __SAVEPOINT_H__


