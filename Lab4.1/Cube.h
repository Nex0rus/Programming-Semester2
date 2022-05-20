#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <Windows.h>
#include <sstream>
#include <string>
#include <conio.h>
#include <chrono>
#include <atomic>
#include <thread>
#include <future>

class Cube;

enum COLORS { WHITE, ORANGE, GREEN, RED, BLUE, YELLOW };
enum COORDS { X = 1, Y = 2, Z = 3 };
enum FACES { U, L, F, R, B, D };
enum MODE { HIDE, SHOW };
enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

//setting a position of a cursor to (x, y) coordinate
void setcur(int x, int y);  

// changes a color of a console font
void setColor(unsigned fg);

  /////////////////////////////
 //       Cubie class       //
/////////////////////////////
class Cubie
{
private:
	char color;

public:

	Cubie& operator=(char color_)
	{
		color = color_;
		return *this;
	}

	// displays one sticker with its color in the ostream
	friend std::ostream& operator<<(std::ostream& os, const Cubie& cubie);

	bool operator!=(const Cubie & other) { return (this->color != other.color); }

};


  ////////////////////////////
 //       Line class       //
////////////////////////////

class Line
{
private:
	std::vector<Cubie> cubies;
public:

	Line() : cubies(std::vector<Cubie>(3)) {}

	Line(std::vector<char> colors) { (*this) = colors; }

	friend std::ostream& operator<<(std::ostream& os, const Line& line)
	{
		for (int i = 0; i < 3; ++i)
		{
			os << line.cubies[i] << " ";
		}

		return os;
	}

	Line& operator=(std::vector<char>& colors)
	{
		cubies.resize(3 * sizeof(Cubie));
		for (int i = 0; i < 3; ++i)
		{
			cubies[i] = colors[i];
		}
		return *this;
	}

	Cubie& operator[](size_t i) { return cubies[i]; }

	const Cubie& operator[](size_t i) const { return cubies[i]; }
};

  ////////////////////////////
 //       Facet class      //
////////////////////////////

class Facet 
{
private:
	// stores 3 lines in a vector
	std::vector<Line> lines;  

public:

	friend class Line;

	enum LAYERS { TOP, MID, DOWN };

	Facet() : lines(std::vector<Line>(3)) {}

	Facet(std::vector<char>& colors) { *this = colors; }

	// constructor from a vector of nine colors
	Facet& operator=(const std::vector<char>& colors) 
	{
		lines.resize(3); 
		for (int i = 0; i < 3; ++i)
		{
			lines[i] =  std::vector<char>(colors.begin() + i * 3, colors.begin() + (i + 1) * 3);
		}

		return *this;
	}

	Line& operator[](size_t i) { return lines[i];}

	const Line& operator[](size_t i) const { return lines[i];}

};

  ////////////////////////////
 //       Cube class       //
////////////////////////////

class Cube
{
private:

	// stores a vector of 6 elements (one for each face)
	std::vector<Facet> faces;  

	// private help functions //

	// enum for directions of rotations
	enum DIR{CLOCKWISE = 1, COUNTERCLOCKWISE = -1, DOUBLE = 2};

    // rotates a parametrized face (use "enum FACES") 
    // clockwise (flag=DIR::CLOCKWISE) or counterclockwise(flag=DIR::COUNTERCLOCKWISE)
	void matrix_rot(int face, int flag); 

	// rotates left (FACES::L) or right (FACES::R) face clockwise
	void clockwise_rot_lr(int face); 

	// rotates left (FACES::L) or right (FACES::R) face counterclockwise
	void counter_clockwise_rot_lr(int face); 

	// rotates up (FACES::U) or down (FACES::D) face clockwise
	void clockwise_rot_ud(int face);  

	// rotates up (FACES::U) or down (FACES::D) face counterclockwise
	void counter_clockwise_rot_ud(int face); 

	// rotates front (FACES::F) or back (FACES::B) face clockwise
	void clockwise_rot_fb(int face); 

	// rotates front (FACES::F) or back (FACES::B) face counterclockwise
	void counter_clockwise_rot_fb(int face); 


	// a single method to rotate any face - use "enum FACES"  clockwise - use flag=DIR::CLOCKWISE
	// counterclockwise - use flag=DIR::COUNTERCLOCKWISE 
	// or double - use flag=DIR::DOUBLE from "enum DIR"
	void rotation(int face, int flag); 
	
	// a single method to flip or to change the cube's orientation 
	// using "enum COORDS" as a "coord" and flag=DIR::CLOCKWISE or flag=DIR::COUNTERCLOCKWISE
	void flip(int coord, int flag);    

public:
	friend class Facet;
	Cube() : faces(std::vector<Facet>(6))
	{
		for (int i = 0; i < 6; ++i) 
		{
			std::vector<char> tmp({ char(i), char(i), char(i) });
			for (int j = 0; j < 3; ++j) 
			{
				faces[i][j] = tmp;
			}
		}
	}

	Cube(const std::vector< std::vector<char> >& v) : faces(std::vector<Facet>(6))
	{
		for (int i = 0; i < 6; ++i)
		{
			faces[i] = v[i];

		}
	}

	// input of a cube form istream (loading state)
	friend std::istream & operator>>(std::istream& is, Cube& c);

	// calculating a wrong placed stickers
	int misplaced_stickers() const;

	// displaying a cube in the ostream (saving state)
	friend std::ostream& operator<<(std::ostream& os, const Cube& cube);

	// turns on a "hand-solving" mode (you can manipulate with a cube using keyboard keys)
	void free_mode();

	// a global method converting string of operations given in letter notation to commands and applying them
	// use flag=MODE::SHOW for operations to be shown flag=MODE::HIDE is a default value
	void execute(const std::string& ops, int flag = MODE::HIDE);

	// applies random operations to a cube
	void scramble(int flag =MODE::HIDE);
};
