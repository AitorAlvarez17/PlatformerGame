#include "Collisions.h"

#include "App.h"
#include "Input.h"
#include "Log.h"
#include "Render.h"

Collisions::Collisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL_A][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL_A][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::DEATH] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::HEART] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::COIN] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::TP] = false;
	matrix[Collider::Type::WALL_A][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::WALL_D][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL_D][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::DEATH] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::HEART] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::COIN] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::TP] = false;
	matrix[Collider::Type::WALL_D][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL_A] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL_D] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::DEATH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HEART] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SAVEPOINT] = true;

	matrix[Collider::Type::FLOOR][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::DEATH] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::HEART] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::COIN] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::TP] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::DEATH][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::DEATH][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::DEATH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DEATH][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::DEATH][Collider::Type::DEATH] = false;
	matrix[Collider::Type::DEATH][Collider::Type::HEART] = false;
	matrix[Collider::Type::DEATH][Collider::Type::COIN] = false;
	matrix[Collider::Type::DEATH][Collider::Type::TP] = false;
	matrix[Collider::Type::DEATH][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::HEART][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::HEART][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::HEART][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HEART][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::HEART][Collider::Type::DEATH] = false;
	matrix[Collider::Type::HEART][Collider::Type::HEART] = false;
	matrix[Collider::Type::HEART][Collider::Type::COIN] = false;
	matrix[Collider::Type::HEART][Collider::Type::TP] = false;
	matrix[Collider::Type::HEART][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::COIN][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::COIN][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::COIN][Collider::Type::DEATH] = false;
	matrix[Collider::Type::COIN][Collider::Type::HEART] = false;
	matrix[Collider::Type::COIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::TP] = false;
	matrix[Collider::Type::COIN][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::TP][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::TP][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::TP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TP][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::TP][Collider::Type::DEATH] = false;
	matrix[Collider::Type::TP][Collider::Type::HEART] = false;
	matrix[Collider::Type::TP][Collider::Type::COIN] = false;
	matrix[Collider::Type::TP][Collider::Type::TP] = false;
	matrix[Collider::Type::TP][Collider::Type::SAVEPOINT] = false;

	matrix[Collider::Type::SAVEPOINT][Collider::Type::WALL_A] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::WALL_D] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::DEATH] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::HEART] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::TP] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::SAVEPOINT] = false;

}

// Called before render is available
bool Collisions::Awake(pugi::xml_node&) 
{
	return true;
}

// Called before the first frame
bool Collisions::Start() 
{
	return true;
}

// Called each loop iteration
bool Collisions::PreUpdate() 
{
	
	
	return true;
}

bool Collisions::Update(float dt) 
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}

		}
	}

	return true;
}

bool Collisions::PostUpdate() 
{

	if (debug)
		DebugDraw();
	
	
	return true;
}

// Called before quitting
bool Collisions::CleanUp()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* Collisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}


void Collisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}

void Collisions::DebugDraw()
{
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case Collider::Type::NONE: // white
			app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
			break;

		case Collider::Type::FLOOR:
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case Collider::Type::PLAYER:
			app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
			break;
		case Collider::Type::DEATH:
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::COIN:
			app->render->DrawRectangle(colliders[i]->rect, 255, 207, 64, alpha);
			break;
		case Collider::Type::HEART:
			app->render->DrawRectangle(colliders[i]->rect, 0, 255, 253, alpha);
			break;
		case Collider::Type::TP:
			app->render->DrawRectangle(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case Collider::Type::SAVEPOINT:
			app->render->DrawRectangle(colliders[i]->rect, 247, 0, 255, alpha);
			break;


		}


	}

}

void Collisions::DebugRequest() {

	debug = !debug;
}