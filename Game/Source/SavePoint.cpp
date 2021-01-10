#include "SavePoint.h"

SavePoint::SavePoint(iPoint origin) : Entity(EntityType::SAVEPOINT)
{
	position = origin;

	//set the width and the height to the requested value depending on the item etc...
	width = 32;
	height = 32;

	saveActive = true;
}

void SavePoint::Update(Input* input, float dt)
{
	saveCoroutine += dt;

	if (saveCoroutine > 2.0f)
		saveCoroutine = 2.0f;
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
	//aqui se meterán las comparaciones entre colliders. C1 siempre sera el collider del cpp en el que estas.


}

void SavePoint::OnCollision(Collider* c1)
{
	if (c1->type == Collider::Type::PLAYER)
	{
		saveActive = false;
		saveCoroutine = 0;
	}
	//aqui se compara con otro collider, siendo c1 el collider del otro objeto.


}

SavePoint::~SavePoint()
{
}


