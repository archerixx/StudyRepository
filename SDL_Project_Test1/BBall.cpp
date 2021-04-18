#include "BBall.h"
#include <string>

BBall::BBall()
{
	gBrick = new BBricks;
	gSound = new BSound;

	//setup base background
	baseBackgroundTexture = new BTexture;
	if (!loadBackgroundMedia(gBrick->getLevel()->getBackGroundTexture()))
	{
		std::cout << "Failed to load base background media!";
	}

	bBallPosition.x = 360;
	bBallPosition.y = 560;
	bBallPreviousPosition = bBallPosition;

	gameScore = 0;
	brickHitCounter = 0;
	lifeLost = false;

	scoreTexture = new BTexture;
	if (!loadScoreMedia(gameScore))
	{
		std::cout << "Failed to load font for score media!\n";
	}
	ballTexture = new BTexture;
	if (!loadBallMedia())
	{
		std::cout << "Failed to load Ball media!\n";
	}

	//setup bricks
	gBrick->setYellowBrick();
	gBrick->setBlueBrick();
	gBrick->setRedBrick();

	if (!gSound->loadMusicMedia())
	{
		std::cout << "Failed to load Sound!\n";
	}
}
BBall::~BBall()
{
	baseBackgroundTexture->clearTexture();
	delete baseBackgroundTexture;
	baseBackgroundTexture = NULL;
	scoreTexture->clearTexture();
	delete scoreTexture;
	scoreTexture = NULL;
	ballTexture->clearTexture();
	delete ballTexture;
	ballTexture = NULL;

	delete gBrick;
	gBrick = NULL;
	delete gSound;
	gSound = NULL;
}

bool BBall::loadBackgroundMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	//Load background texture
	if (!baseBackgroundTexture->loadFromFile(path))
	{
		std::cout << "\nFailed to load background texture image!\n";
		success = false;
	}

	return success;
}
void BBall::renderBackground(int x,int y)
{
	baseBackgroundTexture->renderTexture(x, y);
}

BSound* BBall::getSound()
{
	return gSound;
}

/*
	Ball setup
*/
void BBall::setBallPoint(int x, int y)
{
	bBallPosition.x = x;
	bBallPosition.y = y;
}
int BBall::getBallSize() const
{
	return BALL_SIZE;
}
bool BBall::loadBallMedia()
{
	//Loading success flag
	bool success = true;

	if (!ballTexture->loadFromFile("SDL_Image_Imports/Ball.png"))
	{
		std::cout << "Failed to load Ball texture!\n";
		success = false;
	}

	return success;
}
void BBall::renderBall(int x, int y)
{
	ballTexture->renderTexture(x, y);
}

