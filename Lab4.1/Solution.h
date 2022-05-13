#pragma once
#include "Cube.h"
#include <algorithm>
#include <random>


static std::vector<std::string> full_rotations{
	"X", "X'", "X2", "Y", "Y'", "Y2"
};

static std::vector<std::string> orientations{
	"Z", "Z'", "Z2"
};

static std::vector<std::string> permutations{
	// permutes two edges : U face, bottom edge and right edge
	"F' L' B' R' U' R U' B L F R U R' U",
	// permutes two edges : U face, bottom edge and left edge
	"F R B L U L' U B' R' F' L' U' L U'",
	// permutes two corners : U face, bottom left and bottom right
	"U2 B U2 B' R2 F R' F' U2 F' U2 F R'",
	//# permutes three corners : U face, bottom left and top left
	"U2 R U2 R' F2 L F' L' U2 L' U2 L F'",
	// permutes three centers : F face, top, right, bottom
	"U' B2 D2 L' F2 D2 B2 R' U'",
	// permutes three centers : F face, top, right, left
	"U B2 D2 R F2 D2 B2 L U",
	// twists one corner clockwise ЭТО МОЯ ФОРМУЛА МОЖЕТ ГОВНО?
	"R F' R' F R F' R' F",
	// Левое, Верхнее и правое ребра передней грани
	//"U2 F' R2 U2 R2 F' R2 U2 F2 R2 U2 R2 F2 R2"
	// U face : bottom edge < ->right edge, bottom right corner < ->top right corner
	"D' R' D R2 U' R B2 L U' L' B2 U R2",
	// U face : bottom edge < ->right edge, bottom right corner < ->left right corner
	"D L D' L2 U L' B2 R' U R B2 U' L2",
	// U face : top edge < ->bottom edge, bottom left corner < ->top right corner
	"R' U L' U2 R U' L R' U L' U2 R U' L U'",
	// U face : top edge < ->bottom edge, bottom right corner < ->top left corner
	"L U' R U2 L' U R' L U' R U2 L' U R' U",
	// permutes three corners : U face, bottom right, bottom leftand top left
	"F' U B U' F U B' U'",
	// permutes three corners : U face, bottom left, bottom rightand top right
	"F U' B' U F' U' B U",
	// permutes three edges : F face bottom, F face top, B face top
	"L' U2 L R' F2 R",
	// permutes three edges : F face top, B face top, B face bottom
	"R' U2 R L' B2 L"
};


class Solution 
{
private:
	
	class Cube_solution : public Cube
	{
	private:

		void calculate_fitness() { fitness = misplaced_stickers(); }

	public:
		int fitness;
		std::string move_history;

		Cube_solution() : Cube(), fitness(100) {}

		bool operator<(const Cube_solution& other) { return this->fitness < other.fitness; }

		Cube_solution(const Cube& other) : Cube(other), fitness(100) {}

		void random_permutation()
		{
			int rnd = rand() % permutations.size();
			execute(permutations[rnd]);
			calculate_fitness();
			move_history += permutations[rnd] + " ";
		}

		void random_rotation()
		{
			int rnd = rand() % full_rotations.size();
			execute(full_rotations[rnd]);
			calculate_fitness();
			move_history += full_rotations[rnd] + " ";
		}

		void random_orientation()
		{
			int rnd = rand() % orientations.size();
			execute(orientations[rnd]);
			calculate_fitness();
			move_history += orientations[rnd] + " ";
		}
	};

private:
	int generations;
	int resets;
	int elitarity;
	int population;
	Cube cube;
	std::vector<Cube_solution> cubes;
	std::string string_solution;
	

public:
	
	Solution(int ppl_, int gens_, int resets_, int elit_, Cube cube_) : 
		cube(cube_), 
		population(ppl_), generations(gens_), 
		resets(resets_), elitarity(elit_), 
		cubes(std::vector<Cube_solution>(population)) {}

	void operator()(void)
	{
		for (int r = 0; r < resets; ++r)
		{
			/*std::cout << "RESET NUMBER : " << r << std::endl;*/

			for (int p = 0; p < population; ++p)
			{
				cubes[p] = cube;
				cubes[p].fitness = cube.misplaced_stickers();

				// rnd operations on start to be executed
			}
			srand((unsigned)time(NULL));
			for (int g = 0; g < generations; ++g)
			{
				std::cout << "GENERATION NUMBER : " << g << std::endl;
				std::sort(cubes.begin(), cubes.end());
				std::cout << "Best cube have " << cubes[0].fitness << " misplaced stickers ";
				//std::cout << cubes[0];

				for (int i = 0; i < cubes.size(); ++i)
				{
					/*if (cubes[i].fitness == 4) 
					{
						std::cout << cubes[i];
						return;
					}*/

					if (cubes[i].fitness == 0)
					{
						string_solution += cubes[i].move_history;
						std::cout << string_solution << std::endl;
						std::cout << cubes[i];
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

};
