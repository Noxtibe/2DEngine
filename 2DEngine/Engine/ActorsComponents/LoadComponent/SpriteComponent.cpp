#include "SpriteComponent.h"
#include <Engine/Maths/Rectangle.h>

SpriteComponent::SpriteComponent(Actor* ownerP, Texture& textureP, Vector2 offsetP, RendererSDL::Flip spriteFlipP, int drawOrderP): LoadComponent(ownerP), texture(textureP), drawOrder(drawOrderP), texWidth(textureP.getWidth()), texHeight(textureP.getHeight()), offset(offsetP), spriteFlip(spriteFlipP)
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(RendererSDL& renderer)
{
	Vector2 origin{ texWidth / 2.f, texHeight / 2.f };
	renderer.drawSprite(owner, texture, Rectangle::nullRect, Vector2::zero, spriteFlip, offset);
}
