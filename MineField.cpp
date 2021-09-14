#include "MineField.h"
#include <vector>
#include <ctime>
#include <cstdlib>

// -----|ãåðåðàöèÿ ïîëÿ|------
MineField::MineField() 
{
	mark_count = 0;
	blown_up = false;
	srand(time(NULL));
	std::vector<int> i_empty;
	int r,
		x_cur, y_cur;
	bool x_0 = false, x_7 = false,
		 y_0 = false, y_7 = false;
	for (int i = 0; i < 64; i++) 
	{
		Player_Field[i] = 9;
		Real_Field[i] = 0;
		i_empty.push_back(i);
	}
	for (int i = 0; i < 10; i++) 
	{
		r = rand() % (64 - i);
		Real_Field[i_empty[r]] = -9;
		y_cur = i_empty[r] / 8;
		x_cur = i_empty[r] - y_cur * 8;
		x_0 = x_cur == 0;
		x_7 = x_cur == 7;
		y_0 = y_cur == 0;
		y_7 = y_cur == 7;
		if(x_0)
		{
			Real_Field[x_cur + 1 + y_cur * 8] += 1;
			if (!y_7) 
			{
				Real_Field[x_cur  + (y_cur + 1) * 8] += 1;
				Real_Field[x_cur + 1 + (y_cur + 1) * 8] += 1;
			}
			if (!y_0) 
			{
				Real_Field[x_cur + (y_cur - 1) * 8] += 1;
				Real_Field[x_cur + 1 + (y_cur - 1) * 8] += 1;
			}
		}
		if (x_7) 
		{
			Real_Field[x_cur - 1 + y_cur * 8] += 1;
			if (!y_7)
			{
				Real_Field[x_cur + (y_cur + 1) * 8] += 1;
				Real_Field[x_cur - 1 + (y_cur + 1) * 8] += 1;
			}
			if (!y_0)
			{
				Real_Field[x_cur + (y_cur - 1) * 8] += 1;
				Real_Field[x_cur - 1 + (y_cur - 1) * 8] += 1;
			}
		}
		if (!x_7 && !x_0) 
		{
			Real_Field[x_cur - 1 + y_cur * 8] += 1;
			Real_Field[x_cur + 1 + y_cur * 8] += 1;
			if (!y_7)
			{
				Real_Field[x_cur + (y_cur + 1) * 8] += 1;
				Real_Field[x_cur - 1 + (y_cur + 1) * 8] += 1;
				Real_Field[x_cur + 1 + (y_cur + 1) * 8] += 1;
			}
			if (!y_0)
			{
				Real_Field[x_cur + (y_cur - 1) * 8] += 1;
				Real_Field[x_cur - 1 + (y_cur - 1) * 8] += 1;
				Real_Field[x_cur + 1 + (y_cur - 1) * 8] += 1;
			}
		}
		i_empty.erase(i_empty.begin() + r);

	}

}
//-----Âñêðûòèå êëåòêè-----
void MineField::Open_Selected(int x, int y)
{
	Player_Field[x + (y * 8)] = Real_Field[x + (y * 8)];
	if (Real_Field[x + (y * 8)] < 0) 
	{
		Player_Field[x + (y * 8)] = 10;
		blown_up = true;
		return;
	}
	if (Real_Field[x + (y * 8)] == 0) 
	{
		if ((x != 7) && (Player_Field[x + 1 + (y * 8)] == 9))Open_Selected(x + 1, y);
		if ((x != 0) && (Player_Field[x - 1 + (y * 8)] == 9))Open_Selected(x - 1, y);
		if ((y != 7) && (Player_Field[x + ((y + 1) * 8)] == 9))Open_Selected(x, y + 1);
		if ((y != 0) && (Player_Field[x + ((y - 1) * 8)] == 9))Open_Selected(x, y - 1);
	}
	return;
}
//-----Ïîìåòèòü êëåòêó-----
void MineField::Mark_Selected(int x, int y)
{
		if (Player_Field[x  + (y * 8)] == 9 && mark_count != 10)
		{
			Player_Field[x + (y * 8)] = 11;
			mark_count++;
		}
		else if (Player_Field[x + (y * 8)] == 11) 
		{
			Player_Field[x + (y * 8)] = 9;
			mark_count--;
		}
	return;
}
//-----Ïîáåäà?-----
bool MineField::Check_Win()
{
	int count_true_marked = 0;
	for (int i = 0;i < 64;i++) 
	{
		if (Player_Field[i] == 11 && Real_Field[i] < 0)
			count_true_marked++;
	}
	return count_true_marked == 10;
}

void MineField::Open_Field()
{
	for (int i = 0;i < 64;i++)
	{
		Player_Field[i] = Real_Field[i];
	}
}
