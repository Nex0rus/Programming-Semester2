#include "Cube.h"
#include <conio.h>
#include <windows.h>
void setcur(int x, int y)//установка курсора на позицию  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void free_mod(Cube& cube)
{
	char c = '0';
	while (c != 'q')
	{
		c = _getch();
		if (c == 'u')
		{
			cube.clockwise_rot_up();
		}
		if (c == 'd')
		{
			cube.clockwise_rot_down();
		}
		if (c == 'l')
		{
			cube.clockwise_rot_left();
		}
		if (c == 'r')
		{
			cube.clockwise_rot_right();
		}
		if (c == 'f')
		{
			cube.clockwise_rot_front();
		}
		if (c == 'b')
		{
			cube.clockwise_rot_back();
		}

		setcur(0, 0);
		std::cout << cube;


	}
}

int main()
{
	/*std::vector< std::vector<int> >cube_src{ { 3, 1, 0, 0, 0, 1, 3, 0, 0 }, { 1, 1, 2, 1, 2, 4, 3, 1, 1 }, { 2, 2, 3, 4, 3, 2, 2, 2, 2 },
		{3, 3, 4, 3, 4, 3, 3, 3, 3}, {4, 1, 5, 4, 5, 2, 4, 4, 4}, {2, 4, 5, 3, 5, 1, 5, 4, 5} };
	Cube cube(cube_src);
	std::cout << cube << std::endl;
	cube.counter_clockwise_rot_back();
	std::cout << cube << std::endl;*/
	std::vector< std::vector<int> >cube_src{ {0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{3, 3, 3, 3, 3, 3, 3, 3, 3}, {4, 4, 4, 4, 4, 4, 4, 4, 4}, {5, 5, 5, 5, 5, 5, 5, 5, 5} };
	char c = '0';
	Cube cube(cube_src);
	std::cout << cube;
	free_mod(cube);
	return 0;
}
