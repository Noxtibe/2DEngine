#pragma once
#include "LoadComponent.h"
#include <Engine/AssetsManager/Font.h>
#include <Engine/Utilitaire/Color.h>
#include <string>

using std::string;

class TextComponent : public LoadComponent
{

public:

	TextComponent(Actor* ownerP, Font* fontP, string textP, Color colorP, Vector2 offsetP, bool centeredP, int drawOrderP = 100);
	virtual ~TextComponent();
	TextComponent() = delete;
	TextComponent(const TextComponent&) = delete;
	TextComponent& operator=(const TextComponent&) = delete;

	virtual void recalculateSDLTexture();
	virtual void setFont(Font* fontP);
	virtual void setText(const string textP);
	virtual void draw(RendererSDL& renderer) override;

	void setCentered(bool centeredP);
	Vector2 getRealOffset();

	string getText() const { return text; }
	SDL_Texture* toSDLTexture() const { return SDLTexture; }

protected:

	Font* font{ nullptr };
	string text;
	Color color;
	SDL_Texture* SDLTexture{ nullptr };
	int width{ 0 };
	int height{ 0 };
	Vector2 offset{ Vector2::zero };
	bool centered{ false };
	float centeredOffsetX{ 0.0f };
};

