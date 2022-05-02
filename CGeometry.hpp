#pragma once
#ifndef CGEOMETRY_HPP_
#define CGEOMETRY_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <exception>
using std::ios;


//////////////////////////////////////////////
// Класс точки Point
/////////////////////////////////////////////

class Point 
{
    private:
        double x_; // Координаты точки типа double
        double y_;
    public:
        explicit Point(double x = 0, double y = 0); // Конструктор точки от double, double так же конструктор по умолчанию
        Point(const Point& other); // Конструктор копирования
        Point(const std::pair<double, double> & other); // Конструктор от пары значений контейнера std::pair
        Point & operator=(const Point& other); // оператор присваивания объекту точек типа Point
        Point & operator=(const std::pair<double, double> & other); // оператор присваивания объекту пар значений типа double, double
        bool operator==(const Point & other) const; // bool операторы покоординатного сравнения точек
        bool operator!=(const Point & other) const;
        double x() const { return x_; } // Методы доступа к отдельным координатам точек
        double y() const { return y_; }
        double distance(const Point & other) const; // Методы рассчета расстояния от точки типа Point до Point 
        double distance(double x, double y) const;  // до точки плоскости с заданными координатами
        bool is_between(const Point & a, const Point & b) const; // проверка нахождения точки внутри прямоугольной области ограниченной двумя точками
        friend std::ostream & operator<< ( std::ostream & os, const Point & p); // Перегрузка для вывода в поток

};

//////////////////////////////////////////////
// Класс незамкнутой ломаной Polyline
/////////////////////////////////////////////

class Polyline
{
    protected:
        std::vector<Point> vertices_; // Вектор вершин(точек) типа Point
        int size_; // Размер объекта

    
    public:
        Polyline(); // Конструктор по умолчанию
        Polyline(const std::vector<Point> & v); // Конструктор от вектора точек типа Point
        Polyline(const std::vector< std::pair<double, double> > & v); // Конструктор от вектора пар значений типа (double, double)
        Polyline(const Polyline& other); // Конструктор копирования
        Polyline & operator=(const Polyline& other); // Оператор присваивания
        const Point & operator[](int i) const; //  Оператор доступа к вершинам объекта (rvalue only)
        virtual int size() const; // Возвращает количество вершин объекта
        double perimeter() const; // Возвращает периметр
        virtual ~Polyline() {}

};

std::ostream & operator<<( std::ostream & os, const Polyline & p);

/////////////////////////////////////////////////
// Класс замкнутой ломаной ClosedPolyline
////////////////////////////////////////////////

class ClosedPolyline : public Polyline
{   
    public:
        ClosedPolyline();
        ClosedPolyline(const std::vector<Point> & v); // Конструктор от вектора точек типа Point
        ClosedPolyline(const std::vector< std::pair<double, double> > & v); // Конструктор от вектора пар значений типа (double, double)
        ClosedPolyline(const ClosedPolyline& other); // Конструктор копирования
        ClosedPolyline & operator=(const ClosedPolyline& other); // Оператор присваивания
        virtual int size() const; // Возвращает количество вершин объекта
        virtual ~ClosedPolyline() {}
};

/////////////////////////////////////////////////
// Класс многоугольника Polygon
////////////////////////////////////////////////

class Polygon : public ClosedPolyline
{   
    protected:
        double shoelace() const; // Формула Гаусса для рассчета площади многоугольника
        const std::pair<bool, Point> point_intrsc(Point a, Point b, Point c, Point d) const; // служебный метод поиска координат точек самопересечения граней 

    public:
        Polygon();
        Polygon(const std::vector<Point> & v);
        Polygon(const ClosedPolyline & cpl);
        Polygon(const Polygon & other);
        Polygon & operator=(const Polygon & other);
        virtual int size() const; // Возвращает количество вершин объекта
        virtual double area() const; // Площадь 
        virtual ~Polygon() {}


};

/////////////////////////////////////////////////
// Класс треугольника Triangle
////////////////////////////////////////////////

class Triangle : public Polygon 
{   
    public:
        enum Vertex {A, B, C};
        Triangle(Point a, Point b, Point c);
        Triangle(const std::vector<Point> & v);
        Triangle(const Polygon & p);
        Triangle(const Triangle & other);
        const Triangle & operator=(const Triangle & other);
        virtual double area() const; // Площадь 
        virtual ~Triangle() {}
        // friend std::ostream & operator<<( std::ostream & os, const Triangle & p); // Перегрузка вывода в поток
        
};


/////////////////////////////////////////////////
// Класс трапеции Trapezoid
////////////////////////////////////////////////

class Trapezoid : public Polygon
{   
    public:
        enum Vertex {A, B, C, D};
        Trapezoid(Point a, Point b, Point c, Point d);
        Trapezoid(const std::vector<Point> & v);
        Trapezoid(const Polygon & p);
        Trapezoid(const Trapezoid & other);
        const Trapezoid & operator=(const Trapezoid & other);
        virtual double area() const; // Площадь
        virtual ~Trapezoid() {}        
};


/////////////////////////////////////////////////
// Класс правильного многоугольника Regular Polygon
////////////////////////////////////////////////


class RegPolygon : public Polygon
{   
    public:
        RegPolygon(const std::vector<Point> & v);
        RegPolygon(const Polygon & p);
        RegPolygon(const RegPolygon & other);
        const RegPolygon & operator=(const RegPolygon & other);
        virtual double area() const;
        virtual ~RegPolygon() {}        
};

#endif