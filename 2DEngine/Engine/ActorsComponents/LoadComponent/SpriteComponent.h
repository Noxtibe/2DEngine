#pragma once
#include "LoadComponent.h"
#include <Engine/AssetsManager/Texture.h>
#include <Engine/RendererSDL.h>

class SpriteComponent : public LoadComponent
{

public:

    SpriteComponent(Actor* ownerP, Texture& textureP, Vector2 offsetP, RendererSDL::Flip spriteFlipP, int drawOrderP = 100);
    virtual ~SpriteComponent();
    SpriteComponent() = delete;
    SpriteComponent(const SpriteComponent&) = delete;
    SpriteComponent& operator=(const SpriteComponent&) = delete;

    virtual void setTexture(const Texture& textureP);
    virtual void setFlip(RendererSDL::Flip spriteFlipP);
    virtual void draw(RendererSDL& renderer) override;

    int getTexWidth() const { return texWidth; }
    int getTexHeight() const { return texHeight; }

protected:

    Texture texture;
    int texWidth;
    int texHeight;
    Vector2 offset{ Vector2::zero };
    RendererSDL::Flip spriteFlip{ RendererSDL::Flip::None };
};

