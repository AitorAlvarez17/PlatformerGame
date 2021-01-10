#include "SavePoint.h"

SavePoint::SavePoint(iPoint origin) : Entity(EntityType::SAVEPOINT)
{
	position = origin;
	//set the width and the height to the requested value depending on the item etc...
	width = 32;
	height = 32;



	/*hitbox->rect.x = origin.x;
	hitbox->rect.y = origin.y;
	hitbox->rect.w = width;
	hitbox->rect.h = height;*/
}

void SavePoint::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}
	OnCollision(c2);
	//aqui se meter�n las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.


}

void SavePoint::OnCollision(Collider* c1)
{
	if (c1->type == Collider::Type::PLAYER)
	{
		pendingToDelete = true;
	}
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

SavePoint::~SavePoint()
{
}

