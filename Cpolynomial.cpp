#include "CPolynomial.hpp"

Polynomial::Polynomial(const std::vector<double> & v) 
{
    for (int deg = 0; deg < v.size(); deg++) 
    {   
        if (v[deg] != 0) 
        {
            coeff[deg] = v[deg];
        }
    }
}


Polynomial::Polynomial(const std::map<int, double> & m) 
{
    coeff = m;
}


Polynomial::Polynomial(const Polynomial & p) : Polynomial(p.coeff) {}


Polynomial & Polynomial::operator=(const Polynomial & other) 
{
    if (this != &other) 
    {
        this->coeff = other.coeff;
    }

    return (*this);
}


const Polynomial Polynomial::operator-() const 
{   
    
    std::map<int, double> copy = this->coeff; 
    for (auto it = copy.begin(); it != copy.end(); it++) 
    {   
        it->second = -it->second;
    }
    Polynomial res(copy);
    return res;
}


bool Polynomial::operator==(const Polynomial & other) const 
{
    if (coeff.size() != other.coeff.size()) 
    {
        return false;
    }

    for (auto it1 = coeff.begin(), it2 = other.coeff.begin(); it1 != coeff.end(); it1++, it2++) 
    {
        if ( it1->first != it2->first || it1->second != it2->second ) 
        {
            return false;
        }
    }

    return true;
}


double Polynomial::operator[](int i) const
{   

    auto it = coeff.find(i);

    if (it != coeff.end()) 
    {
        return it->second;
    }

    else 
    {
        return 0;
    }
}

const Polynomial Polynomial::operator-(const Polynomial & other) const
{   
    std::map<int, double> copy = this->coeff; 
    for (auto other_it = other.coeff.begin(); other_it != other.coeff.end(); other_it++) 
    {
        copy[other_it->first] -= other_it->second;
    }

    return Polynomial(copy);
}

const Polynomial Polynomial::operator-(double d) const
{   
    Polynomial temp(std::vector<double> {d});
    return (*this) - temp;
}

const Polynomial Polynomial::operator+(const Polynomial & other) const
{   

    return (*this) - -other;
}


const Polynomial Polynomial::operator+(double d) const
{
    Polynomial temp(std::vector<double> {d});
    return (*this) + temp;
}


const Polynomial Polynomial::operator*(double d) const
{
    std::map<int, double> copy = this->coeff;
    for (auto it = copy.begin(); it != copy.end(); it++) 
    {
        it->second = it->second * d;
    }

    return Polynomial(copy);
}

void Polynomial::fft(std::vector< std::complex<double> > & v, bool invert) 
{
    int n = v.size();
    if (n == 1) // если в результате рекурсии дошли до одноэлементного вектора, то ничего делать не нужно
    {
        return;
    }
    std::vector< std::complex<double> > a0 (n / 2), a1(n / 2); // два вектора комплексных чисел по n/2 элементов в каждом( чередующиеся по четности коэффициенты)
    for (int i = 0, j = 0; i < n; i+=2, j++) 
    {
        a0[j] = v[i];
        a1[j] = v[i + 1];
    }
    fft(a0, invert); // рекурсивно делим вектора коэффициентов до минимальной длины
    fft(a1, invert);
    
    double angle = 2*M_PI/n * (invert ? -1 : 1); // рассчитывается угол поворота между комплексными корнями из единицы в системе полярных координат
    std::complex<double> omega (1), omega_n(cos(angle), sin(angle));
    for (int i = 0; i < n/2; i++) 
    {
        v[i] = a0[i] + omega * a1[i]; // Преобразование бабочки для рассчета корней (следует из свойства комплексных корней из 1)
        v[i + n/2] = a0[i] - omega * a1[i];
        if (invert) 
        {
            v[i] /= 2; // При обратном приобразовании фурье корни в точках соотвествующие коэффициентам делятся на n чтобы получить сами коэффициенты
            v[i + n/2] /= 2; // рекурсия работает log2_n раз, тогда поделив в каждом шаге рекурсии на 2, получим деление на n.
        }

        omega *= omega_n; // Получаем следующую точку в полярных координатах, для которой необходимо рассчитать значение корня (к комплексных числах 
                          // точки будут совпадать при прохождении полного круга вокруг центра полярных координат (периодически с периодом n))
    }
}

const Polynomial Polynomial::operator*(const Polynomial & other) 
{
    int n = 1;
    int coeffs = deg() > other.deg() ? deg() : other.deg();
    coeffs++;
    while (coeffs != 0) 
    {   
        n *= 2;
        coeffs /= 2;
    }
    n*= 2;

    std::vector< std::complex<double> > p1(n), p2(n);
    for (int i = 0; i < n; i++) 
    {
        p1[i] = (*this)[i];
        p2[i] = other[i];
    }

    fft(p1, false);
    fft(p2, false);
    for (int i = 0; i < n; i++) 
    {
        p1[i] *= p2[i];
    }

    fft(p1, true);

    std::map<int, double> res;
    for (int i = 0; i < n; i++) 
    {
        if (p1[i].real() < -1e-16 || p1[i].real() > 1e-16) 
        {
            res[i] = p1[i].real();
        }
    }

    return Polynomial(res);
}

const Polynomial Polynomial::operator/(double d) const
{   
    return (*this)*(1/d);
}     




std::ostream & operator<<( std::ostream & os, const Polynomial & p) 
{
    for (auto it = p.coeff.begin(); it != p.coeff.end(); it++) 
    {
        if (it->first == 0) 
        {
            os << it->second;
        } 
        else 
        {   
            if (it->second != 0) 
            {
            os << ( ((*it).second > 0) ? " + " : " - " ) << abs((*it).second) << "x^" << (*it).first;
            }
            else 
            {
                os << "";
            }
        }
    }

    return os;
}

std::istream & operator>>(std::istream& is, Polynomial & p) {
    std::map<int, double> map;
    double x;
    int i = 0;
    while (is >> x) 
    {   
        if (x != 0) 
        {
            map[i] = x;
        }
        i++;
    }

    p = Polynomial(map);
    return is;

}