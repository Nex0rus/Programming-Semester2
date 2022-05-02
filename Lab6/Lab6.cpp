// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "polynom_value.h"
int main()
{
	static_assert(polynom_value<2, 2, 3, 4, 5, 6>::value_v == 160);
	polynom_value<4, 5, 6, 7, 8, 10, 1, 7> p2;
	static_assert(p2.value_v == 32909);
	static const int x = 10;
	/*auto p3 = sum(p, p2);*/
	return 1;
}

