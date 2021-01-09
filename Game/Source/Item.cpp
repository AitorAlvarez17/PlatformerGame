#include "Item.h"

Item::Item(iPoint origin,ItemType type) : Entity(EntityType::ITEM)
{
	position = origin;
	iType = type;
	//set the width and the height to the requested value depending on the item etc...
	width = 32;
	height = 32;



	/*hitbox->rect.x = origin.x;
	hitbox->rect.y = origin.y;
	hitbox->rect.w = width;
	hitbox->rect.h = height;*/
}

void Item::OnCollision(Collider* c1, Collider* c2)
{
	if (c2 == hitbox)
	{
		Collider* c3 = c1;
		c1 = c2;
		c2 = c3;
	}

	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.


}

void Item::OnCollision(Collider* c1)
{
	if (c1->type == Collider::Type::PLAYER)
	{
		pendingToDelete = true;
	}
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

Item::~Item()
{
}


