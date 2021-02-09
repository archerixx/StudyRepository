#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <vector>

using namespace std;

void gui(vector<vector<int>>, int, int, int, int, int);
void movement(int&, int&);
void gameLogic(vector<vector<int>>&, int, int, int, int, int, bool&, bool&);

int main()
{
	/*
int carA = rand() % 20;
int carB = rand() % 20;
int carC = rand() % 20;
int carD = rand() % 20;
int carE = rand() % 20;
int carF = rand() % 20;
*/
	/*
int cars[maxH];
for (int i = 0; i < maxH; i++)
{
	cars[i] = rand() % 20;
}
*/
	/*
int cars[maxH][maxW];
for (int i = 0; i < maxH; i++)
{
	//int temp = maxW / (maxW/10);
	for (int j = 0; j < maxW; j++)
	{
		cars[i][j] = rand() % width;
	}

}
*/

	srand(time(NULL));

	int setH, setW, setMaxC, speed;
	char difficulty;
	char startAgain;
	do
	{
		bool gameOver = false;
		bool gameWon = false;
		do {
			cout << "Enter difficulty: ";
			cin >> difficulty;
			switch (difficulty)
			{
			case '1': 
				setH = 10;
				setW = 30;
				setMaxC = setW / 10;
				speed = 70;
				break;
			case '2':
				setH = 16;
				setW = 40;
				setMaxC = setW / 8;
				speed = 50;
				break;
			case '3':
				setH = 20;
				setW = 50;
				setMaxC = setW / 6;
				speed = 30;
				break;
			default:

				break;
			}
		} while (difficulty > 0 && difficulty < 4);
		const int height = setH;
		const int width = setW;
		const int maxC = setMaxC;
		int x = width / 2;
		int y = height;

		vector<vector<int>> cars(height, vector<int>(width));
		for (int i = 1; i < height; i++)
		{
			for (int j=0; j <maxC; j++)
			{
				if (i != height / 2 - 1 && i != height / 2 + 1 && i != height / 2)
				{
					cars[i][j] = rand() % (width-2);
				}
			}
		}

		while (!gameOver)
		{
			gui(cars, height, width, x, y, maxC);
			movement(x,y);
			gameLogic(cars, height, width, x, y, maxC, gameWon, gameOver);
			Sleep(speed);
		}
		
		if (gameOver == true && gameWon == true)
			cout << "YOU WON";
		else
			cout << "YOU LOST";

		cout << "\nWould you like to play again(y,n): ";
		cin >> startAgain;
	} while (startAgain != 'n');
}

void gui(vector<vector<int>> cars, int height, int width, int x, int y, int maxC)  //int &carA, int& carB, int &carC, int &carD, int &carE, int&carF)
{
	system("cls");
	for (int i = 0; i <=height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (i == y && j == x)
				cout << "o";
			else if (i == 0 || i == height || i == height / 2 + 1 || i == height / 2 - 1)
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
				if (whiteSpacePrint == false)
					cout << " ";
			}
		}
		cout << endl;
	}
}

void movement(int &x, int &y)
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

void gameLogic(vector<vector<int>>& cars, int height, int width, int x, int y, int maxC, bool& gameWon, bool &gameOver)
{
	//win or lose
	if (y < 0)
	{
		gameOver = true;
		gameWon = true;
	}

	//car hit
	for (int cH = 1; cH < height; cH++)
	{
		for (int cW = 0; cW < maxC; cW++)
		{
			if (cH == y && cars[cH][cW] == x)
				gameOver = true;
		}
	}

	//car movement (2 lanes different directions)
	for (int cH = 0; cH < height / 2; cH++)
	{
		for (int cW = 0; cW < maxC; cW++)
		{
			int rBroj = rand() % 2;
			cars[cH][cW]++;
			if (cars[cH][cW] == width)
			{
				if (rBroj == 0)
					cars[cH][cW] = 0;
				else
				{
					cars[cH][cW] = -5;
				}
			}
		}
	}
	for (int cH = height / 2; cH < height; cH++)
	{
		for (int cW = 0; cW < maxC; cW++)
		{
			int rBroj = rand() % 2;
			cars[cH][cW]--;
			if (cars[cH][cW] == 0)
			{
				if (rBroj == 0)
					cars[cH][cW] = width;
				else
				{
					cars[cH][cW] = width + 5;
				}
			}
		}
	}
}