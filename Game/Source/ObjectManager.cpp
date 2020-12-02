#include "App.h"
#include "ObjectManager.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Input.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL.h"
#include "Scene.h"
#include "Player.h"
#include "Log.h"


#define SPAWN_MARGIN 50


ObjectManager::ObjectManager(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
		coins[i] = nullptr;
}

bool ObjectManager::Start()
{
	//switch (App->scene->levelSelection) //depending on the level set cursos to its pertinent position
	//{
	//case(1):
	//	texture = App->textures->Load("Assets/balls.png");
	//	break;
	//case(2):
	//	texture = App->textures->Load("Assets/balls_blue.png");
	//	break;
	//case(3):
	//	texture = App->textures->Load("Assets/balls_green.png");
	//	break;
	//case(4):
	//	texture = App->textures->Load("Assets/balls.png");
	//	break;
	//case(5):
	//	texture = App->textures->Load("Assets/balls_blue.png");
	//	break;
	//case(6):
	//	texture = App->textures->Load("Assets/balls_green.png");
	//	break;
	//}
	////texture = App->textures->Load("Assets/balls.png");
	//ballDestroyedFx = App->audio->LoadFx("Assets/[FX]-Ballon pop.wav");

	return true;
}

bool ObjectManager::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	/*for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (coins[i] != nullptr && coins[i]->pendingToDelete)
		{
			delete coins[i];
			coins[i] = nullptr;
		}
	}*/

	return true;
}

bool ObjectManager::Update(float dt)
{

	HandleBallsSpawn();
	/*TileColision();*/

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		/*TileColision();*/

	/*	if (coins[i] != nullptr)
			coins[i]->Update();*/

	}

	HandleBallsDespawn();

	return true;

}

bool ObjectManager::PostUpdate()
{

	/*for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (coins[i] != nullptr)
			coins[i]->Draw();
	}*/

	return true;
}

// Called before quitting
bool ObjectManager::CleanUp()
{
	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (coins[i] != nullptr)
		{
			delete coins[i];
			coins[i] = nullptr;
		}

	}

	return true;
}

void ObjectManager::HandleBallsSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		//if (spawnQueue[i].type != BALL_TYPE::NO_TYPE)
		//{
		//	// Spawn a new enemy if the screen has reached a spawn position
		//	if (spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
		//	{
		//		LOG("Spawning Ball at %d", spawnQueue[i].x * SCREEN_SIZE);

		//		SpawnBall(spawnQueue[i]);
		//		spawnQueue[i].type = BALL_TYPE::NO_TYPE; // Removing the newly spawned enemy from the queue
		//	}
		//}
	}
}

void ObjectManager::HandleBallsDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (coins[i] != nullptr)
		{
			//// Delete the enemy when it has reached the end of the screen
			//if (coins[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			//{
			//	LOG("DeSpawning enemy at %d", coins[i]->position.x * SCREEN_SIZE);

			//	coins[i]->SetToDelete();
			//}
		}
	}
}

void ObjectManager::SpawnBall(const BallSpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{
		if (coins[i] == nullptr)
		{
			//Needs the correspondant spawn for each type of ball
			/*switch (info.type)
			{
			case BALL_TYPE::BIG:
				coins[i] = new Ball(info.x, info.y, BALL_TYPE::BIG);
				if (info.right == false)
					Balls[i]->Ball_vx *= -1;
				break;
			case BALL_TYPE::MEDIUM:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::MEDIUM);
				if (info.right == false)
					Balls[i]->Ball_vx *= -1;
				break;

			case BALL_TYPE::SMALL:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::SMALL);
				if (info.right == false)
					Balls[i]->Ball_vx *= -1;
				break;

			case BALL_TYPE::TINY:
				Balls[i] = new Ball(info.x, info.y, BALL_TYPE::TINY);
				if (info.right == false)
					Balls[i]->Ball_vx *= -1;
				break;
			}

			Balls[i]->texture = texture;
			Balls[i]->destroyedFx = ballDestroyedFx;
			break;*/
		}
	}
}


void ObjectManager::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_OBJECTS; ++i)
	{

		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::ROPE)
		//{
		//	coins[i]->OnCollision(c2);
		//	delete Balls[i];
		//	Balls[i] = nullptr;

		//	break;
		//}

		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_A) {
		//	App->balls->Balls[i]->position.y += 5;
		//	coins[i]->Ball_vx *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::WALL_D) {

		//	coins[i]->Ball_vx *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::FLOOR) {

		//	App->balls->Balls[i]->OnCollision(c2);

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::TOP) {

		//	coins[i]->Ball_vy *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTT) {

		//	App->balls->Balls[i]->OnCollision(c2);

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTD) {
		//	App->balls->Balls[i]->position.y += 5;
		//	Balls[i]->Ball_vy *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTR) {

		//	coins[i]->Ball_vx *= -1;

		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTL) {

		//	Balls[i]->Ball_vx *= -1;
		//}
		//if (coins[i] != nullptr && coins[i]->GetCollider() == c1 && c2->type == Collider::Type::STRUCTT2) {

		//	App->balls->Balls[i]->OnCollision(c2);

		//}
	}
}

