#include "Death.h"

Death::Death(iPoint origin) : Entity(EntityType::DEATH)
{
	position = origin;
	width = 64;
	height = 64;

}

void Death::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}
	OnCollision(c2);
	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.


}

void Death::OnCollision(Collider* c1)
{
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

Death::~Death()
{
}


