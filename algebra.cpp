#include "CPolynomial.hpp"
#include <iostream>

int main() 
{   
    Polynomial p(std::vector<double> {1, 2, 3});
    Polynomial p1(std::vector<double> {7, 8, 9});
    Polynomial p2 = p1;
    double x;
    int i = 0;
    std::map<int, double> m;
    Polynomial p3;
    std::cin >> p3;
    double d = 10;
    std::cout << "Defailt empty ctor: " << p2 << std::endl;
    std::cout << "Vector double ctor: " << p << std::endl;
    std::cout << "Using cin >>: " << p3 << std::endl;
    Polynomial p4 = p;
    std::cout << "Copy ctor from: p4 = p: " << p4 << std::endl;
    std::cout << "Showing math operations: " << std::endl;
    std::cout << "operator-(): from Polynomial p " << -p << std::endl;
    std::cout << "operator-(const & Polynomial other): from Polynomial (p - p1): " << p - p1 << std::endl;
    std::cout << "operator-(const & Polynomial other): from Polynomial (p + p1): " << p + p1 << std::endl;
    std::cout << "Please input some double value to use: " << std::endl;
    std::cout << "operator-(double d): from Polynomial (p - d): " << p - d << std::endl;
    std::cout << "operator+(double d): from Polynomial (p + d): " << p + d << std::endl;
    std::cout << "operator*(double d): from Polynomial (p * d): " << p * d << std::endl;
    std::cout << "operator/(double d): from Polynomial (p / d): " << p / d << std::endl;
    std::cout << "before operator+=(double d): from Polynomial (p += d): " << p << std::endl;
    std::cout << "after operator+=(const & Polynomial other): from Polynomial (p += p1): " << (p += p1) << std::endl;
    std::cout << "before operator*=(double d): from Polynomial p2 : " << p2 << std::endl;
    std::cout << "after operator*=(double d): from Polynomial (p2 *= p3): " << (p2 *= p3) << std::endl;
    std::cout << "before operator/=(double d): from Polynomial p4: " << p4 << std::endl;
    std::cout << "after operator/=(double d): from Polynomial (p /= d): " << (p /= d) << std::endl;

    p2 = p * p1; 
    p*= p1;
    std::cout << "P: " << p << std::endl;
    std::cout << "P1: " << p1 << std::endl;
    std::cout << "P2: " << p2 << std::endl;
    return 0;
}