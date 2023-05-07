#include "RendererSDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Game.h"
#include "Window.h"
#include "Utilitaire/Log.h"
#include "Maths/Maths.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"
#include "Maths/Quaternion.h"
#include "AssetsManager/Texture.h"
#include <Engine/ActorsComponents/LoadComponent/LoadComponent.h>
#include <Engine/ActorsComponents/LoadComponent/TextComponent.h>


RendererSDL::RendererSDL() : SDLRenderer(nullptr)
{
}

RendererSDL::~RendererSDL()
{
}

bool RendererSDL::initialize(Window& window, Color backgroundColorP)
{
	SDLRenderer = SDL_CreateRenderer(
		window.getSDLWindow(), -1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC
	);

	if (!SDLRenderer)
	{
		Log::error(LogCategory::Video, "Failed to create RendererSDL");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL_image");
		return false;
	}
	if (TTF_Init() == -1)
	{
		Log::error(LogCategory::Video, "Unable to initialize SDL_ttf");
		return false;
	}
	backgroundColor = backgroundColorP;
	return true;
}

void RendererSDL::beginDraw()
{
	SDL_SetRenderDrawColor(SDLRenderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderClear(SDLRenderer);
}

void RendererSDL::draw()
{
	loadLoadComponents();
}

void RendererSDL::endDraw()
{
	SDL_RenderPresent(SDLRenderer);
}

void RendererSDL::loadLoadComponents()
{
	for (auto draw_component : LoadComponents)
	{
		draw_component->load(*this);
	}
}

void RendererSDL::drawDebugRect(const Actor& actor, const Rectangle& rect, Color color)
{
	Vector2 cam_pos = Game::instance().getCamera().getCamPos();
	SDL_Rect draw_rect;
	Vector2 position = actor.getPosition() - cam_pos;
	float scale = actor.getScale();

	draw_rect.w = static_cast<int>(rect.width * scale);
	draw_rect.h = static_cast<int>(rect.height * scale);

	draw_rect.x = static_cast<int>(rect.x + position.x);
	draw_rect.y = static_cast<int>(rect.y + position.y);


	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(SDLRenderer, &draw_rect);

}

void RendererSDL::drawDebugCircle(const Actor& actor, const Vector2& circleOffset, int radius, Color color)
{
	Vector2 cam_pos = Game::instance().getCamera().getCamPos();
	const int centre_x = static_cast<int>(actor.getPosition().x + circleOffset.x - cam_pos.x);
	const int centre_y = static_cast<int>(actor.getPosition().y + circleOffset.y - cam_pos.y);

	radius *= actor.getScale();
	const int diameter = radius * 2;

	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = tx - diameter;

	while (x >= y)
	{
		SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);

		SDL_RenderDrawPoint(SDLRenderer, centre_x + x, centre_y - y);
		SDL_RenderDrawPoint(SDLRenderer, centre_x + x, centre_y + y);
		SDL_RenderDrawPoint(SDLRenderer, centre_x - x, centre_y - y);
		SDL_RenderDrawPoint(SDLRenderer, centre_x - x, centre_y + y);
		SDL_RenderDrawPoint(SDLRenderer, centre_x + y, centre_y - x);
		SDL_RenderDrawPoint(SDLRenderer, centre_x + y, centre_y + x);
		SDL_RenderDrawPoint(SDLRenderer, centre_x - y, centre_y - x);
		SDL_RenderDrawPoint(SDLRenderer, centre_x - y, centre_y + x);

		if (error <= 0)
		{
			y++;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			x--;
			tx += 2;
			error += tx - diameter;
		}
	}
}

void RendererSDL::drawTileRect(const Rectangle& tile, Color color)
{
	SDL_Rect draw_rect;

	draw_rect.w = static_cast<int>(tile.width);
	draw_rect.h = static_cast<int>(tile.height);

	draw_rect.x = static_cast<int>(tile.x);
	draw_rect.y = static_cast<int>(tile.y);


	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(SDLRenderer, &draw_rect);
}

void RendererSDL::drawTileSprite(const Rectangle& tile, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip)
{
	SDL_Rect dst_rect;

	dst_rect.w = static_cast<int>(tile.width);
	dst_rect.h = static_cast<int>(tile.height);

	dst_rect.x = static_cast<int>(tile.x - origin.x);
	dst_rect.y = static_cast<int>(tile.y - origin.y);

	SDL_Rect* src_SDL = nullptr;
	if (srcRect != Rectangle::nullRect)
	{
		src_SDL = new SDL_Rect{ Maths::round(srcRect.x), Maths::round(srcRect.y),
			Maths::round(srcRect.width), Maths::round(srcRect.height) };
	}

	SDL_RenderCopyEx(SDLRenderer, tex.toSDLTexture(), src_SDL, &dst_rect, 0.0f, nullptr, SDL_FLIP_NONE);
	delete src_SDL;
}

