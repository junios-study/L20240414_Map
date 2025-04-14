#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

struct CharacterInfo
{
	int X;
	int Y;
	char Shape;
};


//전역변수
int MapHeight = 10;
int KeyCode = 0;
CharacterInfo* Player = nullptr;
CharacterInfo* Monster = nullptr;

string* Map;
bool IsRunning = true;



void Initialize();
void Input();
void Tick();
void Render();
void GotoXY(int x, int y);
void Terminate();
bool Predict(int PredictX, int PredictY);





int main()
{
	Initialize();

	while (IsRunning)  //frame, game loop
	{
		Input();
		Tick();
		Render();
	}

	Terminate();

	return 0;
}

void Initialize()
{
	//Load
	Map = new string[MapHeight];
	//FILE
	Map[0] = "***************";
	Map[1] = "*        ******";
	Map[2] = "*        *** **";
	Map[3] = "*        **  **";
	Map[4] = "****     **  **";
	Map[5] = "*        *  ***";
	Map[6] = "*          ****";
	Map[7] = "*   *    ******";
	Map[8] = "*   *    ******";
	Map[9] = "***************";

	Player = new CharacterInfo();
	Player->X = 1;
	Player->Y = 1;
	Player->Shape = 'P';

	Monster = new CharacterInfo();
	Monster->X = 8;
	Monster->Y = 8;
	Monster->Shape = 'M';

	srand((unsigned int)(time(nullptr)));

}

void Input()
{
	KeyCode = _getch(); //Device에서 입력 신호 캐치
}

void Tick()
{
	//Player
	if (KeyCode == 'w' && Predict(Player->X, Player->Y - 1))
	{
		Player->Y--;
	}
	if (KeyCode == 's' && Predict(Player->X, Player->Y + 1))
	{
		Player->Y++;
	}
	if (KeyCode == 'a' && Predict(Player->X - 1, Player->Y))
	{
		Player->X--;
	}
	if (KeyCode == 'd' && Predict(Player->X + 1, Player->Y))
	{
		Player->X++;
	}

	if (KeyCode == 'q')
	{
		IsRunning = false;
	}

	//AI(Random, HP, Attack, 행동트리, FSM, Tick )
	//Monster
	int Direction = rand() % 4;
	if (Direction == 0)
	{
		if (Predict(Monster->X, Monster->Y - 1))
		{
			Monster->Y--;
		}
	}
	if (Direction == 1)
	{
		if (Predict(Monster->X, Monster->Y + 1))
		{
			Monster->Y++;
		}
	}
	if (Direction == 2)
	{
		if (Predict(Monster->X - 1, Monster->Y))
		{
			Monster->X--;
		}
	}
	if (Direction == 3)
	{
		if (Predict(Monster->X + 1, Monster->Y))
		{
			Monster->X++;
		}
	}
}

void Render()
{
	//system("cls");
	for (int Y = 0; Y < MapHeight; ++Y)
	{
		for (int X = 0; X < Map[Y].length(); ++X)
		{
			GotoXY(X, Y);
			cout << Map[Y][X];
		}
	}



	//Actor, Pawn
	GotoXY(Player->X, Player->Y);
	cout << Player->Shape;

	GotoXY(Monster->X, Monster->Y);
	cout << Monster->Shape;
}

void GotoXY(int X, int Y)
{
	COORD Pos;
	Pos.X = X;
	Pos.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Terminate()
{
	delete Player;
	Player = nullptr;

	delete Monster;
	Monster = nullptr;

	delete[] Map;
	Map = nullptr;
}

bool Predict(int PredictX, int PredictY)
{
	if (Map[PredictY][PredictX] == ' ')
	{
		return true;
	}

	return false;
}
