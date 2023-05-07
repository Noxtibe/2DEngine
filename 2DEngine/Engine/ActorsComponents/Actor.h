#pragma once
#include <vector>
#include <Engine/Maths/Vector2.h>
#include <Engine/Maths/Vector3.h>
#include <SDL_stdinc.h>
#include <Engine/Maths/Matrix4.h>
#include <Engine/Maths/Quaternion.h>

using std::vector;

class Game;
class Component;
class RendererSDL;

class Actor
{

public:

	enum class ActorState
	{
		Active, Paused, Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector3 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }
	const float get2DRotation() const { return rotation2D; }
	Vector3 getForward() const;
	Vector3 getRight() const;

	void setPosition(Vector3 positionP);
	void setScale(float scaleP);
	void setRotation(Quaternion rotationP);
	void set2DRotation(float rotation2DP);

	void update(float dt);
	void updateComponents(float dt);
	void debugComponents(RendererSDL& renderer);
	virtual void updateActor(float dt);
	void updateTransformMatrix();
	void addComponent(Component* component);
	void removeComponent(Component* component);

private:

	Game& game;
	ActorState state{ ActorState::Active };
	Vector3 position{ Vector3::zero };
	float scale{ 1.0f };
	Quaternion rotation{ Quaternion::identity };
	float rotation2D{ 0.0f };
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform{ true };

	vector<Component*> components;
};
