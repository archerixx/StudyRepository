#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <vector>

using namespace std;

void gameSetup(int&, int&, int&, int&);
void carsPositionSetup(vector<vector<int>>&, const int, const int);
void gui(const vector<vector<int>> &,const int, const int, int&, int&);
void gameLogic(vector<vector<int>>&, const int, const int, int&, int&, bool&, bool&);
inline void movement(int&, int&);

int main()
{
	srand(time(NULL));

	
	char startAgain('y');

	int setH, setW, setMaxC, speed;
	do
	{
		gameSetup(setH, setW, setMaxC, speed);
		bool gameOver = false;
		bool gameWon = false;
		const int height = setH;
		const int width = setW;
		const int maxC = setMaxC;
		int x = width / 2;
		int y = height;
		vector<vector<int>> cars(height, vector<int>(width));
		carsPositionSetup(cars, width, maxC);

		while (!gameOver)
		{
			gui(cars, width, maxC, x, y);
			gameLogic(cars, width, maxC, x, y, gameWon, gameOver);
			Sleep(speed);
		}
		
		if (gameOver == true && gameWon == true)
			cout << "YOU WON";
		else
			cout << "YOU LOST";

		cout << "\nPress any key to continue or \"x\" to exit ";
		cin >> startAgain;
		cin.ignore();
		cin.clear();
	} while (startAgain != 'x');
}

void gameSetup(int& setH, int& setW, int& setMaxC, int& speed)
{
	int difficulty(1);
	char startAgain('y');
	do {
		cout << "Enter difficulty (1-5): ";
		cin >> difficulty;
		switch (difficulty)
		{
		case 1:
			setH = 10;
			setW = 30;
			setMaxC = setW / 10;
			speed = 40;
			break;
		case 2:
			setH = 14;
			setW = 40;
			setMaxC = setW / 9;
			speed = 30;
			break;
		case 3:
			setH = 18;
			setW = 50;
			setMaxC = setW / 8;
			speed = 20;
			break;
		case 4:
			setH = 22;
			setW = 60;
			setMaxC = setW / 7;
			speed = 10;
			break;
		case 5:
			setH = 26;
			setW = 70;
			setMaxC = setW / 6;
			speed = 0;
			break;
		}
	} while (difficulty < 0 || difficulty>5);
}

void carsPositionSetup(vector<vector<int>>& cars, const int width, const int maxC)
{
	for (int i = 1; i < cars.size(); i++)
	{
		for (int j = 0; j < maxC; j++)
		{
			if (i != cars.size() / 2 - 1 && i != cars.size() / 2 + 1 && i != cars.size() / 2)
			{
				cars[i][j] = rand() % (width - 4) + 3;
				for (int p = 0; p < j; p++)
				{
					while (cars[i][j] == cars[i][p] || cars[i][j] == cars[i][p] - 1 || cars[i][j] == cars[i][p] + 1)
					{
						cars[i][j] = rand() % (width - 2) + 1;
						p = 0;
					}
				}
			}
		}
	}
}

void gui(const vector<vector<int>>& cars, const int width, const int maxC, int& x, int& y)
{
	system("cls");
	for (int i = 0; i <=cars.size(); i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (i == y && j == x)
				cout << "o";
			else if (i == 0 || i == cars.size() || i == cars.size() / 2 + 1 || i == cars.size() / 2 - 1)
			{

				cout << "-";
			}
			else if (j == 0)
			{
				cout << "|";
			}
			else if (j == width)
			{
				cout << "|";
			}
			else
			{
				bool whiteSpacePrint = false;
				bool samePlaceCar = false;
				for (int cW = 0; cW < maxC; cW++)
				{
					if (j == cars[i][cW])
					{
						
						for (int p = 0; p < maxC; p++) {
							if (p != cW)
								if (cars[i][cW] == cars[i][p])
								{
									//cout << "A";
									samePlaceCar = true;
								}
						}
						if (samePlaceCar == false)
						{
						
							cout << "B";
							whiteSpacePrint = true;
						}
					}
				}
				if (samePlaceCar == true)
					cout << "B";

				if (whiteSpacePrint == false && samePlaceCar == false)
					cout << " ";

				
			}
		}
		cout << endl;
	}
}

void gameLogic(vector<vector<int>>& cars, const int width, const int maxC, int& x, int& y, bool& gameWon, bool &gameOver)
{
	//win or lose
	if (y < 0)
	{
		gameOver = true;
		gameWon = true;
	}

	//car hit
	for (int cH = 1; cH < cars.size(); cH++)
	{
		for (int cW = 0; cW < maxC; cW++)
		{
			if (cH != cars.size() / 2 - 1 && cH != cars.size() / 2 + 1 && cH != cars.size() / 2)
				if (cH == y && cars[cH][cW] == x)
				{ 
					gameOver = true;
				}
		}
	}

	//car movement (2 lanes different directions)
	for (int cH = 0; cH < cars.size() / 2; cH++)
	{
		for (int cW = 0; cW < maxC; cW++)
		{
			int rBroj = rand() % 2;
			
			if (cars[cH][cW] == width)
			{
				int br = 0;
				if (rBroj == 1)
				{ 
					for (int v = 0; v < maxC; v++)
						if (v!=cW)
							if (cars[cH][v] == 0 || cars[cH][v] == -1)
							{
								br++;
							}
					if (br == 0)
					{
						cars[cH][cW] = 0;
					}
					else
					{
						rBroj = 0;
					}
				}
				else if(rBroj ==0)
				{
					cars[cH][cW] = -5;
				}
			}
			cars[cH][cW]++;
			movement(x, y);
		}
	}
	for (int cH = cars.size() / 2; cH < cars.size(); cH++)
	{
		for (int cW = 0; cW < maxC; cW++)
		{
			int rBroj = rand() % 2;
			
			cars[cH][cW]--;
			movement(x, y);
			if (cars[cH][cW] == 0)
			{
				int br = 0;
				if (rBroj == 1)
				{
					for (int v = 0; v < maxC; v++)
						if (v != cW)
							if (cars[cH][v] == width || cars[cH][v] == width+1)
							{
								br++;
							}
					if (br == 0)
					{
						cars[cH][cW] = width;
					}
					else
					{
						rBroj = 0;
					}
				}
				else if (rBroj == 0)
				{
					cars[cH][cW] = width+5;
				}
			}
		}
	}
}

inline void movement(int& x, int& y)
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			y--;
			break;
		case 's':
			y++;
			break;
		case 'a':
			x--;
			break;
		case 'd':
			x++;
			break;
		default:
			break;
		}
	}
}