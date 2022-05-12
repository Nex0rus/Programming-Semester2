#include "Cube.h"

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


static std::map<int, std::pair<const char*, int>> color_map{
	{WHITE, {"W", LightGray}}, {YELLOW, {"Y", Brown} }, {ORANGE, {"O", LightRed}},
	{RED, {"R", Red}}, {GREEN, {"G", Green}}, {BLUE, {"B", Blue} }
};


void setColor(unsigned fg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | fg));

}


void setcur(int x, int y) //��������� ������� �� �������  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

std::ostream& operator<<(std::ostream& os, const Cubie& cubie)
{
	setColor(color_map[cubie.color].second);
	os << std::string(color_map[cubie.color].first);
	return os;
}

void Cube::matrix_rot(int face, int flag)
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


void Cube::clockwise_rot_lr(int face)
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


void Cube::counter_clockwise_rot_lr(int face)
{
	clockwise_rot_lr(face);
	clockwise_rot_lr(face);
	clockwise_rot_lr(face);
}


void Cube::clockwise_rot_ud(int face)
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


void Cube::counter_clockwise_rot_ud(int face)
{
	clockwise_rot_ud(face);
	clockwise_rot_ud(face);
	clockwise_rot_ud(face);
}


void Cube::clockwise_rot_fb(int face)
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


void Cube::counter_clockwise_rot_fb(int face)
{
	clockwise_rot_fb(face);
	clockwise_rot_fb(face);
	clockwise_rot_fb(face);
}


void Cube::rotation(int face, int flag)
{
	switch (flag)
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


void Cube::flip(int coord, int flag)
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


int Cube::misplaced_stickers() const
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


std::ostream& operator<<(std::ostream& os, const Cube& cube)
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


void Cube::free_mod()
{
	std::cout << *this;
	char c = '0';
	while (c != 'Q')
	{
		c = _getch();

		if (c == -32)
		{
			c = _getch();
			if (c == 72) // 72 - ����� 75 - ���� 77 - ������ 80 - �����
			{
				break;
			}
		}
		else
		{
			execute(std::string() += c, SHOW);
		}
	}
}


void Cube::execute(const std::string& ops, int flag)
{
	std::string res;
	std::stringstream input_s(ops);
	char tmp;
	while (std::getline(input_s, res, ' '))
	{
		tmp = tolower(res[0]);

		if (tmp == 'x' || tmp == 'y' || tmp == 'z')
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