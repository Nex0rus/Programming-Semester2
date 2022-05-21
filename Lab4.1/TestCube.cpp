#include "Solution.h"
#include <fstream>

int main()
{
	std::vector< std::vector<char> >cube_src1{ 
		{ORANGE, BLUE, WHITE, BLUE, GREEN, RED, GREEN, GREEN, GREEN },
		{ YELLOW, YELLOW, YELLOW, GREEN, WHITE, RED, RED, ORANGE, RED },
		{ RED, WHITE, ORANGE, BLUE, ORANGE, ORANGE, BLUE, RED, WHITE },
		{YELLOW, GREEN, BLUE, WHITE, YELLOW, YELLOW, GREEN, RED, BLUE},
		{ORANGE, WHITE, BLUE, GREEN, RED, ORANGE, RED, BLUE, WHITE},
		{YELLOW, YELLOW, ORANGE, YELLOW, BLUE, WHITE, GREEN, ORANGE, WHITE} 
	};
	std::vector< std::vector<char> >cube_src2{
		{BLUE, RED, YELLOW, WHITE, YELLOW, BLUE, BLUE, ORANGE, ORANGE},
		{YELLOW, GREEN, YELLOW, ORANGE, GREEN, ORANGE, RED, GREEN, ORANGE},
		{ORANGE, BLUE, GREEN, GREEN, ORANGE, WHITE, BLUE, YELLOW, RED},
		{WHITE, WHITE, GREEN, RED, BLUE, ORANGE, WHITE, BLUE, RED},
		{ORANGE, BLUE, RED, WHITE, RED, YELLOW, YELLOW, YELLOW, WHITE},
		{WHITE, RED, BLUE, RED, WHITE, YELLOW, GREEN, GREEN, GREEN}
	};
	char c = '0';

	Cube cube;
	Cube cube1;
	auto begin = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(begin - begin);
	int ret = 0;
	cube.scramble();
	cube.free_mode();
	//for (int i = 0; i < 100; ++i) 
	//{
	//	std::cout << i << std::endl;
	//	cube.scramble();
	//	int misplaced = cube.misplaced_stickers();
	//	auto begin = std::chrono::steady_clock::now();
	///*	Solution solve(500, 75, 20, 50, cube);
	//	ret = solve();
	//	if (ret != 0) 
	//	{
	//		std::cout << "PROBLEM OCCURED" << cube;
	//	}*/
	//	std::ofstream out("in.txt");
	//	out << cube;
	//	std::ifstream is("in.txt");
	//	is >> cube1;
	//	std::cout << cube1;
	//	auto end = std::chrono::steady_clock::now();
	//	elapsed_ms += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	//	out << elapsed_ms << "\t" << misplaced << std::endl;
	//}
	//std::cout << "AVG IS : " << elapsed_ms / 30 << std::endl;

	return 0;
}