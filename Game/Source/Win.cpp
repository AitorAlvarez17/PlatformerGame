#include "Win.h"

Win::Win(iPoint origin) : Entity(EntityType::WIN)
{
	position = origin;
	width = 64;
	height = 64;

}

void Win::OnCollision(Collider* c1, Collider* c2)
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

void Win::OnCollision(Collider* c1)
{
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.
	if (c1->type == Collider::Type::PLAYER)
		active = true;

}

Win::~Win()
{
}


