#pragma once
class MineField
{
	int Real_Field[64];
public:
	int Player_Field[64];
	bool blown_up;
	int mark_count;
	MineField();// -----|��������� ����|-----
	void Open_Selected(int x, int y);//-----�������� ������-----
	void Mark_Selected(int x, int y);//-----�������� ������-----
	bool Check_Win();//-----������?-----
	void Open_Field();//-----�������� ���� ������
};

