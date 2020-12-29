#include "Item.h"

Item::Item(iPoint origin) : Entity(EntityType::ITEM)
{
	position = origin;
}

Item::~Item()
{
}
