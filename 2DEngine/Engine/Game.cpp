#include "Game.h"
#include "Utilitaire/Log.h"
#include "Timer.h"


bool Game::initialize(const char* windowName, int windowWidth, int windowHeight, Color backgroundColor)
{
	bool is_window_init = window.initialize(windowName, windowWidth, windowHeight);
	bool is_renderer_init = renderer.initialize(window, backgroundColor);
	return is_window_init && is_renderer_init;
}

void Game::loadGame(ILoading* loadP)
{
	unload();
	load = loadP;
	load->load(this);
	updateAllTransformMatrix();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	if (load == nullptr) return;
	while (!actors.empty())
	{
		//delete actors.back();
		actors.pop_back();
	}

	// Resources
	Assets::clear();
	delete load;
}

void Game::close()
{
	window.close();
	SDL_Quit();
}

KeyState Game::getKeyState(SDL_Scancode keyCode)
{
	if (keys.find(keyCode) == keys.end())
	{
		return KeyState::Up;
	}
	else
	{
		return keys[keyCode];
	}
}

bool Game::isKeyDown(SDL_Scancode keyCode)
{
	KeyState state = getKeyState(keyCode);
	return state == KeyState::Pressed || state == KeyState::Down;
}

bool Game::isKeyUp(SDL_Scancode keyCode)
{
	KeyState state = getKeyState(keyCode);
	return state == KeyState::Released || state == KeyState::Up;
}

bool Game::isKeyPressed(SDL_Scancode keyCode)
{
	KeyState state = getKeyState(keyCode);
	return state == KeyState::Pressed;
}

bool Game::isKeyReleased(SDL_Scancode keyCode)
{
	KeyState state = getKeyState(keyCode);
	return state == KeyState::Released;
}

Vector2 Game::getMousePosition()
{
	return mousePosition;
}

void Game::processInput()
{
	if (!pendingKeys.empty())
	{
		for (auto itr = pendingKeys.begin(); itr != pendingKeys.end(); itr++)
		{
			SDL_Scancode key_code = *itr;
			switch (getKeyState(key_code))
			{
			case KeyState::Pressed:
				keys[key_code] = KeyState::Down;
				break;
			case KeyState::Released:
				keys[key_code] = KeyState::Up;
				break;
			}
		}
		pendingKeys.clear();
	}


	int mouse_pos_x, mouse_pos_y;
	Uint32 mouse_state = SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y); //  register mouse position and get mouse button states
	mousePosition = Vector2{ mouse_pos_x * 1.0f, mouse_pos_y * 1.0f };


	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type) //  register all type of keys (keyboard) in the map when they are pressed or released
		{
		case SDL_QUIT: //  quit game if the window quit button is pressed
			isRunning = false;
			break;

		case SDL_KEYDOWN: //  register the key as pressed in the map
			if (keys.find(event.key.keysym.scancode) == keys.end())
			{
				keys.emplace(event.key.keysym.scancode, KeyState::Pressed);
				pendingKeys.push_back(event.key.keysym.scancode);
			}
			else
			{
				if (keys[event.key.keysym.scancode] != KeyState::Down) //  prevent key to be set as pressed every two frames
				{
					keys[event.key.keysym.scancode] = KeyState::Pressed;
					pendingKeys.push_back(event.key.keysym.scancode);
				}
			}
			break;
		case SDL_KEYUP: //  register the key as released in the map
			if (keys[event.key.keysym.scancode] != KeyState::Up) //  prevent key to be set as released every two frames
			{
				keys[event.key.keysym.scancode] = KeyState::Released;
				pendingKeys.push_back(event.key.keysym.scancode);
			}
			break;
		}
	}

	//  register mouse button manually cause the way SDL treat them is different of keyboard inputs

	if ((mouse_state & 1) == 1) //  left mouse button is currently down
	{
		if (keys.find(SDL_MOUSE_LEFT) == keys.end())
		{
			keys.emplace(SDL_MOUSE_LEFT, KeyState::Pressed);
			pendingKeys.push_back(SDL_MOUSE_LEFT);
		}
		else
		{
			if (keys[SDL_MOUSE_LEFT] != KeyState::Down)
			{
				keys[SDL_MOUSE_LEFT] = KeyState::Pressed;
				pendingKeys.push_back(SDL_MOUSE_LEFT);
			}
		}
	}
	else //  left mouse button is currently up
	{
		if (keys[SDL_MOUSE_LEFT] != KeyState::Up)
		{
			keys[SDL_MOUSE_LEFT] = KeyState::Released;
			pendingKeys.push_back(SDL_MOUSE_LEFT);
		}
	}

	if ((mouse_state & 2) == 2) //  middle mouse button is currently down
	{
		if (keys.find(SDL_MOUSE_MIDDLE) == keys.end())
		{
			keys.emplace(SDL_MOUSE_MIDDLE, KeyState::Pressed);
			pendingKeys.push_back(SDL_MOUSE_MIDDLE);
		}
		else
		{
			if (keys[SDL_MOUSE_MIDDLE] != KeyState::Down)
			{
				keys[SDL_MOUSE_MIDDLE] = KeyState::Pressed;
				pendingKeys.push_back(SDL_MOUSE_MIDDLE);
			}
		}
	}
	else //  middle mouse button is currently up
	{
		if (keys[SDL_MOUSE_MIDDLE] != KeyState::Up)
		{
			keys[SDL_MOUSE_MIDDLE] = KeyState::Released;
			pendingKeys.push_back(SDL_MOUSE_MIDDLE);
		}
	}

	if ((mouse_state & 4) == 4) //  right mouse button is currently down
	{
		if (keys.find(SDL_MOUSE_RIGHT) == keys.end())
		{
			keys.emplace(SDL_MOUSE_RIGHT, KeyState::Pressed);
			pendingKeys.push_back(SDL_MOUSE_RIGHT);
		}
		else
		{
			if (keys[SDL_MOUSE_RIGHT] != KeyState::Down)
			{
				keys[SDL_MOUSE_RIGHT] = KeyState::Pressed;
				pendingKeys.push_back(SDL_MOUSE_RIGHT);
			}
		}
	}
	else //  right mouse button is currently up
	{
		if (keys[SDL_MOUSE_RIGHT] != KeyState::Up)
		{
			keys[SDL_MOUSE_RIGHT] = KeyState::Released;
			pendingKeys.push_back(SDL_MOUSE_RIGHT);
		}
	}


	//  global inputs

	if (isKeyPressed(SDL_SCANCODE_K)) //  enable or disable debug mode if K is pressed
	{
		if (debug)
		{
			Log::info("Disable debug mode");
		}
		else
		{
			Log::info("Enable debug mode");
		}
		debug = !debug;
	}

	if (isKeyPressed(SDL_SCANCODE_ESCAPE)) //  quit game if escape is pressed
	{
		isRunning = false;
	}
}

void Game::update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor : pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}

	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

int Game::getScreenWidth()
{
	return window.getWidth();
}

int Game::getScreenHeight()
{
	return window.getHeight();
}

void Game::render()
{
	updateAllTransformMatrix();
	renderer.beginDraw();
	renderer.draw();
	if (debug)
	{
		for (auto actor : actors)
		{
			actor->debugComponents(renderer);
		}
	}
	renderer.endDraw();
}

void Game::updateAllTransformMatrix()
{
	for (auto actor : actors)
	{
		actor->updateTransformMatrix();
	}
}