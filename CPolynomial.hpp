#pragma once
#ifndef CPOLYNOMIAL_HPP_
#define CPOLYNOMIAL_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <exception>
#include <map>
#include <iterator>
#include <complex>
#include <math.h>

class Polynomial 
{
    private:
        std::map<int, double> coeff;
        void fft(std::vector< std::complex<double> > & v, bool invert);
        int deg() const { return (--coeff.end())->first; }
    
    public:
        // Конструкторы от вектора и копирования, оператор присваивания //
        Polynomial() {coeff.clear();}
        Polynomial(const std::vector<double> & v);
        Polynomial(const Polynomial & p); // Конструктор копирования
        Polynomial(const std::map<int, double> & m);
        Polynomial & operator=(const Polynomial & other); // Оператор присваивания
        // Унарные операторы //
        const Polynomial operator-() const;
        // Бинарные логические операторы //
        bool operator==(const Polynomial & other) const; 
        bool operator!=(const Polynomial & other) const { return !(*this).operator==(other); };
        // Бинарный оператор доступа к элементу rvalue //
        double operator[](int i) const;
        // Бинарные математические операторы //
        const Polynomial operator-(const Polynomial & other) const; // Вычитание полинома Polynomial - Polynomial
        const Polynomial operator-(double d) const;                 // Вычитание числа Polynomial - double
        const Polynomial operator+(const Polynomial & other) const; // Прибавление полинома Polynomial + Polynomial
        const Polynomial operator+(double d) const;                 // Прибавление чилса Polynomial + double
        const Polynomial operator*(const Polynomial & other); // Умножение на полином Polynomial * Polynomial
        const Polynomial operator*(double d) const;                 // Умножение на число Polynomial * double
        const Polynomial operator/(double d) const;                 // Деление на число Polynomial / double
        // Операторы присваивания с математической операцией // 
        const Polynomial & operator+=(const Polynomial & other) { return ( (*this) = (*this) + other ); };
        const Polynomial & operator+=(double d) { coeff[0] += d; return (*this); }
        const Polynomial & operator-=(const Polynomial & other) { return ( (*this) = (*this) - other ); };
        const Polynomial & operator-=(double d) { return ( (*this) += -d ); }
        const Polynomial & operator*=(const Polynomial & other) { return ( (*this) = (*this) * other ); };
        const Polynomial & operator*=(double d) { return ( (*this) = (*this) * d ); };
        const Polynomial & operator/=(double d) { return ( (*this) = (*this) / d ); };
        friend std::ostream & operator<<(std::ostream & os, const Polynomial & p);
        friend std::istream & operator>>(std::istream & is, Polynomial & p);

};


#endif