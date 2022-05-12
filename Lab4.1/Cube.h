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


void setcur(int x, int y)//установка курсора на позицию  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

enum COLORS { WHITE, ORANGE, GREEN, RED, BLUE, YELLOW };
enum COORDS { X = 1, Y = 2, Z = 3 };
enum FACES { U, L, F, R, B, D };
enum MODE {HIDE, SHOW};
static std::map<std::string, std::pair<int, int> > moves{
	{"U", {FACES::U, 1}}, {"U'", {FACES::U, -1}}, {"u", {FACES::U, -1}}, {"U2", {FACES::U, 2}}, {"I", {FACES::U, 2}},
	{"L", {FACES::L, 1}}, {"L'", {FACES::L, -1}}, {"l", {FACES::L, -1}}, {"L2", {FACES::L, 2}}, {";", {FACES::L, 2}},
	{"R", {FACES::R, 1}}, {"R'", {FACES::R, -1}}, {"r", {FACES::R, -1}}, {"R2", {FACES::R, 2}}, {"T", {FACES::R, 2}},
	{"D", {FACES::D, 1}}, {"D'", {FACES::D, -1}}, {"d", {FACES::D, -1}}, {"D2", {FACES::D, 2}},
	{"F", {FACES::F, 1}}, {"F'", {FACES::F, -1}}, {"f", {FACES::F, -1}}, {"F2", {FACES::F, 2}},
	{"B", {FACES::B, 1}}, {"B'", {FACES::B, -1}}, {"b", {FACES::B, -1}}, {"B2", {FACES::B, 2}}, {"N", {FACES::B, 2}},
	{"X", {X, 1}}, {"X'", {X, -1}}, {"x", {X, -1}}, {"X2", {X, 2}},
	{"Y", {Y, 1}}, {"Y'", {Y, -1}}, {"y", {Y, -1}}, {"Y2", {Y, 2}},
	{"Z", {Z, 1}}, {"Z'", {Z, -1}}, {"z", {Z, -1}}, {"Z2", {Z, 2}}
};

enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
static std::map<int, std::pair<const char*, int>> color_map{
	{WHITE, {"W", LightGray}}, {YELLOW, {"Y", Brown} }, {ORANGE, {"O", LightRed}},
	{RED, {"R", Red}}, {GREEN, {"G", Green}}, {BLUE, {"B", Blue} } 
};

void setColor(unsigned fg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | fg));

}

class Cubie
{
private:
	int color;
	int x;
	int y;
public:
	Cubie& operator=(int color_)
	{
		color = color_;
		x = 0;
		y = 0;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, const Cubie& cubie)
	{
		setColor(color_map[cubie.color].second);
		os << std::string(color_map[cubie.color].first);
		return os;
	}

	bool operator!=(const Cubie & other) 
	{
		return (this->color != other.color);
	}

};


class Line
{
private:
	std::vector<Cubie> cubies;
public:

	Line() : cubies(std::vector<Cubie>(3)) {}


	Line(std::vector<int> colors)
	{
		(*this) = colors;
	}


	friend std::ostream& operator<<(std::ostream& os, const Line& line)
	{
		for (int i = 0; i < 3; ++i)
		{
			os << line.cubies[i] << " ";
		}

		return os;
	}


	Line& operator=(std::vector<int>& colors)
	{
		cubies.resize(3 * sizeof(Cubie));
		for (int i = 0; i < 3; ++i)
		{
			cubies[i] = colors[i];
		}
		return *this;
	}

	Cubie& operator[](size_t i)
	{
		return cubies[i];
	}
	const Cubie& operator[](size_t i) const
	{
		return cubies[i];
	}
};


class Facet
{
private:
	std::vector<Line> lines;
public:
	friend class Line;


	enum LAYERS { TOP, MID, DOWN };


	Facet() : lines(std::vector<Line>(3))
	{
	}


	Facet(std::vector<int>& colors)
	{
		*this = colors;
	}

	//Facet& operator=(Facet & other) 
	//{
	//	std::cout << "YAGOVNO";
	//	for (int i = 0; i < 3; ++i) 
	//	{
	//		std::swap((* this)[i], other[i]);
	//	}
	//	return *this;
	//}

	Facet& operator=(const std::vector<int>& colors)
	{
		lines.resize(3 * sizeof(Line));
		for (int i = 0; i < 3; ++i)
		{
			lines[i] = std::vector<int>(colors.begin() + i * 3, colors.begin() + (i + 1) * 3);
		}

		return *this;
	}


	Line& operator[](size_t i)
	{
		return lines[i];
	}


	const Line& operator[](size_t i) const
	{
		return lines[i];
	}

};

class Cube
{
private:

