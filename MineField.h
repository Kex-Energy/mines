#pragma once
class MineField
{
	int Real_Field[64];
public:
	int Player_Field[64];
	bool blown_up;
	int mark_count;
	MineField();// -----|герерация поля|-----
	void Open_Selected(int x, int y);//-----Вскрытие клетки-----
	void Mark_Selected(int x, int y);//-----Пометить клетку-----
	bool Check_Win();//-----Победа?-----
	void Open_Field();//-----Вскрытие всех клеток
};

