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
	matrix[Collider::Type::PLAYER][Collider::Type::ENDLEVEL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::FIREBALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::DEATH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::DEATH][Collider::Type::DEATH] = false;
	matrix[Collider::Type::DEATH][Collider::Type::HEART] = false;
	matrix[Collider::Type::DEATH][Collider::Type::COIN] = false;
	matrix[Collider::Type::DEATH][Collider::Type::TP] = false;
	matrix[Collider::Type::DEATH][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::DEATH][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::DEATH][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::DEATH][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::DEATH][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::HEART][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HEART][Collider::Type::DEATH] = false;
	matrix[Collider::Type::HEART][Collider::Type::HEART] = false;
	matrix[Collider::Type::HEART][Collider::Type::COIN] = false;
	matrix[Collider::Type::HEART][Collider::Type::TP] = false;
	matrix[Collider::Type::HEART][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::HEART][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::HEART][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::HEART][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::HEART][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::COIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN][Collider::Type::DEATH] = false;
	matrix[Collider::Type::COIN][Collider::Type::HEART] = false;
	matrix[Collider::Type::COIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::TP] = false;
	matrix[Collider::Type::COIN][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::COIN][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::COIN][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::COIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::COIN][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::TP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::TP][Collider::Type::DEATH] = false;
	matrix[Collider::Type::TP][Collider::Type::HEART] = false;
	matrix[Collider::Type::TP][Collider::Type::COIN] = false;
	matrix[Collider::Type::TP][Collider::Type::TP] = false;
	matrix[Collider::Type::TP][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::TP][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::TP][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::TP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::TP][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::SAVEPOINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::DEATH] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::HEART] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::TP] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::SAVEPOINT][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::DEATH] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::HEART] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::TP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMYWALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::FIREBALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMYWALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;




	matrix[Collider::Type::ENEMYWALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::DEATH] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::HEART] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::TP] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::ENDLEVEL] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::ENEMYWALL] = false;


	matrix[Collider::Type::ENDLEVEL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::DEATH] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::HEART] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::TP] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::ENDLEVEL][Collider::Type::FIREBALL] = false;
	matrix[Collider::Type::ENEMYWALL][Collider::Type::ENDLEVEL] = false;


	matrix[Collider::Type::FIREBALL][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::DEATH] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::HEART] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::COIN] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::TP] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::SAVEPOINT] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::FIREBALL][Collider::Type::ENEMYWALL] = false;
	matrix[Collider::Type::FIREBALL][Collider::Type::ENDLEVEL] = false;

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
			//render->DrawRectangle(colliders[i]->rect, { 0, 255, 0, 255 });

			break;
		case Collider::Type::PLAYER:
		//	render->DrawRectangle(colliders[i]->rect, { 0, 0, 255, 255 });
			//render->DrawRectangleCam(colliders[i]->rect, { 0, 0, 255, 255 },true);
			render->DrawRectangleScaled(1, { colliders[i]->rect.x,colliders[i]->rect.y,64,64 }, { 255,0,0,255 }, true);
			break;
		case Collider::Type::DEATH:
			//render->DrawRectangle(colliders[i]->rect, { 255, 0, 0, 255 });

			break;
		case Collider::Type::COIN:
		{
			SDL_Rect rec = { 0,0,32,32 };

			render->DrawRectangleScaled(1, {colliders[i]->rect.x,colliders[i]->rect.y,64,64}, { 255,255,255,255 }, true);
			render->DrawTextureScaled(2,collTex, colliders[i]->rect.x, colliders[i]->rect.y , &rec);
			break;
		}


		case Collider::Type::HEART:
			render->DrawRectangle(colliders[i]->rect, { 0, 255, 253, 255 });

			break;
		case Collider::Type::TP:
		//	render->DrawRectangle(colliders[i]->rect, { 255, 0, 0, 255 });

			break;
		case Collider::Type::SAVEPOINT:
			//render->DrawRectangle(colliders[i]->rect, { 247, 0, 255, 255 });

			break;
		case Collider::Type::ENEMY:
			render->DrawRectangleScaled(1,colliders[i]->rect, { 247, 0, 255, 255 });

			break;
		case Collider::Type::ENEMYWALL:
			//render->DrawRectangle(colliders[i]->rect, { 247, 0, 255, 255 });

			break;
		case Collider::Type::ENDLEVEL:
			//render->DrawRectangle(colliders[i]->rect, { 255, 0, 255, 255 });

			break;
		case Collider::Type::FIREBALL:
		//	render->DrawRectangle(colliders[i]->rect, { 255, 127, 80, 255 });

			break;

		}


	}

}

void Collisions::DebugRequest() {

	debug = !debug;
}