int ObjectManager::GetTilePosx(int x) {

	int Tx = 0;
	Tx = x / 8;


	return Tx;
}
int ObjectManager::GetTilePosy(int y) {

	int Ty = 0;
	Ty = y / 8;
	return Ty;

}


void ObjectManager::DivideBalls()
{
	//This function divide and plays the explosion animation
	//And also, the function Random, ads a drop when the ball explodes
	for (uint i = 0; i < MAX_OBJECTS; ++i) {
		//Big=1, Medium=2,Small=3,Tiny=4

		/*if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::BIG) {

			App->particles->bigExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::MEDIUM, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::MEDIUM, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->particles->AddParticle(App->particles->bigExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);
			App->interfaceElements->AddDrop(App->interfaceElements->score400, Balls[i]->position.x, Balls[i]->position.y, DROP_TYPE::SCORE);

			App->audio->PlayFx(ballDestroyedFx);

			App->player->playerScore += 400;
			ballsLeft--;

			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::MEDIUM) {

			App->particles->mediumExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::SMALL, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::SMALL, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->particles->AddParticle(App->particles->mediumExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);
			App->interfaceElements->AddDrop(App->interfaceElements->score800, Balls[i]->position.x, Balls[i]->position.y, DROP_TYPE::SCORE);

			App->audio->PlayFx(ballDestroyedFx);

			App->player->playerScore += 800;
			ballsLeft--;

			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::SMALL) {

			App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0;

			App->balls->AddBall(BALL_TYPE::TINY, Balls[i]->position.x + Xoffset, Balls[i]->position.y + Yoffset, true);
			App->balls->AddBall(BALL_TYPE::TINY, Balls[i]->position.x - Xoffset, Balls[i]->position.y + Yoffset, false);

			App->particles->AddParticle(App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);
			App->interfaceElements->AddDrop(App->interfaceElements->score1600, Balls[i]->position.x, Balls[i]->position.y, DROP_TYPE::SCORE);

			App->audio->PlayFx(ballDestroyedFx);

			App->player->playerScore += 800;
			ballsLeft--;

			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::TINY) {
			App->particles->AddParticle(App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->interfaceElements->RandomDrop(Balls[i]->position.x, Balls[i]->position.y);

			App->particles->AddParticle(App->particles->smallExplosion, Balls[i]->position.x, Balls[i]->position.y, Collider::Type::NONE, 0, PARTICLE_TYPE::EXPLOSION);

			App->audio->PlayFx(ballDestroyedFx);

			App->player->playerScore += 1600;
			ballsLeft--;

			Balls[i]->div = false;
			Balls[i]->SetToDelete();
			break;
		}

		else if (Balls[i] != nullptr && Balls[i]->div == true && Balls[i]->type == BALL_TYPE::NO_TYPE) {
			LOG("No type ball");
		}*/

	}
}


bool ObjectManager::checkRemainingBalls()
{
	int counter = 0;
	for (int i = 0; i < MAX_OBJECTS; ++i)
	{
	/*	if (Balls[i] != nullptr)
		{
			return update_status::UPDATE_CONTINUE;
			break;
			counter = 0;
		}
		else if (Balls[i] == nullptr)
		{
			counter++;
			if (counter == MAX_BALLS) {
				App->fade->FadeToBlack((Module*)App->scene, (Module*)App->win, 60);
			}

		}
		else {
			LOG("ERROR");
		}*/
	}
	return true;
}

void ObjectManager::ExplodeAll()
{
	LOG("Balls exploded");
	//This function divide and plays the explosion animation
	//And also, the function Random, ads a drop when the ball explodes
	for (uint i = 0; i < MAX_OBJECTS; ++i) {
		//Big=1, Medium=2,Small=3,Tiny=4
		if (coins[i] != nullptr)
		{
			

			//if (Balls[i] != nullptr && Balls[i]->type == BALL_TYPE::BIG)
			//{
			//	Balls[i]->div = true;
			//	App->balls->DivideBalls();

			//}

			//if (Balls[i] != nullptr && Balls[i]->type == BALL_TYPE::MEDIUM)
			//{
			//	Balls[i]->div = true;
			//	App->balls->DivideBalls();

			//}

			///*if (Balls[i] != nullptr && Balls[i]->type == BALL_TYPE::SMALL)
			//{
			//	Balls[i]->div = true;
			//	App->balls->DivideBalls();

			//}*/



		}


	}
}