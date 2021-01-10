#ifndef __DEATH_H__
#define __DEATH_H__

#include "Entity.h"
#include "Point.h"
#include "SString.h"



class Death : public Entity
{
public:

	Death();
	Death(iPoint origin);

	virtual ~Death();

	//ItemType SetType(ItemType type);

	void OnCollision(Collider* c1, Collider* c2);

	void OnCollision(Collider* c1);



private:

};

#endif // __DEATH_H__
