#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "MineField.h"
using namespace std;
int main()
{
	int nScreenWidth = 80;			// Console Screen Size X (columns)
	int nScreenHeight = 30;			// Console Screen Size Y (rows)
	MineField Game;
	int key;
	int x_sel=0, y_sel=0;
	bool win = false;
	wstring table;
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < 80 * 30; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	table.append(L"┍─┭─┭─┭─┭─┭─┭─┭─┑");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┝─┽─┽─┽─┽─┽─┽─┽─┥");
	table.append(L"│ │ │ │ │ │ │ │ │");
	table.append(L"┕─┵─┵─┵─┵─┵─┵─┵─┙");
	while (1)
	{
		if (win || Game.blown_up) Game.Open_Field();
		for (int y = 0; y < 17; y++)
		{
			for (int x = 0; x < 17; x++)
			{
				screen[x + y * nScreenWidth] = table[x + y * 17];
			}
		}
		int npole = 0; //для нахождения соответствующей клетки поля игры и поля экрана
		for (int y = 1; y < 17; y += 2)
		{
			for (int x = 1; x < 17; x += 2)
			{
				if (npole == x_sel + (y_sel * 8)) screen[x + y * nScreenWidth] = L"_①②③④⑤⑥⑦⑧□☢⚑"[Game.Player_Field[npole]];
				else screen[x + y * nScreenWidth] = L" 12345678#*?"[Game.Player_Field[npole]];
				npole++;
			}
		}
		swprintf_s(&screen[2 * nScreenWidth + 18], 12, L"Управление:");
		swprintf_s(&screen[3 * nScreenWidth + 18], 30, L"Перемещать маркер - стрелочки");
		swprintf_s(&screen[4 * nScreenWidth + 18], 42, L"insert - отметить delete - открыть клетку");
		swprintf_s(&screen[5 * nScreenWidth + 18], 12, L"esc - выход");
		swprintf_s(&screen[10 * nScreenWidth + 18], 22, L"Кол-во отмеченных: %2d", Game.mark_count);
		if(win && !Game.blown_up) swprintf_s(&screen[11 * nScreenWidth + 18], 4, L"Win");
		if(!win && Game.blown_up) swprintf_s(&screen[11 * nScreenWidth + 18], 5, L"Lose");
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		key = _getch();
		if(key == 224)
		key = _getch();
		if (!win || !Game.blown_up) 
		{
			switch (key)
			{
			case 72://нажатие вверх
				if (y_sel != 0) y_sel--;
				break;
			case 80://нажатие вниз
				if (y_sel != 7) y_sel++;
				break;
			case 75://нажатие влево
				if (x_sel != 0) x_sel--;
				break;
			case 77://нажатие вправо
				if (x_sel != 7) x_sel++;
				break;
			case 83://открытие
				if (Game.Player_Field[x_sel + (y_sel * 8)] != 11)
					Game.Open_Selected(x_sel, y_sel);
				break;
			case 82://отметить
				Game.Mark_Selected(x_sel, y_sel);
				win = Game.Check_Win();
				break;
			default:
				break;
			}
			if (key == 27) return 0;
		}
	}

}