	int dim;
	std::vector<Facet> faces;
	enum DIR{CLOCKWISE = 1, COUNTERCLOCKWISE = -1};
	void matrix_rot(int face, int flag)
	{
		Facet temp = faces[face];
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (flag == CLOCKWISE) 
				{
					faces[face][j][2 - i] = temp[i][j];
				}
				else 
				{
					faces[face][2 - j][i] = temp[i][j];
				}
			}
		}
	}


	//void matrix_counter_clockwise_rot(int face)
	//{
	//	matrix_clockwise_rot(face);
	//	matrix_clockwise_rot(face);
	//	matrix_clockwise_rot(face);
	//}


	void clockwise_rot_lr(int face)
	{
		int ind = 0;
		if (face == FACES::L)
		{
			ind = 2;
		}

		for (int i = 0; i < 3; ++i) 
		{
			std::swap(faces[FACES::F][i][2 - ind], faces[(face == FACES::L) ? FACES::D : FACES::U][i][2 - ind]);
			std::swap(faces[FACES::F][i][2 - ind], faces[FACES::B][2 - i][ind]);
			std::swap(faces[FACES::F][i][2 - ind], faces[(face == FACES::L) ? FACES::U : FACES::D][i][2 - ind]);

		}
		matrix_rot(face, CLOCKWISE);
	}


	void counter_clockwise_rot_lr(int face) 
	{
		clockwise_rot_lr(face);
		clockwise_rot_lr(face);
		clockwise_rot_lr(face);
	}


	void clockwise_rot_ud(int face)
	{
		int layer;
		if (face == FACES::U) 
		{
			matrix_rot(FACES::U, CLOCKWISE);
			layer = Facet::LAYERS::TOP;
		}
		else 
		{
			matrix_rot(FACES::D, CLOCKWISE);
			layer = Facet::LAYERS::DOWN;
		}

		std::swap(faces[FACES::F][layer], faces[(face == FACES::U) ? FACES::L : FACES::R][layer]);
		std::swap(faces[FACES::F][layer], faces[FACES::B][layer]);
		std::swap(faces[FACES::F][layer], faces[(face == FACES::U) ? FACES::R : FACES::L][layer]);
	}


	void counter_clockwise_rot_ud(int face)
	{
		clockwise_rot_ud(face);
		clockwise_rot_ud(face);
		clockwise_rot_ud(face);
	}


	void clockwise_rot_fb(int face)
	{
		int ind = 0;
		if (face == FACES::B)
		{
			ind = 2;
		}

		for (int i = 0; i < 3; ++i) 
		{
			std::swap(faces[FACES::R][i][ind], faces[(face == FACES::F) ? FACES::D : FACES::U][0][(face == FACES::F) ? 2 - i : i]);
			std::swap(faces[FACES::R][i][ind], faces[FACES::L][2 - i][2 - ind]);
			std::swap(faces[FACES::R][i][ind], faces[(face == FACES::F) ? FACES::U : FACES::D][2][(face == FACES::F) ? i : 2 - i]);

		}

		matrix_rot(face, CLOCKWISE);
	}


	void counter_clockwise_rot_fb(int face) 
	{
		clockwise_rot_fb(face);
		clockwise_rot_fb(face);
		clockwise_rot_fb(face);
	}

	void rotation(int face, int flag) 
	{
		switch(flag) 
		{

		case 1:
			if (face == FACES::U || face == FACES::D) 
			{
				clockwise_rot_ud(face);
			}
			else if (face == FACES::F || face == FACES::B) 
			{
				clockwise_rot_fb(face);
			}
			else if (face == FACES::L || face == FACES::R) 
			{
				clockwise_rot_lr(face);
			}
			break;

		case -1:
			if (face == FACES::U || face == FACES::D)
			{
				counter_clockwise_rot_ud(face);
			}
			else if (face == FACES::F || face == FACES::B)
			{
				counter_clockwise_rot_fb(face);
			}
			else if (face == FACES::L || face == FACES::R)
			{
				counter_clockwise_rot_lr(face);
			}
			break;

		case 2:
			if (face == FACES::U || face == FACES::D)
			{
				clockwise_rot_ud(face);
				clockwise_rot_ud(face);
			}
			else if (face == FACES::F || face == FACES::B)
			{
				clockwise_rot_fb(face);
				clockwise_rot_fb(face);
			}
			else if (face == FACES::L || face == FACES::R)
			{
				clockwise_rot_lr(face);
				clockwise_rot_lr(face);
			}
			break;

		}
	}

	void flip(int coord, int flag) 
	{
		if (coord == COORDS::X) 
		{

			matrix_rot(FACES::R, flag);
			matrix_rot(FACES::L, -flag);
		
			for (int i = 0; i < 3; ++i) 
			{
				for (int j = 0; j < 3; ++j) 
				{
					std::swap(faces[FACES::F][i][j], faces[(flag == 1) ? FACES::U : FACES::D][i][j]);
					std::swap(faces[FACES::F][i][j], faces[FACES::B][2 - i][2 - j]);
					std::swap(faces[FACES::F][i][j], faces[(flag == 1) ? FACES::D : FACES::U][i][j]);
				}
			}

		}

		else if (coord == COORDS::Y) 
		{
			matrix_rot(FACES::U, flag);
			matrix_rot(FACES::D, -flag);

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					std::swap(faces[FACES::F][i][j], faces[(flag == 1) ? FACES::L : FACES::R][i][j]);
					std::swap(faces[FACES::F][i][j], faces[FACES::B][i][j]);
					std::swap(faces[FACES::F][i][j], faces[(flag == 1) ? FACES::R : FACES::L][i][j]);
				}
			}

		}

		else if (coord == COORDS::Z) 
		{
			matrix_rot(FACES::F, flag);
			matrix_rot(FACES::B, -flag);
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					std::swap(faces[FACES::U][i][j], faces[(flag == 1) ? FACES::R : FACES::L][j][2 - i]);
					std::swap(faces[FACES::U][i][j], faces[FACES::D][2 - i][2 - j]);
					std::swap(faces[FACES::U][i][j], faces[(flag == 1) ? FACES::L : FACES::R][2 - j][i]);
				}
			}
		}
		
	}

