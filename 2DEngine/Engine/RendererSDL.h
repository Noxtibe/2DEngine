#pragma once
#include <SDL.h>
#include "ActorsComponents/Actor.h"
#include "Utilitaire/Color.h"

class Window;
struct Rectangle;
struct Vector2;

class RendererSDL
{

public:

	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	RendererSDL();
	~RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }

	bool initialize(Window& window, Color backgroundColorP);
	void beginDraw();
	void draw();
	void endDraw();
	void close();

	void addLoadComponent(class LoadComponent* LoadComponent);
	void removeLoadComponent(class LoadComponent* LoadComponent);
	void loadLoadComponents();

	void drawRect(const Actor& actor, const Rectangle& rect, Color color);
	void drawCircle(const Actor& actor, const Vector2& circleOffset, int radius, Color color);
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip, Vector2 offset) const;
	void drawText(const Actor& actor, const class TextComponent* text, int width, int height, Vector2 offset);

	void drawDebugRect(const Actor& actor, const Rectangle& rect, Color color);
	void drawDebugCircle(const Actor& actor, const Vector2& circleOffset, int radius, Color color);

	void drawTileRect(const Rectangle& tile, Color color);
	void drawTileSprite(const Rectangle& tile, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip);
	void drawDebugTile(const Rectangle& tile, Color color);

private:

	SDL_Renderer* SDLRenderer{ nullptr };
	Color backgroundColor{ Color::black };
	std::vector<LoadComponent*> LoadComponents;
};