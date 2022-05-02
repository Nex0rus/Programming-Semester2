#include "CGeometry.hpp"
#include <fstream>
int main() 
{   
    Point p1(10, 300);
    std::vector<Point> v1;
    std::vector< std::pair<double, double> > v2;
    for (int i = 0; i < 5; i++) 
    {
        v1.push_back(Point(i, 5 - i));
        v2.push_back(std::pair<double, double>(i + 100, i + 101));
    }
    std::vector<Point> v3 = {Point(1, 10), Point(2, 45), Point(5, 17)};
    std::vector<Point> v4 = {Point(1, 1), Point(5, 1), Point(4, 8), Point(2, 8)};
    std::vector<Point> v5 = {Point(1, 2), Point(6, 7), Point(6, 8), Point(1, 8)};
    int n;
    double x, y;
    // std::ifstream file("test1.txt");
    // file >> n;
    // for (int i = 0; i < n; i++) 
    // {
    //     file >>  x >> y;
    //     v4.push_back(Point(x, y));
    //     v5.push_back(Point());
    // }
    // std::cout << pl2;
    // std::cout << pl1.perimeter() << std::endl;
    // ClosedPolyline cpl1(v4);
    // std::cout << cpl1 << "\n\n\n";
    // Polygon p(v4);
    // std::cout << p.area()<< "\n";

    std::vector<Point> v6 = {Point(1, 2), Point(3, 10), Point(8, 5)};
    Triangle t1(v4);
    Triangle t2(v5);
    // std::cout << t1 << std::endl;
    // // std::cout << t2 << std::endl;
    // t1 = t2;
    // std::cout << t1 << std::endl;
    Trapezoid tr1(v4);
    std::cout << "vector ctor\n" << tr1 << std::endl;
    Trapezoid tr4 = tr1;
    std::cout << "copy ctor\n" << tr4 << std::endl;
    Trapezoid tr2(v5);
    std::cout << "vector ctor\n" << tr2 << std::endl;
    Trapezoid tr3(Point(1, 2), Point(6, 7), Point(6, 8), Point(2, 8));
    std::cout << "point ctor\n" << tr3 << std::endl;
    tr3 = tr4;
    std::cout << "operator= \n" << tr3 << std::endl;

    return 0;
}

