#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <Windows.h>
#include <sstream>
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>

enum COLORS { WHITE, ORANGE, GREEN, RED, BLUE, YELLOW };
enum COORDS { X = 1, Y = 2, Z = 3 };
enum FACES { U, L, F, R, B, D };
enum MODE { HIDE, SHOW };
enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

void setcur(int x, int y);  //установка курсора на позицию  x y

void setColor(unsigned fg);


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

	friend std::ostream& operator<<(std::ostream& os, const Cubie& cubie);

	bool operator!=(const Cubie & other) { return (this->color != other.color); }

};


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


class Facet
{
private:
	std::vector<Line> lines;

public:

	friend class Line;

	enum LAYERS { TOP, MID, DOWN };

	Facet() : lines(std::vector<Line>(3)) {}

	Facet(std::vector<char>& colors) { *this = colors; }

	Facet& operator=(const std::vector<char>& colors)
	{
		lines.resize(3 * sizeof(Line));
		for (int i = 0; i < 3; ++i)
		{
			lines[i] = std::vector<char>(colors.begin() + i * 3, colors.begin() + (i + 1) * 3);
		}

		return *this;
	}

	Line& operator[](size_t i) { return lines[i];}

	const Line& operator[](size_t i) const { return lines[i];}

};


class Cube
{
private:

	std::vector<Facet> faces;

	enum DIR{CLOCKWISE = 1, COUNTERCLOCKWISE = -1};

	void matrix_rot(int face, int flag);

	void clockwise_rot_lr(int face);

	void counter_clockwise_rot_lr(int face);

	void clockwise_rot_ud(int face);

	void counter_clockwise_rot_ud(int face);

	void clockwise_rot_fb(int face);

	void counter_clockwise_rot_fb(int face);

	void rotation(int face, int flag);
	
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

	int misplaced_stickers() const;

	friend std::ostream& operator<<(std::ostream& os, const Cube& cube);

	void free_mod();

	void execute(const std::string& ops, int flag = MODE::HIDE);

};