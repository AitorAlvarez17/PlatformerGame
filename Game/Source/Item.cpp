#include "Item.h"

Item::Item(fPoint origin) : Entity(EntityType::ITEM)
{
	position = origin;
}

Item::~Item()
{
}
