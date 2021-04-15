#pragma once

class BLevel 
{

private:
	int RowCount;
	int ColumnCount;
	int RowSpacing;
	int ColumnSpacing;
	const char* BackGroundTexture;

public:
	BLevel();
	BLevel(int RC, int CC, int RS, int CS, const char* BGT);

	int getRowCount() const;
	int getColumnCount() const;
	int getRowSpacing() const;
	int getColumtSpacing() const;
	const char* getBackGroundTexture() const;
};