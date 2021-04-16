#include "BBall.h"

BBall::BBall()
{
	bBallPosition.x = 360;
	bBallPosition.y = 560;
	bBallPreviousPosition = bBallPosition;

	gBrick->setYellowBrick();
	gBrick->setBlueBrick();
	gBrick->setRedBrick();

	loadBallMedia();

	*lifeLost = false;
}

void BBall::setScore(int addScore)
{
	this->Score += addScore;
}

int BBall::getScore()
{
	return this->Score;
}

void BBall::setBallPoint(int x, int y)
{
	bBallPosition.x = x;
	bBallPosition.y = y;
}

bool BBall::loadBallMedia()
{
	//Loading success flag
	bool success = true;

	if (!ballTexture.loadFromFile("SDL_Image_Imports/Ball.png"))
	{
		printf("Failed to load Ball texture!\n");
		success = false;
	}

	return success;
}

void BBall::ballMovementAndCollision(int board_x, int board_y)//, BBricks gBricks)
{
	//show/renderTexture ball
	renderBall(bBallPosition.x, bBallPosition.y);

	if (*lifeLost)
	{
		*lifeLost = false;
		bBallPosition.x = board_x + getBoardWidth()/2;
		bBallPosition.y = board_y - BALL_HEIGHT;
	}

	/*
		Ball starts from board, first read is if ball has hit board and if game continues
	*/
	if (((bBallPosition.y+BALL_HEIGHT) >= board_y) && (bBallPosition.y + BALL_HEIGHT) <= (board_y+getBoardHeight()/5))
	{
		//check if ball is on left side of board
		if ((bBallPosition.x+BALL_WIDTH) > board_x && bBallPosition.x <= (board_x + (getBoardWidth() / 2)))
		{
			stateReset();
			onLeftBoardSide = true;
		}
		//check if ball is on right side of board
		else if (bBallPosition.x > (board_x + (getBoardWidth() / 2)) && bBallPosition.x < (board_x + getBoardWidth()))
		{
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
	if ((bBallPosition.x + BALL_WIDTH) > getGametableWidthEnd())
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
			(bBallPosition.y+BALL_HEIGHT) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0))
		{
			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && 
				bBallPosition.y < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 1))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeYellowBricks(i);
					onLeftBrickSide = true;
					break;
				}
				else
				{
					stateReset();
					removeYellowBricks(i);
					onRightBrickSide = true;
					break;
				}
			}

			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//checks speed
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_WIDTH) <= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) + 1))
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
					bBallPosition.x >= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) - 1))
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
			if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) && 
				bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && 
				(bBallPosition.y+BALL_HEIGHT) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y+BALL_HEIGHT) <= (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 1))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeYellowBricks(i);
					onRightBoardSide = true;
					break;
				}
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
			(bBallPosition.y + BALL_HEIGHT) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0))
		{

			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - 1))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeBlueBricks(i);
					onLeftBrickSide = true;
					break;
				}
				else
				{
					stateReset();
					removeBlueBricks(i);
					onRightBrickSide = true;
					break;
				}
			}

			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//check speed
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_WIDTH) <= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) + 1))
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
			if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_HEIGHT) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_HEIGHT) <= (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) + 1))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeBlueBricks(i);
					onRightBoardSide = true;
					break;
				}
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
			(bBallPosition.y + BALL_HEIGHT) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0))
		{

			//checks which brick did ball hit from below
			if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
				bBallPosition.y < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) &&
				bBallPosition.y >= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(1) - 1))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeRedBricks(i);
					onLeftBrickSide = true;
					break;
				}
				else
				{
					stateReset();
					removeRedBricks(i);
					onRightBrickSide = true;
					break;
				}
			}

			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//check speed
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
					(bBallPosition.x + BALL_WIDTH) <= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) + 1))
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
			if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(0) &&
				bBallPosition.x < getBrick()->getHardRedBrick(i)->getBrickBoarderOn_X_Element(1) &&
				(bBallPosition.y + BALL_HEIGHT) > getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0) &&
				(bBallPosition.y + BALL_HEIGHT) <= (getBrick()->getHardRedBrick(i)->getBrickBoarderOn_Y_Element(0) + 1))
			{
				//checks if ball hit brick from left
				if (bBallPosition.x > bBallPreviousPosition.x)
				{
					stateReset();
					removeRedBricks(i);
					onRightBoardSide = true;
					break;
				}
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


	if (onLeftBrickSide == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y++;
	}

	if (onRightBrickSide == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y++;
	}

	if (bBallPosition.y > 600)
	{
		getBrick()->getLevel()->setBallLifes(getBrick()->getLevel()->getBallLifes() - 1);
		*lifeLost = true;
	}

}

void BBall::renderBall(int x, int y)
{
	ballTexture.renderTexture(x, y);
}

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
	onLeftBrickSide = false;
	onRightBrickSide = false;
}

void BBall::removeYellowBricks(int index)
{
	getBrick()->getSoftYellowBrick(index)->setHitPoints(getBrick()->getSoftYellowBrick(index)->getHitPoints() - 1);
	if (getBrick()->getSoftYellowBrick(index)->getHitPoints() == 0)
	{ 
		setScore(getBrick()->getSoftYellowBrick(index)->getBreakScore());
		getBrick()->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrick()->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrick()->getSoftYellowBrick(index)->clearYellowTexture();
	}
}

void BBall::removeBlueBricks(int index)
{                       
	getBrick()->getMediumBlueBrick(index)->setHitPoints(getBrick()->getMediumBlueBrick(index)->getHitPoints() - 1);
	if (getBrick()->getMediumBlueBrick(index)->getHitPoints() == 0)
	{ 
		setScore(getBrick()->getMediumBlueBrick(index)->getBreakScore());
		getBrick()->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrick()->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrick()->getMediumBlueBrick(index)->clearBlueTexture();
	}
}

void BBall::removeRedBricks(int index)
{
	getBrick()->getHardRedBrick(index)->setHitPoints(getBrick()->getHardRedBrick(index)->getHitPoints() - 1);
	if (getBrick()->getHardRedBrick(index)->getHitPoints() == 0)
	{ 
		setScore(getBrick()->getHardRedBrick(index)->getBreakScore());
		getBrick()->getHardRedBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
		getBrick()->getHardRedBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
		getBrick()->getHardRedBrick(index)->clearRedTexture();
	}
}

int BBall::getBallSize() const
{
	return BALL_HEIGHT;
}
