#include "Item.h"

Item::Item(fPoint origin) : Entity(EntityType::ITEM)
{
	position = origin;

	//set the width and the height to the requested value depending on the item etc...

	/*hitbox->rect.x = origin.x;
	hitbox->rect.y = origin.y;
	hitbox->rect.w = width;
	hitbox->rect.h = height;*/
}

Item::~Item()
{
}