//Movement/Collision events
BBricks* BBall::getBrick()
{
	return gBrick;
}
void BBall::ballMovementAndCollision(int board_x, int board_y)
{
	//show/renderTexture ball
	renderBall(bBallPosition.x, bBallPosition.y);
	
	//after life lost, set starting position of ball and reset state
	if (lifeLost)
	{
		lifeLost = false;
		bBallPosition.x = board_x + getBoardWidth()/2;
		bBallPosition.y = board_y - BALL_SIZE;
	}
	
	/*
		Ball starts from board, first read is if ball has hit board and if game continues
	*/
	if ((bBallPosition.y+BALL_SIZE) >= board_y && (bBallPosition.y + BALL_SIZE) <= (board_y + getBoardHeight()/5))
	{
		//check if ball is on left side of board
		if ((bBallPosition.x+BALL_SIZE) > board_x && bBallPosition.x <= (board_x + (getBoardWidth() / 2)))
		{
			stateReset();
			Mix_PlayChannel(-1, gSound->gMedium, 0);
			onLeftBoardSide = true;
		}
		//check if ball is on right side of board
		else if (bBallPosition.x > (board_x + (getBoardWidth() / 2)) && bBallPosition.x <= board_x + getBoardWidth())
		{
			Mix_PlayChannel(-1, gSound->gMedium, 0);
			stateReset();
			onRightBoardSide = true;
		}
	}
	//if on left board side
	if (onLeftBoardSide)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y--;
	}
	//if on right board side
	if (onRightBoardSide)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y--;
	}

	/*
		Check left wall collision
	*/
	if (bBallPosition.x < getGametableWidthStart())
	{
		stateReset();
		//if ball hits wall from below
		if (bBallPosition.y < bBallPreviousPosition.y)
		{
			onLeftWallBelow = true;
		}
		//if ball hits from above
		else
		{
			onLeftWallAbove = true;
		}
	}
	//if ball hits wall from below
	if (onLeftWallBelow)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y--;
	}
	//if ball hits from above
	if (onLeftWallAbove)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y++;
	}

	/*
		Check top wall collision
	*/
	if (bBallPosition.y < getGametableHeightStart())
	{
		stateReset();
		//if ball hits top wall from left
		if (bBallPosition.x > bBallPreviousPosition.x)
		{
			onTopWallLeft = true;
		}
		//if ball hits top wall from right
		else
		{
			onTopWallRight = true;
		}
	}
	//if ball hits top wall from left
	if (onTopWallLeft)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y++;
	}
	//if ball hits top wall from right
	if (onTopWallRight)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y++;
	}

	
	/*
		Check collision with right wall
	*/
	if ((bBallPosition.x + BALL_SIZE) > getGametableWidthEnd())
	{
		stateReset();
		//if ball hits wall from above
		if (bBallPosition.y > bBallPreviousPosition.y)
		{
			onRightWallAbove = true;
		}
		//if ball hits wall from below
		else
		{
			onRightWallBelow = true;
		}
	}
	//if ball hits wall from above
	if (onRightWallAbove)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y++;
	}
	//if ball hits wall from below
	if (onRightWallBelow)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y--;
	}

	
	/*
		Check if ball hit bricks and removes it
	*/
	for (int i = 0; i < getBrick()->getLevel()->getColumnCount(); i++)
	{
		//checks if ball hits yellow bricks on Y-axis
		if (bBallPosition.y < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) && 
			(bBallPosition.y+BALL_SIZE) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_SIZE) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && 
				bBallPosition.y < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeYellowBricks(i);
					onTopWallLeft = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeYellowBricks(i);
					onTopWallRight = true;
					break;
				}
			}
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//checks speed
				if ((bBallPosition.x + BALL_SIZE) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_SIZE) <= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) + 1) &&
					bBallPosition.y < (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 2) &&
					(bBallPosition.y + BALL_SIZE) > (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeYellowBricks(i);
						onRightWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeYellowBricks(i);
						onRightWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick on right side
			else
			{
				//check speed
				if (bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) &&
					bBallPosition.x >= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) - 1) &&
					bBallPosition.y < (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 2) &&
					(bBallPosition.y + BALL_SIZE) >(getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeYellowBricks(i);
						onLeftWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeYellowBricks(i);
						onLeftWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from above
			if ((bBallPosition.x + BALL_SIZE) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) && 
				bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && 
				(bBallPosition.y+BALL_SIZE) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y+BALL_SIZE) <= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeYellowBricks(i);
					onRightBoardSide = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeYellowBricks(i);
					onLeftBoardSide = true;
					break;
				}
			}
		}

		//checks if ball hits blue bricks on Y-axis
		if (bBallPosition.y < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) &&
			(bBallPosition.y + BALL_SIZE) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_SIZE) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeBlueBricks(i);
					onTopWallLeft = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeBlueBricks(i);
					onTopWallRight = true;
					break;
				}
			}
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//check speed
				if ((bBallPosition.x + BALL_SIZE) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_SIZE) <= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) + 2))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeBlueBricks(i);
						onRightWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeBlueBricks(i);
						onRightWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from right
			else
			{
				//check speed
				if (bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
					bBallPosition.x >= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) - 1))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeBlueBricks(i);
						onLeftWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeBlueBricks(i);
						onLeftWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from above
			if ((bBallPosition.x + BALL_SIZE) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_SIZE) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_SIZE) <= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeBlueBricks(i);
					onRightBoardSide = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeBlueBricks(i);
					onLeftBoardSide = true;
					break;
				}
			}
		}

		//checks if ball hits red bricks on Y-axis
		if (bBallPosition.y < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) &&
			(bBallPosition.y + BALL_SIZE) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_SIZE) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) - 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeRedBricks(i);
					onTopWallLeft = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeRedBricks(i);
					onTopWallRight = true;
					break;
				}
			}
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//check speed
				if ((bBallPosition.x + BALL_SIZE) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_SIZE) <= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) + 1))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeRedBricks(i);
						onRightWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeRedBricks(i);
						onRightWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from right
			else
			{
				//check speed
				if (bBallPosition.x < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
					bBallPosition.x >= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) - 1))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeRedBricks(i);
						onLeftWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeRedBricks(i);
						onLeftWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from above
			if ((bBallPosition.x + BALL_SIZE) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_SIZE) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_SIZE) <= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeRedBricks(i);
					onRightBoardSide = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeRedBricks(i);
					onLeftBoardSide = true;
					break;
				}
			}
		}
	}

	//if ball misses board and falls below
	if (bBallPosition.y > 600)
	{
		getBrick()->getLevel()->setBallLifes(getBrick()->getLevel()->getBallLifes() - 1);
		lifeLost = true;
	}

}
//Ball states reset
void BBall::stateReset()
{
	onLeftBoardSide = false;
	onRightBoardSide = false;
	onLeftWallBelow = false;
	onLeftWallAbove = false;
	onTopWallLeft = false;
	onTopWallRight = false;
	onRightWallAbove = false;
	onRightWallBelow = false;
}

