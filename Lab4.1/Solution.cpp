#include "Solution.h"

enum OP { PERMUTATION, ROTATION, ORIENTATION };

static std::vector< std::vector<std::string> > operations{
	{
		"F' L' B' R' U' R U' B L F R U R' U",

		"F R B L U L' U B' R' F' L' U' L U'",

		"U2 B U2 B' R2 F R' F' U2 F' U2 F R'",

		"U2 R U2 R' F2 L F' L' U2 L' U2 L F'",

		"U2 R' U2 R U D' R2 B2 L2 B2 R2 U D F2",

		"D2 R F2 U2 B2 L D F2 D2 R2 F2 U2 B2 L2 D' F2",

		"F2 U2 R2 B2 L2 D' L2 B2 R2 U F2",

		"U' B2 D2 L' F2 D2 B2 R' U'",

		"U B2 D2 R F2 D2 B2 L U",

		"R F' R' F R F' R' F",

		"D' R' D R2 U' R B2 L U' L' B2 U R2",

		"D L D' L2 U L' B2 R' U R B2 U' L2",

		"R' U L' U2 R U' L R' U L' U2 R U' L U'",

		"L U' R U2 L' U R' L U' R U2 L' U R' U",

		"F' U B U' F U B' U'",

		"F U' B' U F' U' B U",

		"L' U2 L R' F2 R",

		"R' U2 R L' B2 L"
	},
	{
		"X", "X'", "X2", "Y", "Y'", "Y2"
	},
	{
		"Z", "Z'", "Z2"
	}
};

void Solution::Cube_solution::random_permutation() 
{
	int rand_pmt = rand() % operations[PERMUTATION].size();
	execute(operations[PERMUTATION][rand_pmt]);
	set_fitness();
	move_seq.push_back({ PERMUTATION, rand_pmt });
}

void Solution::Cube_solution::random_rotation()
{
	int rand_rot = rand() % operations[ROTATION].size();
	execute(operations[ROTATION][rand_rot]);
	set_fitness();
	move_seq.push_back({ ROTATION, rand_rot });
}

void Solution::Cube_solution::random_orientation() 
{
	int rand_ort = rand() % operations[ORIENTATION].size();
	execute(operations[ORIENTATION][rand_ort]);
	set_fitness();
	move_seq.push_back({ ORIENTATION, rand_ort });
}

void Solution::set_string_solution(std::vector<std::pair<int, int> > & seq)
{
	for (auto it = seq.begin(); it != seq.end(); ++it) 
	{
		string_solution += operations[it->first][it->second] + " ";
	}
}

void Solution::operator()()
{

	for (int r = 0; r < resets; ++r)
	{
		//std::cout << "RESET NUMBER : " << r << std::endl;

		for (int p = 0; p < population; ++p)
		{
			cubes[p] = cube;
			cubes[p].fitness = cube.misplaced_stickers();

			// rnd operations on start to be executed
		}
		srand((unsigned)time(NULL));
		for (int g = 0; g < generations; ++g)
		{
			//std::cout << "GENERATION NUMBER : " << g << std::endl;
			std::sort(cubes.begin(), cubes.end());
			//std::cout << "Best cube have " << cubes[0].fitness << " misplaced stickers ";
			//std::cout << cubes[0];

			for (int i = 0; i < cubes.size(); ++i)
			{


				if (cubes[i].fitness == 0)
				{
					set_string_solution(cubes[i].move_seq);
					//std::cout << "SOLUTION IS: \n" << string_solution << std::endl;
					//std::cout << cubes[i];
					return;
				}

				if (i > elitarity)
				{
					cubes[i] = cubes[rand() % elitarity];
					int decision = rand() % 6;
					switch (decision)
					{
					case 0: // random operations to be executed with the cube copy, choosen randmly
						cubes[i].random_permutation();
						break;

					case 1:
						cubes[i].random_permutation();
						cubes[i].random_permutation();
						break;

					case 2:
						cubes[i].random_rotation();
						cubes[i].random_permutation();
						break;

					case 3:
						cubes[i].random_orientation();
						cubes[i].random_permutation();
						break;

					case 4:
						cubes[i].random_rotation();
						cubes[i].random_orientation();
						cubes[i].random_permutation();
						break;

					case 5:
						cubes[i].random_orientation();
						cubes[i].random_rotation();
						cubes[i].random_permutation();
						break;

					}
				}

			}
		}
	}
}