#pragma once
#include <vector>
#include "Window.h"
#include "RendererSDL.h"
#include <Engine/Maths/Vector2.h>
#include <Engine/AssetsManager/Assets.h>
#include "Camera.h"
#include <Engine/ActorsComponents/Actor.h>
#include <Engine/ILoading.h>

using std::vector;
using std::map;

enum KeyState
{
	Up,
	Down,
	Pressed,
	Released
};

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

	Game() = default;

	// End Singleton

public:

	bool initialize(const char* windowName, int windowWidth, int windowHeight, Color backgroundColor);
	void loadGame(ILoading* loadP);
	void loop();
	void unload();
	void close();

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	RendererSDL& getRenderer() { return renderer; }
	Camera& getCamera() { return camera; }

	int getScreenWidth();
	int getScreenHeight();
	KeyState getKeyState(SDL_Scancode keyCode);
	bool isKeyDown(SDL_Scancode keyCode);
	bool isKeyUp(SDL_Scancode keyCode);
	bool isKeyPressed(SDL_Scancode keyCode);
	bool isKeyReleased(SDL_Scancode keyCode);
	Vector2 getMousePosition();

private:

	void processInput();
	void update(float dt);
	void render();
	void updateAllTransformMatrix();

	Window window;
	RendererSDL renderer;
	Camera camera;
	ILoading* load{ nullptr };
	bool isRunning{ true };

	bool debug{ false };
	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;

	Vector2 mousePosition{ Vector2::zero };
	map<SDL_Scancode, KeyState> keys;
	vector<SDL_Scancode> pendingKeys;
};

