#include "Collisions.h"


#include "App.h"
#include "Input.h"
#include "Log.h"
#include "Render.h"
#include "Player.h"

Collisions::Collisions(Render* rend, Textures* tex) : Module()
{
	render = rend;
	textures = tex;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::DEATH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HEART] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::TP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::SAVEPOINT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WIN] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FIREBALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	


	matrix[Collider::Type::DEATH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DEATH][Collider::Type::DEATH] = false;
	matrix[Collider::Type::DEATH][Collider::Type::HEART] = false;
	matrix[Collider::Type::DEATH][Collider::Type::COIN] = false;
	matrix[Collider::Type::DEATH][Collider::Type::TP] = false;
	matrix[Collider::Type::DEATH][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::DEATH][Collider::Type::WIN] = false;
	matrix[Collider::Type::DEATH][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::DEATH][Collider::Type::ENEMY] = true;



	matrix[Collider::Type::HEART][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HEART][Collider::Type::DEATH] = false;
	matrix[Collider::Type::HEART][Collider::Type::HEART] = false;
	matrix[Collider::Type::HEART][Collider::Type::COIN] = false;
	matrix[Collider::Type::HEART][Collider::Type::TP] = false;
	matrix[Collider::Type::HEART][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::HEART][Collider::Type::WIN] = false;
	matrix[Collider::Type::HEART][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::HEART][Collider::Type::ENEMY] = false;



	matrix[Collider::Type::COIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN][Collider::Type::DEATH] = false;
	matrix[Collider::Type::COIN][Collider::Type::HEART] = false;
	matrix[Collider::Type::COIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::TP] = false;
	matrix[Collider::Type::COIN][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::COIN][Collider::Type::WIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::COIN][Collider::Type::ENEMY] = false;



	matrix[Collider::Type::TP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TP][Collider::Type::DEATH] = false;
	matrix[Collider::Type::TP][Collider::Type::HEART] = false;
	matrix[Collider::Type::TP][Collider::Type::COIN] = false;
	matrix[Collider::Type::TP][Collider::Type::TP] = false;
	matrix[Collider::Type::TP][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::TP][Collider::Type::WIN] = false;
	matrix[Collider::Type::TP][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::TP][Collider::Type::ENEMY] = false;



	matrix[Collider::Type::SAVEPOINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::DEATH] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::HEART] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::TP] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::WIN] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::ENEMY] = false;


	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::DEATH] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::HEART] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FIREBALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;



	matrix[Collider::Type::WIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WIN][Collider::Type::DEATH] = false;
	matrix[Collider::Type::WIN][Collider::Type::HEART] = false;
	matrix[Collider::Type::WIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::WIN][Collider::Type::TP] = false;
	matrix[Collider::Type::WIN][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::WIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::WIN][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::WIN][Collider::Type::WIN] = false;


	matrix[Collider::Type::FIREBALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::DEATH] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::HEART] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::COIN] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::TP] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::FIREBALL][Collider::Type::WIN] = false;

}

// Called before render is available
bool Collisions::Awake(pugi::xml_node&)
{
	return true;
}

// Called before the first frame
bool Collisions::Start()
{
	collTex = textures->Load("Assets/Textures/Items/cherry.png");

	return true;
}

// Called each loop iteration
bool Collisions::PreUpdate()
{


	return true;
}

bool Collisions::Update(float dt)
{

	if (godMode == false)
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
						if (c1->listeners[i] != nullptr)
							c1->listeners[i]->OnCollision(c1, c2);

					for (uint i = 0; i < MAX_LISTENERS; ++i)
						if (c2->listeners[i] != nullptr)
							c2->listeners[i]->OnCollision(c2, c1);
				}

			}
		}
	}

	return true;
}

bool Collisions::Draw(Render* render)
{

	if (debug)
		DebugDraw();


	return true;

}

bool Collisions::PostUpdate()
{

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
			/*render->DrawRectangleCam(colliders[i]->rect, 255, 255, 255, alpha,true,false);*/
			break;

		case Collider::Type::FLOOR:

			break;
		case Collider::Type::PLAYER:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 0,0,255,170 }, true);
			break;
		case Collider::Type::DEATH:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 204,0,0,170 }, true);

			break;
		case Collider::Type::COIN:
		{
			SDL_Rect rec = { 0,0,32,32 };

			render->DrawRectangleScaled(1, {colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h}, { 255,204,0,170 }, true);
			break;
		}
		case Collider::Type::HEART:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 255,0,102,170 }, true);

			break;
		case Collider::Type::TP:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 0,102,255,170 }, true);

			break;
		case Collider::Type::SAVEPOINT:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 51,102,255,170 }, true);

			break;
		case Collider::Type::ENEMY:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 255,0,0,170 }, true);

			break;

			break;
		case Collider::Type::WIN:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 102,255,51,170 }, true);

			break;
		case Collider::Type::FIREBALL:
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,colliders[i]->rect.w,colliders[i]->rect.h }, { 255,102,0,170 }, true);

			break;
		}
	}
}

void Collisions::DebugRequest() {

	debug = !debug;
}