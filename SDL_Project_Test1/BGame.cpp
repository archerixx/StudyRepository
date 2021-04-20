#include "BGame.h"
#include <string>

BGame::BGame()
{
	gBrick_Level_1 = new BBricks;
	gSound = new BSound;

	//setup base background
	baseBackgroundTexture = new BTexture;
	gameOverBackground = new BTexture;
	menuText = new BTexture;
	if (!loadBackgroundMedia(gBrick_Level_1->getLevel_1()->getBackGroundTexture()))
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
	livesTexture = new BTexture;
	if (!loadScoreAndLivesMedia(gameScore, getBrickLevel_1()->getLevel_1()->getBallLives()))
	{
		std::cout << "Failed to load font for score media!\n";
	}
	ballTexture = new BTexture;
	if (!loadBallMedia())
	{
		std::cout << "Failed to load Ball media!\n";
	}
	
	//setup bricks
	gBrick_Level_1->setYellowBrick(false, gBrick_Level_1->getLevel_1()->getColumnCount(), gBrick_Level_1->getLevel_1()->getColumtSpacing());
	gBrick_Level_1->setBlueBrick(false, gBrick_Level_1->getLevel_1()->getColumnCount(), gBrick_Level_1->getLevel_1()->getColumtSpacing());
	gBrick_Level_1->setRedBrick(false, gBrick_Level_1->getLevel_1()->getColumnCount(), gBrick_Level_1->getLevel_1()->getColumtSpacing());

	if (!gSound->loadMusicMedia())
	{
		std::cout << "Failed to load Sound!\n";
	}

	callDestructor = true;
}
BGame::BGame(bool thirdLevel)
{
	gBrick_Level_2 = new BBricks(true);
	gSound = new BSound;
	//setup base background
	baseBackgroundTexture = new BTexture;
	gameOverBackground = new BTexture;
	menuText = new BTexture;
	if (!loadBackgroundMedia(getBrickLevel_2()->getLevel_2()->getBackGroundTexture()))
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
	livesTexture = new BTexture;
	if (!loadScoreAndLivesMedia(gameScore, getBrickLevel_2()->getLevel_2()->getBallLives()))
	{
		std::cout << "Failed to load font for score media!\n";
	}
	ballTexture = new BTexture;
	if (!loadBallMedia())
	{
		std::cout << "Failed to load Ball media!\n";
	}
	
	//setup bricks
	gBrick_Level_2->setYellowBrick(true, gBrick_Level_2->getLevel_2()->getColumnCount(), gBrick_Level_2->getLevel_2()->getColumtSpacing());
	gBrick_Level_2->setBlueBrick(true, gBrick_Level_2->getLevel_2()->getColumnCount(), gBrick_Level_2->getLevel_2()->getColumtSpacing());
	gBrick_Level_2->setRedBrick(true, gBrick_Level_2->getLevel_2()->getColumnCount(), gBrick_Level_2->getLevel_2()->getColumtSpacing());
	
	if (!gSound->loadMusicMedia())
	{
		std::cout << "Failed to load Sound!\n";
	}

	callDestructor = false;
}
BGame::~BGame()
{
	if (callDestructor)
	{
	baseBackgroundTexture->clearTexture();
	delete baseBackgroundTexture;
	baseBackgroundTexture = NULL;
	gameOverBackground->clearTexture();
	delete gameOverBackground;
	gameOverBackground = NULL;
	menuText->clearTexture();
	delete menuText;
	menuText = NULL;
	scoreTexture->clearTexture();
	delete scoreTexture;
	scoreTexture = NULL;
	livesTexture->clearTexture();
	delete livesTexture;
	livesTexture = NULL;
	ballTexture->clearTexture();
	delete ballTexture;
	ballTexture = NULL;

	
	delete gBrick_Level_1;
	gBrick_Level_1 = NULL;
	
	delete gSound;
	gSound = NULL;
	}
}

bool BGame::loadBackgroundMedia(const char* path)
{
	//Loading success flag
	bool success = true;

	//Load background texture
	if (!baseBackgroundTexture->loadFromFile(path))
	{
		std::cout << "\nFailed to load background texture image!\n";
		success = false;
	}
	//Load game over texture
	if (!gameOverBackground->loadFromFile("SDL_Image_Imports/gameover_background.png"))
	{
		std::cout << "\nFailed to load game over texture image!\n";
		success = false;
	}
	//Load menu text
	if (!menuText->loadFromFile("SDL_Image_Imports/menu_text.png"))
	{
		std::cout << "\nFailed to load game over texture image!\n";
		success = false;
	}

	return success;
}
void BGame::renderBackground(int x,int y)
{
	baseBackgroundTexture->renderTexture(x, y);
}
void BGame::renderGameOverBackground(int x, int y)
{
	gameOverBackground->renderTexture(x, y);
}
void BGame::renderMenu(int x, int y)
{
	menuText->renderTexture(x, y);
}

