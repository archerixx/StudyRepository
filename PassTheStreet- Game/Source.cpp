#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;

const int width(50), height(16);
int x = width / 2;
int y = height;
bool gameOver = false;
const int maxH = height - 4;
const int maxW = width/10;
bool gameWon = false;


void gui(int cars[][width])  //int &carA, int& carB, int &carC, int &carD, int &carE, int&carF)
{
	system("cls");
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (i == y && j == x)
				cout << "o";
			else if (i == 0 || i == height || i == height / 2 + 1 || i == height / 2 - 1)
			{
				
				cout << "-";
			}
			else if (j == 0 || j == width)
			{
				cout << "|";
			}
			else
			{
				bool whiteSpacePrint = false;

				/*
				for (int cH = maxH/2, temp=1;  temp < maxH / 2, cH < maxH; cH++, temp++)
				{
					if ((i == (height)/2 + temp+1) && j == cars[cH][maxH])
					{
						cout << "B";
						whiteSpacePrint = true;
					}

				}
				*/
				
				
				/*
				for (int cH = 0; cH < maxH/2; cH++)
				{
					for (int cW=0; cW< maxW; cW++)
					{ 
						if ((i==0+(cH+1)) && j == cars[cH][cW])
						{ 
							cout << "B";
							whiteSpacePrint = true;
						}
					}
				}
				
				for (int cH = maxH/2, temp(2); cH <= maxH ; cH++, temp++)
				{
					for (int cW = 0; cW < maxW; cW++)
					{
						if ((i == height/2+temp) && j == cars[cH][cW])
						{
							cout << "B";
							whiteSpacePrint = true;
						}
					}
				}
				*/
				for (int cH = 0; cH <= height; cH++)
				{
					for (int cW = 0; cW <= width; cW++)
					{
						if (i == cH && j == cars[cH][cW])
						{
							cout << "B";
							whiteSpacePrint = true;
						}
					}
				}


				if (!whiteSpacePrint)
					cout << " ";
				
				/*
				if (i == height - 1 && j == carA)
					cout << "B";
				else if (i == height - 2 && j == carB)
					cout << "B";
				else if (i == height - 3 && j == carB)
					cout << "B";
				else if (i == height - 6 && j == carC)
					cout << "B";
				else if (i == height - 7 && j == carD)
					cout << "B";
				else if (i == height - 8 && j == carE)
					cout << "B";
				else if (i == height - 9 && j == carF)
					cout << "B";
				else
					cout << " ";
					*/
			}
			
		}
		cout << endl;
	}
}

void movement()
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

void gameLogic(int cars[][width])   //int &carA, int &carB, int& carC, int& carD, int& carE, int& carF)
{
	if (y < 0)
	{
		gameOver = true;
		gameWon = true;
	}
	
	for (int cH = 1; cH < height; cH++)
	{
		for (int cW = 0; cW < width; cW++)
		{
			if (cH == y && cars[cH][cW]==x)
				gameOver = true;
		}
	}
	
	/*
	for (int p = 0; p < height - 4; p++)
	{
		if (cars[p] == x)
			gameOver = true;
	}
	*/
	/*
	for (int k = 0; k < maxH; k++)
	{ 
		cars[k]++;
		if (cars[k] == width)
			cars[k] = 0;
	}
	*/
	for (int cH = 0; cH < height; cH++)
	{
		
		for (int cW=0; cW <= width; cW++)
		{ 
			cars[cH][cW]++;
			if (cars[cH][cW] == width)
				cars[cH][cW] = 0;
		}
		/*
		for (int cW = 0; cW < width; cW+=2)
		{
			cars[cH][cW]--;
			if (cars[cH][cW] == 0)
				cars[cH][cW] = width;
		}
		*/
	}
	// tri reda u obe strane
	/*
	for (int cH = 0; cH < height / 2-4; cH++)
	{
		for (int cW = 0; cW < width; cW++)
		{
			cars[cH][cW]++;
			if (cars[cH][cW] == width)
				cars[cH][cW] = 0;
		}
	}


	for (int cH = height/2-4; cH < height/2; cH++)
	{
		for (int cW = 0; cW < width; cW++)
		{
			cars[cH][cW]--;
			if (cars[cH][cW] == 0)
				cars[cH][cW] = width;
		}
	}

	for (int cH = height / 2; cH < height/2+4; cH++)
	{
		for (int cW = 0; cW < width; cW++)
		{
			cars[cH][cW]++;
			if (cars[cH][cW] == width)
				cars[cH][cW] = 0;
		}
	}

	for (int cH = height / 2+4; cH < height; cH++)
	{
		for (int cW = 0; cW < width; cW++)
		{
			cars[cH][cW]--;
			if (cars[cH][cW] == 0)
				cars[cH][cW] = width;
		}
	}
	*/
	/*
	//so it can move to the right
	carA++;
	//for it to come back to beginning
	if (carA == width)
		carA = 0;

	//carB
	//so it can move to the right
	carB++;
	//for it to come back to beginning
	if (carB == width)
		carB = 0;

	carC++;
	if (carC == width)
		carC = 0;

	carD++;
	if (carD == width)
		carD = 0;

	carE++;
	if (carE == width)
		carE = 0;

	carF++;
	if (carF == width)
		carF = 0;
		*/
}

int main()
{
	srand(time(NULL));
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

	int cars[height][width];
	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j < width/7; j++)
		{
			if (i != height / 2 - 1 && i != height / 2 + 1 && i != height / 2)
			{
				cars[i][j] = rand() % width;
			}
		}
	}


	while (!gameOver)
	{
		gui(cars);
		movement();
		gameLogic(cars);
		Sleep(100);
	}
		
	if (gameOver == true && gameWon == true)
		cout << "YOU WON";
	else
		cout << "YOU LOST";

	cin.get();
	cin.get();
	cin.get();
	cin.get();

}