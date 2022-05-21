#pragma once
#include "Cube.h"
#include <algorithm>
#include <random>
#include <fstream>

// Solution class is a functor that provides solving algorithm for a Cube class
class Solution 
{
private:
	
	// Cube_solution is a wrapping class over a Cube class 
	// with methods used in genetic algorithm
	class Cube_solution : public Cube 
	{
	private:

		// fitness is an int value showing 
		// the number of stickers to be set correctly
		void set_fitness() { fitness = misplaced_stickers(); }

	public:
		int fitness;

		// a vector of indexes related to "operations" vector 
		// presenting a move sequence
		std::vector<std::pair<int, int> > move_seq; 

		Cube_solution() : Cube(), fitness(100) {}  

		bool operator<(const Cube_solution& other) { return this->fitness < other.fitness; }

		Cube_solution(const Cube& other) : Cube(other), fitness(100) {}

		// applies permutation that is randomly picked from "operations" vector
		void random_permutation(); 

		// applies rotation that is randomly picked from "operations" vector (X, X', X2, Y, Y', Y2)
		void random_rotation();    

		// applies orientation that is randomly picked from "operations" vector (Z, Z', Z2)
		void random_orientation(); 
	};

private:
	// the number of iterations over one data set
	int generations; 
	// the number of data set regenerations 
	int resets;      
	// the number of cubes that remains without change
	int elitarity;   
	// the number of cubes in a single data set
	int population;  
	// the original cube to be solved
	Cube cube;       
	// the data set vector used for algorithm 
	std::vector<Cube_solution> cubes;
	// the sequence of moves to be executed to solve the Cube
	std::string string_solution; 
	// transfers move_seq to string with moves
	void set_string_solution(std::vector<std::pair<int, int> > & seq); 

public:
	
	Solution(int ppl_, int gens_, int resets_, int elit_, Cube cube_) : 
		cube(cube_), 
		population(ppl_), generations(gens_), 
		resets(resets_), elitarity(elit_), 
		cubes(std::vector<Cube_solution>(population)), string_solution("") {}

	// getter to return a solution as a string
	std::string get_string_solution() 
	{
		return string_solution;
	}

	// solver algorithm returns 0 if a cube is solved less than in 10 resets 
    // (tests showed that if the cube is not solved in 10 resets than it is probably invalid)
	// if the cube is not solved in 10 resets - returns 1 as a flag showing the cube is invalid
	int operator()(); 
};