BSound* BGame::getSound()
{
	return gSound;
}

/*
	Ball setup
*/
void BGame::setBallPoint(int x, int y)
{
	bBallPosition.x = x;
	bBallPosition.y = y;
}
int BGame::getBallSize() const
{
	return BALL_SIZE;
}
bool BGame::loadBallMedia()
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
void BGame::renderBall(int x, int y)
{
	ballTexture->renderTexture(x, y);
}

//Movement/Collision events
BBricks* BGame::getBrickLevel_1()
{
	return gBrick_Level_1;
}
BBricks* BGame::getBrickLevel_2()
{
	return gBrick_Level_2;
}
void BGame::ballMovementAndCollision(int board_x, int board_y, bool levelState)
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
			brickHitCounter++;
			stateReset();
			Mix_PlayChannel(-1, gSound->gMedium, 0);
			onLeftBoardSide = true;
		}
		//check if ball is on right side of board
		else if (bBallPosition.x > (board_x + (getBoardWidth() / 2)) && bBallPosition.x <= board_x + getBoardWidth())
		{
			brickHitCounter++;
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
	if (!levelState)
	{ 
		brickCollision(getBrickLevel_1()->getLevel_1()->getColumnCount(), getBrickLevel_1());

		//if ball misses board and falls below
		if (bBallPosition.y > 600)
		{
			getBrickLevel_1()->getLevel_1()->setBallLives(getBrickLevel_1()->getLevel_1()->getBallLives() - 1);
			lifeLost = true;
		}
	}
	else
	{
		brickCollision(getBrickLevel_2()->getLevel_2()->getColumnCount(), getBrickLevel_2()); //TODO add lvl 2

			//if ball misses board and falls below
		if (bBallPosition.y > 600)
		{
			getBrickLevel_2()->getLevel_2()->setBallLives(getBrickLevel_2()->getLevel_2()->getBallLives() - 1);
			lifeLost = true;
		}
	}


}
//Ball states reset
void BGame::stateReset()
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
void BGame::brickCollision(int size, BBricks* getBrickLevel)
{
	for (int i = 0; i < size; i++)
	{
		//checks if ball hits yellow bricks on Y-axis
		if (bBallPosition.y < getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) &&
			(bBallPosition.y + BALL_SIZE) > getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeYellowBricks(i, getBrickLevel);
					onTopWallLeft = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeYellowBricks(i, getBrickLevel);
					onTopWallRight = true;
					break;
				}
			}
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//checks speed
				if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_SIZE) <= (getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) + 1) &&
					bBallPosition.y < (getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 2) &&
					(bBallPosition.y + BALL_SIZE) >(getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeYellowBricks(i, getBrickLevel);
						onRightWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeYellowBricks(i, getBrickLevel);
						onRightWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick on right side
			else
			{
				//check speed
				if (bBallPosition.x < getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) &&
					bBallPosition.x >= (getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) - 1) &&
					bBallPosition.y < (getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 2) &&
					(bBallPosition.y + BALL_SIZE) >(getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeYellowBricks(i, getBrickLevel);
						onLeftWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeYellowBricks(i, getBrickLevel);
						onLeftWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from above
			if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_SIZE) > getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_SIZE) <= (getBrickLevel->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeYellowBricks(i, getBrickLevel);
					onRightBoardSide = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeYellowBricks(i, getBrickLevel);
					onLeftBoardSide = true;
					break;
				}
			}
		}

		//checks if ball hits blue bricks on Y-axis
		if (bBallPosition.y < getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) &&
			(bBallPosition.y + BALL_SIZE) > getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeBlueBricks(i, getBrickLevel);
					onTopWallLeft = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeBlueBricks(i, getBrickLevel);
					onTopWallRight = true;
					break;
				}
			}
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//check speed
				if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_SIZE) <= (getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) + 2))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeBlueBricks(i, getBrickLevel);
						onRightWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeBlueBricks(i, getBrickLevel);
						onRightWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from right
			else
			{
				//check speed
				if (bBallPosition.x < getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
					bBallPosition.x >= (getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) - 1))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeBlueBricks(i, getBrickLevel);
						onLeftWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeBlueBricks(i, getBrickLevel);
						onLeftWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from above
			if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_SIZE) > getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_SIZE) <= (getBrickLevel->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeBlueBricks(i, getBrickLevel);
					onRightBoardSide = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeBlueBricks(i, getBrickLevel);
					onLeftBoardSide = true;
					break;
				}
			}
		}

		//checks if ball hits red bricks on Y-axis
		if (bBallPosition.y < getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) &&
			(bBallPosition.y + BALL_SIZE) > getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) - 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeRedBricks(i, getBrickLevel);
					onTopWallLeft = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeRedBricks(i, getBrickLevel);
					onTopWallRight = true;
					break;
				}
			}
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//check speed
				if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_SIZE) <= (getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) + 1))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeRedBricks(i, getBrickLevel);
						onRightWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeRedBricks(i, getBrickLevel);
						onRightWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from right
			else
			{
				//check speed
				if (bBallPosition.x < getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
					bBallPosition.x >= (getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) - 1))
				{
					//checks if ball came from above
					if (bBallPosition.y > bBallPreviousPosition.y)
					{
						stateReset();
						removeRedBricks(i, getBrickLevel);
						onLeftWallAbove = true;
						break;
					}
					//check if ball came from below
					else
					{
						stateReset();
						removeRedBricks(i, getBrickLevel);
						onLeftWallBelow = true;
						break;
					}
				}
			}
			//checks if ball hit brick from above
			if ((bBallPosition.x + BALL_SIZE) > getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_SIZE) > getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_SIZE) <= (getBrickLevel->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0) + 2))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeRedBricks(i, getBrickLevel);
					onRightBoardSide = true;
					break;
				}
				//checks if ball hit brick from right
				else
				{
					stateReset();
					removeRedBricks(i, getBrickLevel);
					onLeftBoardSide = true;
					break;
				}
			}
		}
	}
}


