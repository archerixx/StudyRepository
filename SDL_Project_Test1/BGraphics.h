#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

//The window we'll be rendering to
extern SDL_Window* baseWindow;
//The window renderer
extern SDL_Renderer* baseRenderer;
//Globally used font
extern TTF_Font* baseFont;

class BGraphics
{
private:
	//game table dimension constants
	const int GAMETABLE_WIDTH = 700;
	const int GAMETABLE_HEIGHT = 600;

	//game table width start
	const int GAMETABLE_WIDTH_START = 100;
	const int GAMETABLE_WIDTH_END = 700;

	//game table height start 
	const int GAMETABLE_HEIGHT_START = 50;
	const int GAMETABLE_HEIGHT_END = 570;

	//Board brick start/end in width
	const int BRICKS_WIDTH_START = 100;
	const int BRICKS_WIDTH_END = 700;

	//Board brick start/end in height
	const int BRICKS_HEIGHT_START = 150;
	const int BRICKS_HEIGHT_END = 200;

	//player board dimension constants
	const int BOARD_WIDTH = 100;
	const int BOARD_HEIGHT = 20;

	//bricks dimensions
	const int BRICK_WIDTH = 50;
	const int BRICK_HEIGHT = 20;

	//spacing between bricks
	const int BRICK_WIDTH_SPACING = 5;
	const int BRICK_HEIGHT_SPACING = 5;

public:

	int getGametableWidth() const;
	int getGametableHeight() const;

	int getGametableWidthStart() const;
	int getGametableWidthEnd() const;

	int getGametableHeightStart() const;
	int getGametableHeightEnd() const;

	int getBricksWidthStart() const;
	int getBricksWidthEnd() const;

	int getBricksHeightStart() const;
	int getBricksHeightEnd() const;

	int getBoardWidth() const;
	int getBoardHeight() const;

	int getBrickWidth() const;
	int getBrickHeight() const;

	int getBrickWidthSpacing() const;
	int getBrickHeightSpacing() const;

};