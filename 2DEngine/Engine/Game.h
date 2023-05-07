#pragma once
#include <vector>
#include "Window.h"
#include "RendererSDL.h"
#include <Engine/Maths/Vector2.h>
#include <Engine/AssetsManager/Assets.h>
#include "Camera.h"
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ILoading.h>
#include <Engine/Controls/InputManager.h>

using std::vector;
using std::map;

class Game
{

// Begin Singleton

public:

	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:

	Game() : isRunning(true), isUpdatingActors(false), camera(nullptr) {}

	// End Singleton

public:

	bool initialize();
	void load(ILoading* loadP);
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererSDL& getRenderer() { return renderer; }
	Camera* getCamera() { return camera; }

	int getScreenWidth();
	int getScreenHeight();

private:

	void processInput();
	void update(float dt);
	void render();
	void updateAllTransformMatrix();

	Window window;
	RendererSDL renderer;
	Camera* camera;
	ILoading* load{ nullptr };
	InputManager inputManager;
	bool isRunning;


	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	Vector2 mousePosition{ Vector2::zero };

};

