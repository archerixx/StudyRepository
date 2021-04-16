#pragma once

#include "BBricks.h"

class BBall : public BBricks
{
private:
	const int BALL_WIDTH = 10;
	const int BALL_HEIGHT = 10;

	static const int BALL_START_POSITION_X = 400;
	static const int BALL_START_POSITION_Y = 560;

	SDL_Point bBallPosition;
	SDL_Point bBallPreviousPosition;

	BTexture ballTexture;

	//ball states
	bool onLeftBoardSide = false;
	bool onRightBoardSide = false;
	bool onLeftWallBelow = false;
	bool onLeftWallAbove = false;
	bool onTopWallLeft = false;
	bool onTopWallRight = false;
	bool onRightWallBelow = false;
	bool onRightWallAbove = false;
	bool onLeftBrickSide = false;
	bool onRightBrickSide = false;

	BBricks* gBrick = new BBricks;

	int BrickColums;
	int YellowBrick_Y_End;

	int Score;

public:

	BBricks* getBrick()
	{
		return gBrick;
	}

	BBall();

	void setScore(int addScore);

	int getScore();

	void setBallPoint(int x= BALL_START_POSITION_X, int y = BALL_START_POSITION_Y);
	
	bool loadBallMedia();

	void renderBall(int x, int y);

	void ballMovementAndCollision(int board_x, int board_y);

	void stateReset();

	void removeYellowBricks(int index);
	void removeBlueBricks(int index);
	void removeRedBricks(int index);

	int getBallSize() const;

	bool* lifeLost = new bool;
};