void RendererSDL::drawDebugTile(const Rectangle& tile, Color color)
{
	SDL_Rect draw_rect;

	draw_rect.w = static_cast<int>(tile.width);
	draw_rect.h = static_cast<int>(tile.height);

	draw_rect.x = static_cast<int>(tile.x);
	draw_rect.y = static_cast<int>(tile.y);


	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(SDLRenderer, &draw_rect);
}

void RendererSDL::drawRect(const Actor& actor, const Rectangle& rect, Color color)
{
	Vector2 cam_pos = Game::instance().getCamera().getCamPos();
	SDL_Rect draw_rect;
	Vector2 position = actor.getPosition() - cam_pos;
	float scale = actor.getScale();

	draw_rect.w = static_cast<int>(rect.width * scale);
	draw_rect.h = static_cast<int>(rect.height * scale);

	draw_rect.x = static_cast<int>(rect.x + position.x);
	draw_rect.y = static_cast<int>(rect.y + position.y);


	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(SDLRenderer, &draw_rect);
}

void RendererSDL::drawCircle(const Actor& actor, const Vector2& circleOffset, int radius, Color color)
{
	Vector2 cam_pos = Game::instance().getCamera().getCamPos();
	const int centre_x = static_cast<int>(actor.getPosition().x + circleOffset.x - cam_pos.x);
	const int centre_y = static_cast<int>(actor.getPosition().y + circleOffset.y - cam_pos.y);
	radius *= actor.getScale();

	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(SDLRenderer, centre_x + dx, centre_y + dy);
			}
		}
	}
}

void RendererSDL::drawSprite(const Actor& actor, const Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip, Vector2 offset) const
{
	Vector2 cam_pos = Game::instance().getCamera().getCamPos();
	SDL_Rect dst_rect;
	Vector2 position = actor.getPosition() - cam_pos + offset;
	float rotation = actor.get2DRotation();
	float scale = actor.getScale();

	dst_rect.w = static_cast<int>(tex.getWidth() * scale);
	dst_rect.h = static_cast<int>(tex.getHeight() * scale);

	dst_rect.x = static_cast<int>(position.x - origin.x);
	dst_rect.y = static_cast<int>(position.y - origin.y);

	SDL_Rect* src_SDL = nullptr;
	if (srcRect != Rectangle::nullRect)
	{
		src_SDL = new SDL_Rect{ Maths::round(srcRect.x), Maths::round(srcRect.y),
			Maths::round(srcRect.width), Maths::round(srcRect.height) };
	}

	SDL_RendererFlip sdl_flip = SDL_FLIP_NONE;
	switch (flip)
	{
	case Flip::Horizontal:
		sdl_flip = SDL_FLIP_HORIZONTAL;
		break;
	case Flip::Vertical:
		sdl_flip = SDL_FLIP_VERTICAL;
		break;
	}

	SDL_RenderCopyEx(SDLRenderer, tex.toSDLTexture(), src_SDL, &dst_rect, -Maths::toDegrees(rotation), nullptr, sdl_flip);
	delete src_SDL;
}

void RendererSDL::drawText(const Actor& actor, const class TextComponent* text, int width, int height, Vector2 offset)
{
	Vector2 cam_pos = Game::instance().getCamera().getCamPos();
	SDL_Rect dst_rect;
	Vector2 position = actor.getPosition() - cam_pos + offset;
	float rotation = actor.get2DRotation();
	float scale = actor.getScale();

	dst_rect.w = static_cast<int>(scale * width);
	dst_rect.h = static_cast<int>(scale * height);

	dst_rect.x = static_cast<int>(position.x);
	dst_rect.y = static_cast<int>(position.y);

	SDL_Rect* src_SDL = nullptr;

	SDL_RenderCopyEx(SDLRenderer, text->toSDLTexture(), src_SDL, &dst_rect, -Maths::toDegrees(rotation), nullptr, SDL_FLIP_NONE);
	delete src_SDL;
}

void RendererSDL::close()
{
	SDL_DestroyRenderer(SDLRenderer);
}

void RendererSDL::addLoadComponent(LoadComponent* LoadComponent)
{
	int sprite_draw_order = LoadComponent->getLoadOrder();
	auto iter = begin(LoadComponents);
	for (; iter != end(LoadComponents); ++iter)
	{
		if (sprite_draw_order < (*iter)->getLoadOrder())
		{
			break;
		}
	}
	LoadComponents.insert(iter, LoadComponent);
}

void RendererSDL::removeLoadComponent(LoadComponent* LoadComponent)
{
	auto iter = std::find(begin(LoadComponents), end(LoadComponents), LoadComponent);
	LoadComponents.erase(iter);
}