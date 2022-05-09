#include "Cube.h"
#include <Windows.h>
#include <conio.h>


int main() 
{
	
	std::vector< std::vector<int> >cube_src{ {0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 1, 1, 1, 1, 1, 1, 1, 1, 1 }, { 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{3, 3, 3, 3, 3, 3, 3, 3, 3}, {4, 4, 4, 4, 4, 4, 4, 4, 4}, {5, 5, 5, 5, 5, 5, 5, 5, 5} };
	char c = '0';
	Cube cube(cube_src);
	std::cout << cube;
	/*while (true)
	{
		c = getch();
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
		SetCursorPos(0, 0);
		std::cout << cube;
		

	}*/

	return 0;
}