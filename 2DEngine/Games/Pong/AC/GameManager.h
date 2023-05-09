#pragma once
#include <Engine/ActorsComponents/Actor.h>
#include <LoadComponent/TextComponent.h>
#include <LoadComponent/RectangleComponent.h>
#include "Ball.h"
#include "PlayerPaddle.h"
#include "IAPaddle.h"

class GameManager : public Actor
{

public:

	GameManager(Ball* ballP, PlayerPaddle* leftPaddleP, IAPaddle* rightPaddleP, Font* fontP);
	GameManager() = delete;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void updateActor(float dt) override;

	void ScoreAtLeft();
	void ScoreAtRight();

private:

	void ResetScores();
	void PauseGame();
	void ResumeGame();

	TextComponent* leftLoadTextComp;
	TextComponent* rightLoadTextComp;
	TextComponent* victoryLoadTextComp;
	TextComponent* resetLoadTextComp;

	RectangleComponent* lineLoadRectComps[15];

	Font* font;

	Ball* ball;
	PlayerPaddle* leftPaddle;
	IAPaddle* rightPaddle;

	int scoreLeft{ 0 };
	int scoreRight{ 0 };
	int maxScore{ 3 };

	bool isGamePaused{ true };
};