/*
	Clear bricks from gametable and its texture
*/
void BGame::removeYellowBricks(int index, BBricks* getBrickLevel)
{
	Mix_PlayChannel(-1, gSound->gLow, 0);
	getBrickLevel->getSoftYellowBrick(index)->setHitPoints(getBrickLevel->getSoftYellowBrick(index)->getHitPoints() - 1);
	if (getBrickLevel->getSoftYellowBrick(index)->getHitPoints() == 0)
	{ 
		//brickHitCounter++;
		setScore(getBrickLevel->getSoftYellowBrick(index)->getBreakScore());
		getBrickLevel->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrickLevel->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrickLevel->getSoftYellowBrick(index)->clearYellowTexture();
	}
}
void BGame::removeBlueBricks(int index, BBricks* getBrickLevel)
{            
	Mix_PlayChannel(-1, gSound->gLow, 0);
	getBrickLevel->getMediumBlueBrick(index)->setHitPoints(getBrickLevel->getMediumBlueBrick(index)->getHitPoints() - 1);
	if (getBrickLevel->getMediumBlueBrick(index)->getHitPoints() == 0)
	{ 
		//brickHitCounter++;
		setScore(getBrickLevel->getMediumBlueBrick(index)->getBreakScore());
		getBrickLevel->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrickLevel->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrickLevel->getMediumBlueBrick(index)->clearBlueTexture();
	}
}
void BGame::removeRedBricks(int index, BBricks* getBrickLevel)
{
	Mix_PlayChannel(-1, gSound->gLow, 0);
	getBrickLevel->getHardRedBrick(index)->setHitPoints(getBrickLevel->getHardRedBrick(index)->getHitPoints() - 1);
	if (getBrickLevel->getHardRedBrick(index)->getHitPoints() == 0)
	{ 
		//brickHitCounter++;
		setScore(getBrickLevel->getHardRedBrick(index)->getBreakScore());
		getBrickLevel->getHardRedBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrickLevel->getHardRedBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrickLevel->getHardRedBrick(index)->clearRedTexture();
	}
}

/*
	SETs/GETs
*/
void BGame::setScore(int addScore)
{
	this->gameScore += addScore;
}
int BGame::getScore()
{
	return this->gameScore;
}
int BGame::getHitCounter()
{
	return this->brickHitCounter;
}
void BGame::updateHitCounter()
{
	this->brickHitCounter = 0;
}
bool BGame::getLifeLostState()
{
	return lifeLost;
}

/*
	Setup text/font for score
*/
BTexture* BGame::getScoreTexture()
{
	return scoreTexture;
}
BTexture* BGame::getLivesTexture()
{
	return livesTexture;
}
bool BGame::loadScoreAndLivesMedia(int gameScore, int livesLeft)
{
	//Loading success flag
	bool success = true;

	//Open the font
	baseFont = TTF_OpenFont("SDL_Image_Imports/MAGNETOB.ttf", 26);
	if (baseFont == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf Error: %s\n" << TTF_GetError();
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 188, 255 };
		if (!scoreTexture->loadFromRenderedText(std::to_string(gameScore).c_str(), textColor))
		{
			std::cout << "Failed to render text texture!\n";
			success = false;
		}
		if (!livesTexture->loadFromRenderedText(std::to_string(livesLeft).c_str(), textColor))
		{
			std::cout << "Failed to render text texture!\n";
			success = false;
		}
	}

	return success;
}
