#ifndef __OBJECTMANAGER__
#define __OBJECTMANAGER_H__

#include "App.h"
#include "Module.h"
#include "Object.h"

#define MAX_OBJECTS 100



struct ObjSpawnpoint
{
	ObjType type = ObjType::NONE;
	int x, y;
};




class ObjectManager : public Module
{
public:
	// Constructor
	ObjectManager(bool startEnabled);

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	bool PreUpdate() override;
	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	bool Update(float dt) override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	bool PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	int GetTilePosx(int x);
	int GetTilePosy(int y);
	bool AddObject(ObjType type, int x, int y);

	// Add an enemy into the queue to be spawned later
	/*bool AddBall(BALL_TYPE type, int x, int y, bool right);*/

	// Iterates the queue and checks for camera position
	void HandleBallsSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandleBallsDespawn();

	//spawns new balls after destroyed ones

	//checks if all balls have been destroyed
	bool checkRemainingBalls();


	int Xoffset = 10;
	int Yoffset = 0;


	Object* objects[MAX_OBJECTS] = { nullptr };

	uint ballsLeft = 15;

	bool ballsStop = false;

private:
	// Spawns a new enemy using the data from the queue
	void SpawnObj(const ObjSpawnpoint& info);



private:
	// A queue with all spawn points information
	ObjSpawnpoint spawnQueue[MAX_OBJECTS];

	// All spawned enemies in the scene


	// The enemies sprite sheet
	SDL_Texture* coinTex = nullptr;
	SDL_Texture* heartTex = nullptr;


	// The audio fx for destroying an enemy
	int ballDestroyedFx = 0;
};

#endif // __MODULE_ENEMIES_H__

