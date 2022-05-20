#pragma once
#include "Cube.h"
#include <algorithm>
#include <random>
#include <fstream>


class Solution 
{
private:
	
	class Cube_solution : public Cube
	{
	private:

		void set_fitness() { fitness = misplaced_stickers(); }

	public:
		int fitness;
		std::vector<std::pair<int, int> > move_seq;

		Cube_solution() : Cube(), fitness(100) {}

		bool operator<(const Cube_solution& other) { return this->fitness < other.fitness; }

		Cube_solution(const Cube& other) : Cube(other), fitness(100) {}

		void random_permutation();

		void random_rotation();

		void random_orientation();
	};

private:
	int generations;
	int resets;
	int elitarity;
	int population;
	Cube cube;
	std::vector<Cube_solution> cubes;
	std::string string_solution;
	void set_string_solution(std::vector<std::pair<int, int> > & seq);

public:
	
	Solution(int ppl_, int gens_, int resets_, int elit_, Cube cube_) : 
		cube(cube_), 
		population(ppl_), generations(gens_), 
		resets(resets_), elitarity(elit_), 
		cubes(std::vector<Cube_solution>(population)), string_solution("") {}

	std::string get_string_solution()
	{
		return string_solution;
	}

	void operator()();

};
