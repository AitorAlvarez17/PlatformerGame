#ifndef __DEBUG_H__
#define __DEBUG_H__

#define MAX_COLLIDERS 1000

#include "Module.h"
class Debug : public Module
{
public:
	Debug(bool startEnabled);

	// Destructor
	~Debug();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	//Called at the end of the application
	bool CleanUp();

	// Switches isEnabled and calls Start() method
	void Enable();

	// Switches isEnabled and calls CleanUp() method
	void Disable();

	inline bool IsEnabled() const { return isEnabled; }


	
	bool godMode = false;
	//int levelChoose = 0;

private:
	
	bool isEnabled = true;
};
#endif // __DEBUG_H__