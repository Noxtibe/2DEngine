#include "TextComponent.h"
#include <Engine/Game.h>

TextComponent::TextComponent(Actor* ownerP, Font* fontP, string textP, Color colorP, Vector2 offsetP, bool centeredP, int drawOrderP) : LoadComponent(ownerP, drawOrderP), font(fontP), text(textP), color(colorP), offset(offsetP), centered(centeredP)
{
	recalculateSDLTexture();
}

TextComponent::~TextComponent()
{
	if (SDLTexture)
	{
		SDL_DestroyTexture(SDLTexture);
	}
}

void TextComponent::setFont(Font* fontP)
{
	font = fontP;
	recalculateSDLTexture();
}

void TextComponent::setText(const string textP)
{
	text = textP;
	recalculateSDLTexture();
}

void TextComponent::recalculateSDLTexture()
{
	if (font == nullptr) return;

	if (SDLTexture)
	{
		SDL_DestroyTexture(SDLTexture);
	}

	auto sdl_surface = TTF_RenderText_Solid(font->getSdlFont(), text.c_str(), color.toSDLColor());
	SDLTexture = SDL_CreateTextureFromSurface(owner.getGame().getRenderer().toSDLRenderer(), sdl_surface);

	width = sdl_surface->w;
	height = sdl_surface->h;

	if (centered)
	{
		centeredOffsetX = width / 2.0f;
	}

	SDL_FreeSurface(sdl_surface);
}

void TextComponent::draw(RendererSDL& renderer)
{
	if (willLoad)
	{
		renderer.drawText(owner, this, width, height, getRealOffset());
	}
}

void TextComponent::setCentered(bool centeredP)
{
	centered = centeredP;
	if (centered)
	{
		centeredOffsetX = width / 2.0f;
	}
	else
	{
		centeredOffsetX = 0.0f;
	}
}

Vector2 TextComponent::getRealOffset()
{
	if (centered)
	{
		return Vector2{ offset.x - centeredOffsetX, offset.y };
	}
	else
	{
		return offset;
	}
}
