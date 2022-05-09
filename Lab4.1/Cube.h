#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <Windows.h>

enum COLORS { WHITE, YELLOW, ORANGE, RED, GREEN, BLUE };

enum ConsoleColor {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
	DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
static std::map<int, std::pair<const char*, int>> color_map{ {WHITE, {"W", LightGray}}, {YELLOW, {"Y", Brown} }, {ORANGE, {"O", LightRed}}, {RED, {"R", Red}}, {GREEN, {"G", Green}}, {BLUE, {"B", Blue} } };

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

};


class Line
{
private:
	std::vector<Cubie> cubies;
public:
	Line()
	{
		cubies.resize(3 * sizeof(Cubie));
	}
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
	Facet()
	{
		lines.resize(3 * sizeof(Line));
	}
	Facet(std::vector<int>& colors)
	{
		*this = colors;
	}

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
	enum FACES { U, L, F, R, B, D };
	std::vector<Facet> faces;


	void matrix_clockwise_rot(int side)
	{
		Facet temp = faces[side];
		for (int i = 0; i < dim; ++i)
		{
			for (int j = 0; j < dim; ++j)
			{
				faces[side][j][dim - 1 - i] = temp[i][j];
			}
		}
	}


	void matrix_counter_clockwise_rot(int side)
	{
		matrix_clockwise_rot(side);
		matrix_clockwise_rot(side);
		matrix_clockwise_rot(side);
	}


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
		matrix_clockwise_rot(face);
	}


	void counter_clockwise_rot_lr(int face) 
	{
		clockwise_rot_lr(face);
		clockwise_rot_lr(face);
		clockwise_rot_lr(face);
	}


	void clockwise_rot_horizontal(int layer)
	{
		std::swap(faces[FACES::F][layer], faces[FACES::L][layer]);
		std::swap(faces[FACES::F][layer], faces[FACES::B][layer]);
		std::swap(faces[FACES::F][layer], faces[FACES::R][layer]);
		if (layer == Facet::LAYERS::TOP)
		{
			matrix_clockwise_rot(FACES::U);
		}
		else
		{
			matrix_counter_clockwise_rot(FACES::D);
		}
	}


	void counter_clockwise_rot_horizontal(int layer)
	{
		clockwise_rot_horizontal(layer);
		clockwise_rot_horizontal(layer);
		clockwise_rot_horizontal(layer);
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
			std::swap(faces[FACES::R][i][ind], faces[(face == FACES::F) ? FACES::U : FACES::D][2 - ind][(face == FACES::F) ? i : 2 - i]);

		}

		matrix_clockwise_rot(face);
	}


	void counter_clockwise_rot_fb(int face) 
	{
		clockwise_rot_fb(face);
		clockwise_rot_fb(face);
		clockwise_rot_fb(face);
	}

public:
	friend class Facet;
	Cube(int dim_)
	{
		dim = dim_;
		faces.resize(6 * sizeof(Facet));
	}
	Cube(const std::vector< std::vector<int> >& v)
	{
		dim = 3;
		faces.resize(6 * sizeof(Facet));
		for (int i = 0; i < 6; ++i)
		{
			faces[i] = v[i];

		}
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


	void clockwise_rot_up() 
	{
		clockwise_rot_horizontal(Facet::LAYERS::TOP);
	}


	void counter_clockwise_rot_up() 
	{
		counter_clockwise_rot_horizontal(Facet::LAYERS::TOP);
	}


	void clockwise_rot_down() 
	{
		clockwise_rot_horizontal(Facet::LAYERS::DOWN);
	}


	void counter_clockwise_rot_down() 
	{
		counter_clockwise_rot_horizontal(Facet::LAYERS::DOWN);
	}


	void clockwise_rot_left()
	{
		clockwise_rot_lr(FACES::L);
	}


	void counter_clockwise_rot_left() 
	{
		counter_clockwise_rot_lr(FACES::L);
	}


	void clockwise_rot_right() 
	{
		clockwise_rot_lr(FACES::R);
	}


	void counter_clockwise_rot_right()
	{
		counter_clockwise_rot_lr(FACES::R);
	}


	void clockwise_rot_front() 
	{
		clockwise_rot_fb(FACES::F);
	}


	void counter_clockwise_rot_front() 
	{
		counter_clockwise_rot_fb(FACES::F);
	}


	void clockwise_rot_back() 
	{
		clockwise_rot_fb(FACES::B);
	}


	void counter_clockwise_rot_back() 
	{
		counter_clockwise_rot_fb(FACES::B);
	}



};