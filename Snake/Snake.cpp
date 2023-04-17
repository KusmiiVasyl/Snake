#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

const int cols = 40;
const int rows = 20;
char field[rows][cols];


void InitGameField(int x, int y, int x_dolar, int y_dolar, int size_snake, int* snake_x, int* snake_y) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == 0 || i == rows - 1)			field[i][j] = char(219);
			else if (j == 0 || j == cols - 1)		field[i][j] = char(219);
			else if (i == y && j == x) 				field[i][j] = char(2);
			else if (i == y_dolar && j == x_dolar) 	field[i][j] = '$';
			else {
				bool dolar = false;
				for (int n = 0; n < size_snake; n++) {
					if (snake_y[n] == i && snake_x[n] == j) {
						field[i][j] = char(253);
						dolar = true;
					}
				}
				if (dolar != true)
					field[i][j] = ' ';
			}
		}
	}
}

void Init_Speed(int score) {
	if (score < 25) Sleep(150);
	else if (score >= 25 && score < 50) Sleep(140);
	else if (score >= 50 && score < 75) Sleep(130);
	else if (score >= 75 && score < 100) Sleep(120);
	else if (score >= 100) Sleep(110);
}
void Show_Speed(int score) {
	if (score < 25) cout << "Speed-1";
	else if (score >= 25 && score < 50) cout << "Speed-2";
	else if (score >= 50 && score < 75) cout << "Speed-3";
	else if (score >= 75 && score < 100) cout << "Speed-4";
	else if (score >= 100) cout << "Speed-5";
}
void ShowStartScreen() {
	for (int i = 0; i < rows; i++) {
		if (i == rows / 6) cout << "\t\tGAME" << endl;
		if (i == (rows / 2) - 3) cout << "\t------S N A K E------" << endl;
		if (i == rows - 6) cout << "       press any key to continue" << endl;
		if (i == 1) cout << "    created by student KUSMII VASYL" << endl;
		else cout << endl;
	}
	system("pause");
	system("cls");
}
void ShowControlPanel() {
	cout << endl << endl;
	for (int t = 0; t < cols; t++)
		cout << char(219);
	cout << endl;
	cout << " Control buttons :" << endl;
	cout << "\tw - up  \tx - exit" << endl;
	cout << "\ta - left\tp - pause " << endl;
	cout << "\td - right " << endl;
	cout << "\ts - down" << endl;
	for (int t = 0; t < cols; t++)
		cout << char(219);
	cout << endl << endl;
	cout << "    press any key to continue" << endl;
	cout << endl << endl << endl;
	system("pause");
	system("cls");
}
void ShowGameOver(int score) {
	for (int i = 2; i < rows; i++) {
		if (i == rows / 2)
			cout << "____________GAME OVER_____________" << endl;
		else if (i == (rows / 2) + 2)
			cout << "\tTOTAL SCORE -> " << score << endl;
		else if (i == (rows / 2) + 4) {
			cout << "\tYOUR SPEED -> ";
			Show_Speed(score);
		}
		else if (i == (rows / 2) + 6) {
			cout << "\n\tpress 1 - to play again " << endl;
			cout << "\tpress x - to exit " << endl;
		}
		else
			cout << endl;
	}
}
void snake(int x, int y, int size_snake, int* snake_x, int* snake_y, char mov) {
	int tmp_x1, tmp_y1, tmp_x2, tmp_y2;
	tmp_x1 = snake_x[0];
	tmp_y1 = snake_y[0];
	snake_x[0] = x;
	snake_y[0] = y;
	if (mov != 'p') {
		for (int i = 1; i < size_snake; i++) {
			tmp_x2 = snake_x[i];
			tmp_y2 = snake_y[i];
			snake_x[i] = tmp_x1;
			snake_y[i] = tmp_y1;
			tmp_x1 = tmp_x2;
			tmp_y1 = tmp_y2;
		}
	}
}
void Input_Play(int& x, int& y, char& mov, int& x_dolar, int& y_dolar, int& size_snake, int* snake_x, int* snake_y, int& score) {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'w':  mov = 'w'; ; break;
		case 's':  mov = 's'; break;
		case 'a':  mov = 'a'; break;
		case 'd':  mov = 'd'; break;
		case 'x':  mov = 'x'; break;
		case 'p':  mov = 'p'; break;
		}
	}
	switch (mov)
	{
	case 'w':  y--; break;
	case 's':  y++; break;
	case 'a':  x--; break;
	case 'd':  x++; break;
	case 'p':  x, y; break;
	}

	if (x == x_dolar && y == y_dolar) {
		size_snake++;
		x_dolar = 1 + rand() % (cols - 2);
		y_dolar = 1 + rand() % (rows - 2);
		score += 5;
	}
}
void ShowGameField(char mov, int score) {
	for (int t = 0; t < cols; t++)
		cout << char(219);
	cout << endl;
	Show_Speed(score);
	cout << "\t\tSCORE  " << score << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << field[i][j];
		}
		cout << endl;
	}
	if (mov == 'p')	cout << "\t\tPAUSE\n" << "press __any motion buttons__ to continue" << endl;
}
bool Exit(char mov, int x, int y, int size_snake, int* snake_x, int* snake_y) {
	if (mov == 'x')  return true;
	if (x <= 0 || x >= cols - 1 || y <= 0 || y >= rows - 1) return true;
	for (int i = 5; i < size_snake; i++) {
		if (x == snake_x[i] && y == snake_y[i])
			return true;
	}
}

int main()
{
	srand(time(NULL));
	char mov = ' ';
	bool GameExit = false;
	int x = cols / 2 - 1;
	int y = rows / 2 - 1;
	int x_dolar = 1 + rand() % (cols - 2);
	int y_dolar = 1 + rand() % (rows - 2);
	int snake_x[cols * rows], snake_y[cols * rows];
	int size_snake = 5;
	int SCORE = 0;

	ShowStartScreen();
	ShowControlPanel();
	while (GameExit != true) {
		InitGameField(x, y, x_dolar, y_dolar, size_snake, snake_x, snake_y);
		ShowGameField(mov, SCORE);
		snake(x, y, size_snake, snake_x, snake_y, mov);
		Input_Play(x, y, mov, x_dolar, y_dolar, size_snake, snake_x, snake_y, SCORE);
		Init_Speed(SCORE);
		GameExit = Exit(mov, x, y, size_snake, snake_x, snake_y);
		if (GameExit == true) {
			Sleep(1200);
			system("cls");
			ShowGameOver(SCORE);
			int key;
			cin >> key;
			if (key == 1) {
				GameExit = false;
				x = cols / 2 - 1;
				y = rows / 2 - 1;
				snake_x[0] = x;
				snake_y[0] = y;
				SCORE = 0;
				size_snake = 5;
			}
		}
		system("cls");
	}



	return 0;
}
