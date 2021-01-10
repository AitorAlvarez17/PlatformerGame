#ifndef __SCENE_H__
#define __SCENE_H__

#include "SString.h"

class Input;
class Render;
class Textures;
class AudioManager;
class GuiControl;

enum class SceneType
{
	LOGO,
	TITLE,
	GAMEPLAY,
	ENDING
};

class Scene
{
public:

	Scene() : active(true), loaded(false), transitionRequired(false) {}

	virtual bool Load(Textures* tex)
	{
		return true;
	}

	virtual bool PreUpdate()
	{
		return true;
	}

	virtual bool Update(Input* input, float dt)
	{
		return true;
	}

	virtual bool PostUpdate(Input* input, float dt)
	{
		return true;
	}

	virtual bool Draw(Render* render)
	{
		return true;
	}

	virtual bool Unload()
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	void TransitionToScene(SceneType scene)
	{
		transitionRequired = true;
		nextScene = scene;
	}

	// Define multiple Gui Event methods
	virtual bool OnGuiMouseClickEvent(GuiControl* control)
	{
		return true;
	}

public:

	bool active = true;
	SString name;

	// Possible properties
	bool loaded = false;

	// Transition animation properties
	bool transitionRequired;
	SceneType nextScene;
};

#endif // __SCENE_H__