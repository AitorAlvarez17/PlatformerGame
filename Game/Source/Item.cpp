#include "Item.h"

Item::Item(fPoint origin,ItemType type) : Entity(EntityType::ITEM)
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

Item::~Item()
{
}


