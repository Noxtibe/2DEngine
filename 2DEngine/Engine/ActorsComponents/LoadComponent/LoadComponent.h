#pragma once
#include <Engine/ActorsComponents/Component.h>
#include <Engine/RendererSDL.h>

class LoadComponent : public Component
{

public:

	LoadComponent(Actor* ownerP, int drawOrderP = 100);
	virtual ~LoadComponent();
	LoadComponent() = delete;
	LoadComponent(const LoadComponent&) = delete;
	LoadComponent& operator=(const LoadComponent&) = delete;

	virtual void draw(RendererSDL& renderer);

	int getLoadOrder() const { return loadOrder; }

	void setWillLoad(bool willLoadP);

protected:

	int loadOrder;
	bool willLoad{ true };
};
