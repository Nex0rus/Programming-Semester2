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
	/*Cube cube;*/
	// U L R D F B X Y Z U' L' R' D' F' B' X2 Y2 Z2 U2 L2 R2 D2 F2 B2 X' Y' Z'
	/*std::cout << cube;
	cube.execute("U L R D F B X Y Z U' L' R' D' F' B' X2 Y2 Z2 U2 L2 R2 D2 F2 B2 X' Y' Z'");
	std::cout << cube;*/


	/*Cube cube;
	cube.scramble();
	Cube cube1 = cube;
	std::cout << cube << std::endl;
	Solution solve(100, 200, 10, 10, cube);
	solve();
	std::cout << std::endl << "SOLUTION IS : " << solve.get_string_solution() << std::endl << cube1;
	cube1.execute(solve.get_string_solution());
	std::cout << cube1;*/

	Cube cube;
	std::ofstream out("in.txt");
	auto begin = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(begin - begin);
	for (int i = 0; i < 30; ++i) 
	{
		std::cout << i << std::endl;
		cube.scramble();
		int misplaced = cube.misplaced_stickers();
		auto begin = std::chrono::steady_clock::now();
		Solution solve(100, 200, 10, 10, cube);
		solve();
		auto end = std::chrono::steady_clock::now();
		elapsed_ms += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		out << elapsed_ms << "\t" << misplaced << std::endl;
	}
	std::cout << "AVG IS : " << elapsed_ms / 30 << std::endl;
	/*cube.execute("L R U R L D");
	cube.free_mod();*/
	/*cube.scramble();
	std::cout << std::endl << cube;*/
	/*std::ifstream is("in.txt");
	is >> cube;
	std::cout << cube << std::endl;
	cube.execute("F B2 U2 F L U' B R L' D' R F' L2 U F2 U' B2 D' F2 D");
	std::cout << cube << std::endl;*/
	/*Solution sol(100, 200, 10, 10, cube);
	sol();*/
	/*cube.scramble(MODE::SHOW);*/
	/*std::ofstream f("Output.txt");
	f << cube;
	f.close();*/
	/*Cube cube2;
	std::cout << cube2;
	std::ifstream is("Output.txt");
	is >> cube2;
	std::cout << cube2;*/

	//std::cout << cube;
	//std::cout << cube;
	//cube.execute("X F U' B' U F' U' B U Z Y U2 R U2 R' F2 L F' L' U2 L' U2 L F' X2 Z2 U' B2 D2 L' F2 D2 B2 R' U' Z Y F U' B' U F' U' B U Y R' U L' U2 R U' L R' U L' U2 R U' L U' R' U2 R L' B2 L R' U2 R L' B2 L Z2 R' U2 R L' B2 L U B2 D2 R F2 D2 B2 L U Z X' D L D' L2 U L' B2 R' U R B2 U' L2 U2 R U2 R' F2 L F' L' U2 L' U2 L F' L' U2 L R' F2 R F R B L U L' U B' R' F' L' U' L U' F' U B U' F U B' U' U' B2 D2 L' F2 D2 B2 R' U' F' L' B' R' U' R U' B L F R U R' U X' Z2 R' U L' U2 R U' L R' U L' U2 R U' L U' R' U L' U2 R U' L R' U L' U2 R U' L U' Z Y U' B2 D2 L' F2 D2 B2 R' U' Y2 U' B2 D2 L' F2 D2 B2 R' U' Z X F R B L U L' U B' R' F' L' U' L U' F' L' B' R' U' R U' B L F R U R' U F R B L U L' U B' R' F' L' U' L U' Y R' U2 R L' B2 L Z2 X' R' U2 R L' B2 L Z Y F R B L U L' U B' R' F' L' U' L U' Y F R B L U L' U B' R' F' L' U' L U' U B2 D2 R F2 D2 B2 L U F' L' B' R' U' R U' B L F R U R' U F' L' B' R' U' R U' B L F R U R' U D' R' D R2 U' R B2 L U' L' B2 U R2 D L D' L2 U L' B2 R' U R B2 U' L2 Y' R' U2 R L' B2 L", MODE::HIDE);
	/*cube.execute("U L");*/
	//std::cout << cube;
	/*Solution sol(1000, 100, 10, 100, cube);
	sol();*/
	return 0;
}