public:
	friend class Facet;
	Cube() : faces(std::vector<Facet>(6))
	{
		dim = 3;
		for (int i = 0; i < 6; ++i) 
		{
			std::vector tmp({ i, i, i });
			for (int j = 0; j < 3; ++j) 
			{
				faces[i][j] = tmp;
			}
		}
	}
	/*Cube(int dim_)
	{
		dim = dim_;
		faces.resize(6 * sizeof(Facet));
	}*/

	Cube(const std::vector< std::vector<int> >& v) : faces(std::vector<Facet>(6))
	{
		dim = 3;
		for (int i = 0; i < 6; ++i)
		{
			faces[i] = v[i];

		}
	}

	int misplaced_stickers() const
	{
		int misplaced = 0;
		for (int face = 0; face < 6; ++face) 
		{
			Cubie etalon = faces[face][Facet::LAYERS::MID][1];
			for (int line = 0; line < 3; ++line) 
			{
				for (int cubie = 0; cubie < 3; ++cubie) 
				{
					if (etalon != faces[face][line][cubie]) 
					{
						++misplaced;
					}
				}
			}
		}

		return misplaced;
	}

	friend std::ostream& operator<<(std::ostream& os, const Cube& cube)
	{
		setColor(LightGray);
		os << "=============================" << std::endl;

		for (int i = 0; i < 3; ++i)
		{
			os << "\t" << cube.faces[FACES::U][i] << std::endl;
		}
		os << std::endl;
		
		for (int j = 0; j < 3; ++j) 
		{
			for (int i = 1; i < 5; ++i)
			{
				os << cube.faces[i][j] << "  ";
			}
			os << std::endl;
		}
		os << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			os << "\t" << cube.faces[FACES::D][i] << std::endl;
		}
		setColor(LightGray);
		os << "=============================" << std::endl;
		return os;
	}

	void free_mod()
	{
		std::cout << *this;
		char c = '0';
		while (c != 'Q')
		{
			c = _getch();

			if (c == -32)
			{
				c = _getch();
				if (c == 72) // 72 - вверх 75 - вниз 77 - вправо 80 - влево
				{
					break;
				}
			}
			else
			{
				execute(std::string() += c, SHOW);
			}
			//std::cout << (std::string() += c) << std::endl;

			/*setcur(0, 0);
			std::cout << *this;*/


		}
	}

	void execute(const std::string & ops, int flag = MODE::HIDE) 
	{
		std::string res;
		std::stringstream input_s(ops);
		char tmp;
		while (std::getline(input_s, res, ' '))
		{
			tmp = tolower(res[0]);

			if ( tmp == 'x' || tmp == 'y' || tmp == 'z') 
			{
				if (moves[res].second == 2) 
				{
					flip(moves[res].first, CLOCKWISE);
					flip(moves[res].first, CLOCKWISE);
				}
				else 
				{
					flip(moves[res].first, moves[res].second);
				}

			}
			else 
			{
				rotation(moves[res].first, moves[res].second);
			}

			if (flag) 
			{
				setcur(0, 0);
				std::cout << *this;
				std::this_thread::sleep_for(std::chrono::milliseconds(150));
			}

		}
	}



};