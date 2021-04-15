#pragma once

#include "BTexture.h"

//extern BTexture BrickSoftYellowTexture;
//extern BTexture BrickMediumBlueTexture;
//extern BTexture BrickHardRedTexture;

class BBrickType : protected BGraphics  //, public BTexture
{

public:

	//Constructors
	BBrickType();
	BBrickType(char bID, const char* bTexture, int bHitPoints);

	//Destructor
	//~BBrickType();

	//SET functions for private variables
	void setBrickID(char bID);
	void setBrickTexturePath(const char* bTexture);
	void setHitPoints(int bHitPoints);

	//GET function for private vraiables
	int getBrickID() const;
	const char* getBrickTexturePath() const;
	int getHitPoints() const;

	//set element of Pixel Array for X or Y axis
	void setBrickBoarderOn_X_Element(int index, int element);
	void setBrickBoarderOn_Y_Element(int index, int element);

	//GET functions for Pixel Array element
	int getBrickBoarderOn_X_Element(int element);
	int getBrickBoarderOn_Y_Element(int element);

	//SET/GET function for BTexture BrickSoftYellowTexture
	void setYellowBrickTexture(BTexture& texture);
	BTexture getYellowBrickTexture();

	void renderYellowBrick(int x, int y);
	void renderBlueBrick(int x, int y);
	void renderRedBrick(int x, int y);

	bool loadYellowBrickMedia(const char* path);
	bool loadBlueBrickMedia(const char* path);
	bool loadRedBrickMedia(const char* path);

	void clearYellowTexture();
	void clearBlueTexture();
	void clearRedTexture();

	//void renderYellowBrickTest(int x, int y);
	//bool loadYellowBrickMediaTest();

		//Bricks texture
	BTexture BrickSoftYellowTexture;
	BTexture BrickMediumBlueTexture;
	BTexture BrickHardRedTexture;

private: 
	char brickID;
	const char* brickTexturePath;
	int hitPoints;
	//char hitSound;
	//char breakSound;
	//int breakScore;



	//X and Y boarders of brick
	int BrickBoarderOn_X[2] = {0};
	int BrickBoarderOn_Y[2] = {0};

	//	BTexture* BrickSoftYellowTextureTest = new BTexture;
};

