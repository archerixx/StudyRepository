#include "BBall.h"
#include <cmath>

BBall::BBall()
{
	bBallPosition.x = 400;
	bBallPosition.y = 560;
	bBallPreviousPosition = bBallPosition;

	gBrick->setYellowBrick();
	gBrick->setBlueBrick();
	gBrick->setRedBrick();

	loadBallMedia();
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
	


	//ball starts from board, first read is if ball has hit board and if game continues
	if ((bBallPosition.y+BALL_HEIGHT)  == board_y)
	{
		stateReset();

		//check if ball is on left side of board
		if ((bBallPosition.x+BALL_WIDTH) > board_x && bBallPosition.x <= (board_x + (getBoardWidth() / 2)))
		{
			
			onLeftBoardSide = true;
		}

		if (bBallPosition.x > (board_x + (getBoardWidth() / 2)) && bBallPosition.x < (board_x + getBoardWidth()))
		{
			onRightBoardSide = true;
		}
	}
	//if on left board side
	if (onLeftBoardSide == true)
	{
		/*
		double speed = 4.0;
		double lenght = sqrt(bBallPosition.x*bBallPosition.x + bBallPosition.y*bBallPosition.y);

		bBallPosition.x = bBallPosition.x / lenght;
		bBallPosition.y = bBallPosition.y / lenght;

		bBallPosition.x *= speed;
		bBallPosition.y *= speed;
		*/
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y--;
	}
	//if on right board side
	if (onRightBoardSide == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y--;
	}

	//check left wall collision
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
	if (onLeftWallBelow == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y--;
	}
	//if ball hits from above
	if (onLeftWallAbove == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y++;
	}

	//check top wall collision
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
	if (onTopWallLeft == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x++;
		bBallPosition.y++;
	}
	//if ball hits top wall from right
	if (onTopWallRight == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y++;
	}

	//check collision with right wall
	if (bBallPosition.x > (getGametableWidthEnd()- BALL_WIDTH))
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
	if (onRightWallAbove == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y++;
	}
	//if ball hits wall from below
	if (onRightWallBelow == true)
	{
		bBallPreviousPosition = bBallPosition;
		bBallPosition.x--;
		bBallPosition.y--;
	}

	//if ball hit bricks and removes it
	for (int i = 0; i < getBrick()->getLevel().getColumnCount(); i++)
	{
		//checks if ball hits yellow bricks on Y-axis
		if (bBallPosition.y < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) && (bBallPosition.y+BALL_HEIGHT) > (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1)-getBrickHeight()))
		{
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//checks which brick did ball hit from below and removes it
				if (bBallPosition.x > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) && (bBallPosition.x+BALL_WIDTH) < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && bBallPosition.y == (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1)-1))
				{
					stateReset();
					removeYellowBricks(i);
					onLeftBrickSide = true;
					break;
				}
				//checks if ball came from above
				if (bBallPosition.y > bBallPreviousPosition.y) 
				{
					//checks if ball hit brick on side from above
					if ((bBallPosition.x + BALL_WIDTH) == getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0))
					{
						stateReset();
						removeYellowBricks(i);
						onRightWallAbove = true;
						break;
					}
				}
				//checks if ball came from below
				else
				{
					//checks if ball hit brick on side from below
					if ((bBallPosition.x + BALL_WIDTH) == getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0))
					{
						stateReset();
						removeYellowBricks(i);
						onRightWallBelow = true;
						break;
					}
				}
				//checks if ball hit brick from above
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) && bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && (bBallPosition.y+BALL_HEIGHT) == (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - getBrickHeight() + 1))
				{
					stateReset();
					removeYellowBricks(i);
					onRightBoardSide = true;
					break;
				}
			}
			//checks if ball hit brick from right
			else
			{
				//checks which brick did ball hit from below
				if (bBallPosition.x > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) && bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && bBallPosition.y == (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(1) - 1))
				{
					stateReset();
					removeYellowBricks(i);
					onRightBrickSide = true;
					break;
				}
				//checks if ball came from above
				if (bBallPosition.y > bBallPreviousPosition.y)
				{ 
					//checks if ball hit brick on side from above
					if (bBallPosition.x == getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1))
					{
						stateReset();
						removeYellowBricks(i);
						onLeftWallAbove = true;
						break;
					}
				}
				//checks if ball came from below
				else
				{
					//checks if ball hit brick on side from below
					if (bBallPosition.x == getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1))
					{
						stateReset();
						removeYellowBricks(i);
						onLeftWallBelow = true;
						break;
					}
				}
				//checks if ball hit brick from above
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(0) && bBallPosition.x < getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_X_Element(1) && (bBallPosition.y + BALL_HEIGHT) == (getBrick()->getSoftYellowBrick(i)->getBrickBoarderOn_Y_Element(0) + 1))
				{
					stateReset();
					removeYellowBricks(i);
					onLeftBoardSide = true;
					break;
				}
			}
		}

		//checks if ball hits blue bricks on Y-axis
		if (bBallPosition.y < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) && (bBallPosition.y + BALL_HEIGHT) >(getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - getBrickHeight()))
		{
			
			//checks if ball hit brick from left
			if (bBallPosition.x > bBallPreviousPosition.x)
			{
				//checks which brick did ball hit from below and removes it
				if (bBallPosition.x > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) && (bBallPosition.x + BALL_WIDTH) < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) && bBallPosition.y == (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - 1))
				{
					
					stateReset();
					removeBlueBricks(i);
					onLeftBrickSide = true;
					break;
				}
				//checks if ball came from above
				if (bBallPosition.y > bBallPreviousPosition.y)
				{
					//checks if ball hit brick on side from above
					if ((bBallPosition.x + BALL_WIDTH) == getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0))
					{
						stateReset();
						removeBlueBricks(i);
						onRightWallAbove = true;
						break;
					}
				}
				//checks if ball came from below
				else
				{
					//checks if ball hit brick on side from below
					if ((bBallPosition.x + BALL_WIDTH) == getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0))
					{
						stateReset();
						removeBlueBricks(i);
						onRightWallBelow = true;
						break;
					}
				}
				//checks if ball hit brick from above
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) && bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) && (bBallPosition.y + BALL_HEIGHT) == (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - getBrickHeight() + 1))
				{
					stateReset();
					removeBlueBricks(i);
					onRightBoardSide = true;
					break;
				}
			}
			//checks if ball hit brick from right
			else
			{
				//checks which brick did ball hit from below
				if (bBallPosition.x > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) && bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) && bBallPosition.y == (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(1) - 1))
				{
					stateReset();
					removeBlueBricks(i);
					onRightBrickSide = true;
					break;
				}
				//checks if ball came from above
				if (bBallPosition.y > bBallPreviousPosition.y)
				{
					//checks if ball hit brick on side from above
					if (bBallPosition.x == getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1))
					{
						stateReset();
						removeBlueBricks(i);
						onLeftWallAbove = true;
						break;
					}
				}
				//checks if ball came from below
				else
				{
					//checks if ball hit brick on side from below
					if (bBallPosition.x == getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1))
					{
						stateReset();
						removeBlueBricks(i);
						onLeftWallBelow = true;
						break;
					}
				}
				//checks if ball hit brick from above
				if ((bBallPosition.x + BALL_WIDTH) > getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(0) && bBallPosition.x < getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_X_Element(1) && (bBallPosition.y + BALL_HEIGHT) == (getBrick()->getMediumBlueBrick(i)->getBrickBoarderOn_Y_Element(0) + 1))
				{
					stateReset();
					removeBlueBricks(i);
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
	//onDestroyedBrick = false;
}

void BBall::removeYellowBricks(int index)
{
	getBrick()->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
	getBrick()->getSoftYellowBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
	getBrick()->getSoftYellowBrick(index)->clearTexture();
}

void BBall::removeBlueBricks(int index)
{
	getBrick()->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(0, 658);
	getBrick()->getMediumBlueBrick(index)->setBrickBoarderOn_Y_Element(1, 0);
	getBrick()->getMediumBlueBrick(index)->clearTexture();
}