/*
	Clear bricks from gametable and its texture
*/
void BBall::removeYellowBricks(int index)
{
	Mix_PlayChannel(-1, gSound->gLow, 0);
	getBrick()->getSoftYellowBrick(index)->setHitPoints(getBrick()->getSoftYellowBrick(index)->getHitPoints() - 1);
	if (getBrick()->getSoftYellowBrick(index)->getHitPoints() == 0)
	{ 
		brickHitCounter++;
		setScore(getBrick()->getSoftYellowBrick(index)->getBreakScore());
		getBrick()->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrick()->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrick()->getSoftYellowBrick(index)->clearYellowTexture();
	}
}
void BBall::removeBlueBricks(int index)
{            
	Mix_PlayChannel(-1, gSound->gLow, 0);
	getBrick()->getMediumBlueBrick(index)->setHitPoints(getBrick()->getMediumBlueBrick(index)->getHitPoints() - 1);
	if (getBrick()->getMediumBlueBrick(index)->getHitPoints() == 0)
	{ 
		brickHitCounter++;
		setScore(getBrick()->getMediumBlueBrick(index)->getBreakScore());
		getBrick()->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrick()->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrick()->getMediumBlueBrick(index)->clearBlueTexture();
	}
}
void BBall::removeRedBricks(int index)
{
	Mix_PlayChannel(-1, gSound->gLow, 0);
	getBrick()->getHardRedBrick(index)->setHitPoints(getBrick()->getHardRedBrick(index)->getHitPoints() - 1);
	if (getBrick()->getHardRedBrick(index)->getHitPoints() == 0)
	{ 
		brickHitCounter++;
		setScore(getBrick()->getHardRedBrick(index)->getBreakScore());
		getBrick()->getHardRedBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrick()->getHardRedBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrick()->getHardRedBrick(index)->clearRedTexture();
	}
}

/*
	SETs/GETs
*/
void BBall::setScore(int addScore)
{
	this->gameScore += addScore;
}
int BBall::getScore()
{
	return this->gameScore;
}
int BBall::getHitCounter()
{
	return this->brickHitCounter;
}
bool BBall::getLifeLostState()
{
	return lifeLost;
}

/*
	Setup text/font for score
*/
BTexture* BBall::getScoreTexture()
{
	return scoreTexture;
}
bool BBall::loadScoreMedia(int gameScore)
{
	//Loading success flag
	bool success = true;

	//Open the font
	baseFont = TTF_OpenFont("SDL_Image_Imports/BOD_PSTC.ttf", 26);
	if (baseFont == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf Error: %s\n" << TTF_GetError();
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 111, 111 };
		if (!scoreTexture->loadFromRenderedText(std::to_string(gameScore).c_str(), textColor))
		{
			std::cout << "Failed to render text texture!\n";
			success = false;
		}
	}

	return success;
}


