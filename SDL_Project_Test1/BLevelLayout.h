#pragma once

class BLevelLayout 
{
public:
	//Constructors
	BLevelLayout();
	BLevelLayout(int rowCount, int columnCount, int rowSpacing, int columnSpacing, const char* backGroundTexture, int ballLives);

	//GET class variables
	int getRowCount() const;
	int getColumnCount() const;
	int getRowSpacing() const;
	int getColumtSpacing() const;
	const char* getBackGroundTexture() const;
	int getBallLives() const;

	void setBrickRowCount(int rowCount);
	void setBrickColumnCount(int columnCount);
	void setBrickRowSpacing(int rowSpacing);
	void setbrickColumnSpacing(int columnSpacing);
	void setBackgroundTexture(const char* backgroundTexture);
	void setBallLives(int lifesLeft);

private:
	int brickRowCount;
	int brickColumnCount;
	int brickRowSpacing;
	int brickColumnSpacing;
	const char* backgroundTexture;
	int ballLives;

};