#ifndef __TP_H__
#define __TP_H__

#include "Entity.h"

#include "Point.h"
#include "SString.h"

class Tp : public Entity
{
public:

    Tp();
    Tp(iPoint origin, int n);

    virtual ~Tp();

    void OnCollision(Collider* c1, Collider* c2);

    void OnCollision(Collider* c1);



private:
};

#endif // __TP_H__

