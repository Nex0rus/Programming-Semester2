#include "Solution.h"


int main()
{
	std::vector< std::vector<int> >cube_src1{ 
		{ORANGE, BLUE, WHITE, BLUE, GREEN, RED, GREEN, GREEN, GREEN },
		{ YELLOW, YELLOW, YELLOW, GREEN, WHITE, RED, RED, ORANGE, RED },
		{ RED, WHITE, ORANGE, BLUE, ORANGE, ORANGE, BLUE, RED, WHITE },
		{YELLOW, GREEN, BLUE, WHITE, YELLOW, YELLOW, GREEN, RED, BLUE},
		{ORANGE, WHITE, BLUE, GREEN, RED, ORANGE, RED, BLUE, WHITE},
		{YELLOW, YELLOW, ORANGE, YELLOW, BLUE, WHITE, GREEN, ORANGE, WHITE} 
	};
	std::vector< std::vector<int> >cube_src2{
		{BLUE, RED, YELLOW, WHITE, YELLOW, BLUE, BLUE, ORANGE, ORANGE},
		{YELLOW, GREEN, YELLOW, ORANGE, GREEN, ORANGE, RED, GREEN, ORANGE},
		{ORANGE, BLUE, GREEN, GREEN, ORANGE, WHITE, BLUE, YELLOW, RED},
		{WHITE, WHITE, GREEN, RED, BLUE, ORANGE, WHITE, BLUE, RED},
		{ORANGE, BLUE, RED, WHITE, RED, YELLOW, YELLOW, YELLOW, WHITE},
		{WHITE, RED, BLUE, RED, WHITE, YELLOW, GREEN, GREEN, GREEN}
	};
	char c = '0';
	Cube cube(cube_src2);
	//cube.free_mod();
	cube.execute("X F U' B' U F' U' B U Z Y U2 R U2 R' F2 L F' L' U2 L' U2 L F' X2 Z2 U' B2 D2 L' F2 D2 B2 R' U' Z Y F U' B' U F' U' B U Y R' U L' U2 R U' L R' U L' U2 R U' L U' R' U2 R L' B2 L R' U2 R L' B2 L Z2 R' U2 R L' B2 L U B2 D2 R F2 D2 B2 L U Z X' D L D' L2 U L' B2 R' U R B2 U' L2 U2 R U2 R' F2 L F' L' U2 L' U2 L F' L' U2 L R' F2 R F R B L U L' U B' R' F' L' U' L U' F' U B U' F U B' U' U' B2 D2 L' F2 D2 B2 R' U' F' L' B' R' U' R U' B L F R U R' U X' Z2 R' U L' U2 R U' L R' U L' U2 R U' L U' R' U L' U2 R U' L R' U L' U2 R U' L U' Z Y U' B2 D2 L' F2 D2 B2 R' U' Y2 U' B2 D2 L' F2 D2 B2 R' U' Z X F R B L U L' U B' R' F' L' U' L U' F' L' B' R' U' R U' B L F R U R' U F R B L U L' U B' R' F' L' U' L U' Y R' U2 R L' B2 L Z2 X' R' U2 R L' B2 L Z Y F R B L U L' U B' R' F' L' U' L U' Y F R B L U L' U B' R' F' L' U' L U' U B2 D2 R F2 D2 B2 L U F' L' B' R' U' R U' B L F R U R' U F' L' B' R' U' R U' B L F R U R' U D' R' D R2 U' R B2 L U' L' B2 U R2 D L D' L2 U L' B2 R' U R B2 U' L2 Y' R' U2 R L' B2 L", MODE::SHOW);
	/*cube.execute("U L");*/
	/*std::cout << cube;*/
	/*std::cout << cube.misplaced_stickers();*/
	/*Solution sol(1000, 100, 10, 100, cube);
	sol.solve();*/
	return 0;
}
