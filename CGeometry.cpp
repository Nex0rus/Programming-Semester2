#include "CGeometry.hpp"
#include <typeinfo>


/////////////////////////////
// Методы класса точки Point
////////////////////////////


Point::Point(double x, double y) : x_(x), y_(y) {}


Point::Point(const std::pair<double, double> & other) : x_(other.first), y_(other.second) {}


Point::Point(const Point& other) : x_(other.x_), y_(other.y_) {}


Point & Point::operator=(const Point& other) 
{
    if (this != &other) {
        x_ = other.x_;
        y_ = other.y_;
        return *this;
    }

    else {
        return *this;
    }
}


Point & Point::operator=(const std::pair<double, double> & other) {
    x_ = other.first;
    y_ = other.second;
    return *this;
}


std::ostream & operator<< ( std::ostream & os, const Point & p) {
    os.setf(ios::fixed);
    os.precision(4);
    os << "x: " << p.x_ << ", y: " << p.y_ << " ";
    return os;
}


bool Point::operator==(const Point & other) const 
{
    return x_ == other.x_ && y_ == other.y_;
}


bool Point::operator!=(const Point & other) const 
{
    return x_ != other.x_ || y_ != other.y_;
}


double Point::distance(const Point & other) const
{
    double distance = sqrt( (x_ - other.x_) * (x_ - other.x_) + (y_ - other.y_) * (y_ - other.y_) );
    return distance;
}


double Point::distance(double x, double y) const
{
    Point temp(x, y);
    return distance(temp);
}


bool Point::is_between(const Point & a, const Point & b) const { // проверка на то что точка находится внутри прямоугольника ограниченного двумя точами
    return ( (x_ >= std::min(a.x_, b.x_) && x_ <= std::max(a.x_, b.x_) ) && ( y_ >= std::min(a.y_, b.y_) && y_ <= std::max(a.y_, b.y_) ) );
}

//////////////////////////////////////////////
// Методы класса незамкнутой ломаной Polyline
/////////////////////////////////////////////

std::ostream & operator<<( std::ostream & os, const Polyline & p) // Перегрузка для вывода в поток с использованием динамического полиморфизма
{
    std::string st = typeid(p).name();
    st.erase(0, 1);
    os.setf(ios::fixed);  // вывод в фиксированном формате 
    os.precision(4);
    os << st << " of " << p.size() << " vertices:" << std::endl;
    for (int i = 0; i < p.size(); i++) 
    {
        os << i + 1 << " vertex( " << p[i] << ")" << std::endl;
    }

    return os;   
}


Polyline::Polyline()
{
    size_ = 0;
    vertices_.clear();
}


Polyline::Polyline(const std::vector<Point> & v)
{
    vertices_ = v;
    size_ = v.size();
}


Polyline::Polyline(const std::vector< std::pair<double, double> > & v)
{   
    for (int i = 0; i < v.size(); i++) 
    {
        vertices_.push_back(v[i]);
    }
    size_ = v.size();

}


Polyline::Polyline(const Polyline& other) : vertices_(other.vertices_), size_(other.size_) {}


Polyline & Polyline::operator=(const Polyline& other) 
{
    if (this != &other) {
        size_ = other.size_;
        vertices_ = other.vertices_;
        return *this;
    }
    else 
    {
        return *this;
    }
}


const Point & Polyline::operator[](int i) const
{   
    if (i < size()) 
    {
        return this->vertices_.at(i); // автоматически генерирует std::out_of_range exception при выходе за границы массива точек
    }

    else 
    {
        throw std::out_of_range("Невозможно обратиться к данной вершине, так как ее нет в исходной фигуре");
    }
}


int Polyline::size() const 
{
    return size_;
}


double Polyline::perimeter() const{
    double perimeter = 0;
    for (int i = 1; i < size_; i++) {
        perimeter += vertices_[i].distance(vertices_[i - 1]);
    }
    
    return perimeter;
}

/////////////////////////////////////////////////
// Методы класса замкнутой ломаной ClosedPolyline
////////////////////////////////////////////////

ClosedPolyline::ClosedPolyline() : Polyline() {}


ClosedPolyline::ClosedPolyline(const std::vector<Point> & v) : Polyline(v)
{   
    if ( vertices_[0] != vertices_[size_]) 
    {
        vertices_.push_back(v[0]);
        size_ += 1;
    }
}


ClosedPolyline::ClosedPolyline(const std::vector< std::pair<double, double> > & v) : Polyline(v) 
{
    if ( vertices_[0] != vertices_[size_] ) 
    {
        vertices_.push_back(v[0]);
        size_ += 1;
    }
}


ClosedPolyline::ClosedPolyline(const ClosedPolyline& other) : Polyline(other) {}


ClosedPolyline & ClosedPolyline::operator=(const ClosedPolyline& other) 
{   
    if (this != & other) 
    {
        vertices_ = other.vertices_;
        size_ = other.size_;
    }

    return *this;
}


int ClosedPolyline::size() const 
{   
    return Polyline::size() - 1;
}


/////////////////////////////////////////////////
// Методы класса многоугольника Polygon
////////////////////////////////////////////////

Polygon::Polygon() : ClosedPolyline() {}


Polygon::Polygon(const std::vector<Point> & v) : ClosedPolyline(v) {}


Polygon::Polygon(const ClosedPolyline & cpl) : ClosedPolyline(cpl) {}


Polygon::Polygon(const Polygon & other) : ClosedPolyline(other.vertices_) {}


Polygon & Polygon::operator=(const Polygon & other) 
{
    if (this != &other) 
    {
        vertices_ = other.vertices_;
        size_ = other.size_;
    }

    return *this;

}


int Polygon::size() const
{
    return ClosedPolyline::size();
}


const std::pair<bool, Point> Polygon::point_intrsc(Point a, Point b, Point c, Point d) const
{   
    Point ab( b.x() - a.x(), b.y() - a.y() );
    Point cd( d.x() - c.x(), d.y() - c.y() );
    Point n1( -ab.y(), ab.x() );
    Point n2( -cd.y(), cd.x() );
    double c1 = -n1.x() * a.x() - n1.y() * a.y();
    double c2 = -n2.x() * c.x() - n2.y() * c.y();
    double determinator = ( n1.x() * n2.y() ) - ( n1.y() * n2.x() );
    std::pair<bool, Point> result;
    result.first = false;
    result.second = Point(0, 0);

    if (determinator != 0)
    {
        double x = -(c1 * n2.y() - n1.y() * c2) / determinator;
        double y = -(n1.x() * c2 - c1 * n2.x()) / determinator;
        Point intersection(x, y);
        if ( intersection.is_between(a, b) && intersection.is_between(c, d) && intersection != a && intersection != b 
        && intersection != c && intersection != d) {
            result.first = true;
            result.second = intersection;
        }
    }


    return result;
}


double Polygon::shoelace() const 
{       
    double result = 0;
    for (int i = 0; i < size() - 1; i++) 
    {
        result += ( vertices_[i].x() * vertices_[i + 1].y() ) - ( vertices_[i].y() * vertices_[i + 1].x() );
    }
    result += ( vertices_[size() - 1].x() * vertices_[0].y() ) - ( vertices_[size() - 1].y() * vertices_[0].x() );
    return abs(result / 2);
}


double Polygon::area() const
{   
    std::pair<bool, Point> intersection;
    std::vector<Point> pol1;
    std::vector<Point> pol2;
    for (int i = 0; i < size_- 3; i++) 
    {
        for (int j = i + 2; j <= size_ - 2; j++) 
        {   
            intersection = point_intrsc(vertices_[i], vertices_[i + 1], vertices_[j], vertices_[j + 1]);
            if (intersection.first) 
            {   
                int k = i + 1;
                pol1.push_back(intersection.second);
                while (k <= j) 
                {   
                    pol1.push_back(vertices_[k]);
                    k++;
                }
                pol2.push_back(intersection.second);
                int l = j + 1;
                do
                {   
                    pol2.push_back(vertices_[l % (size_ - 1)]);
                    l++;
                }while (l % size_ != i);

                Polygon plg1(pol1);
                Polygon plg2(pol2);

                return plg1.area() + plg2.area();
            }
        }
    }

    return shoelace();
}

/////////////////////////////////////////////////
// Методы класса треугольника Triangle
////////////////////////////////////////////////

Triangle::Triangle(Point a, Point b, Point c) : Polygon( std::vector<Point> {a, b, c} ) {}


Triangle::Triangle(const Polygon & p) : Triangle(p[0], p[1], p[2]) 
{
    if (p.size() > 3) 
    {
        throw std::length_error("Failed to create a triangle with more than 3 points");
    }
}


Triangle::Triangle(const std::vector<Point> & v) : Triangle( Polygon( std::vector<Point> {v[0], v[1], v[2]} ) ) {}


Triangle::Triangle(const Triangle & other) : Polygon(other.vertices_) {}


const Triangle & Triangle::operator=(const Triangle & other) 
{
    if (this != &other) 
    {
        (*this).Polygon::operator=(other);
    }

    return *this;
}

double Triangle::area() const {
    return shoelace();
} 

/////////////////////////////////////////////////
// Методы класса трапеции Trapezoid
////////////////////////////////////////////////

Trapezoid::Trapezoid(Point a, Point b, Point c, Point d) : Polygon(std::vector<Point> {a, b, c, d}) 
{
    double ab_distance = a.distance(b);
    double bc_distance = b.distance(c);
    double cd_distance = c.distance(d);
    double ad_distance = a.distance(d);
    Point ab(b.x() - a.x(), b.y() - a.y());
    Point bc(c.x() - b.x(), c.y() - b.y());
    Point cd(d.x() - c.x(), d.y() - c.y());
    Point ad(d.x() - a.x(), d.y() - a.y());
    if (  ( abs( ( ab.x() * cd.x() + ab.y() * cd.y() )/(ab_distance*cd_distance) ) != 1 &&
        abs( ( bc.x() * ad.x() + bc.y() * ad.y() )/(ad_distance*bc_distance) ) != 1 ) || 
        (point_intrsc(a, b, c, d).first || point_intrsc(b, c, a, d).first) ) 
    {
        throw std::invalid_argument("Failed to create trapezoid, (lines are not parallel or intersects)");
    }

}

Trapezoid::Trapezoid(const Polygon & p) : Trapezoid(p[0], p[1], p[2], p[3]) 
{
    if (p.size() > 4) 
    {
        throw std::length_error("Failed to create a trapezoid with more than 4 points");
    }
}


Trapezoid::Trapezoid(const std::vector<Point> & v) : Trapezoid( Polygon( std::vector<Point> {v[0], v[1], v[2], v[3]} ) ) {}


Trapezoid::Trapezoid(const Trapezoid & other) : Trapezoid(other.vertices_) {}


const Trapezoid & Trapezoid::operator=(const Trapezoid & other) 
{   

    if (this != &other) 
    {
        (*this).Polygon::operator=(other);
    }

    return *this;
}


double Trapezoid::area() const 
{
    return shoelace();
}

/////////////////////////////////////////////////
// Класс правильного многоугольника Regular Polygon
////////////////////////////////////////////////

RegPolygon::RegPolygon(const Polygon & p) : Polygon(p)
{   

    double cos = -2;
    double tmp = 0;
    for (int i = 0; i < vertices_.size(); i++) 
    {   
        Point a = vertices_[i];
        Point b = vertices_[(i + 1) % (vertices_.size() - 1)];
        Point c = vertices_[(i + 2) % (vertices_.size() - 1)];
        Point ab(b.x() - a.x(), b.y() - a.y());
        Point bc(c.x() - b.x(), c.y() - b.y());
        double ab_distance = a.distance(b);
        double bc_distance = b.distance(c);
        tmp = ( (ab.x() * bc.x() + ab.y() * bc.y())/(ab_distance * bc_distance) );
        if (cos == -2) 
        {
            cos = tmp;
        }
        if (cos != tmp || ab_distance != bc_distance) 
        {
            throw std::invalid_argument("Failed to create Regular Polygon (rather the distances between some points or the angles between some lines are not equal)");
        }
    }
}

RegPolygon::RegPolygon(const std::vector<Point> & v) : RegPolygon(Polygon(v)) {}


RegPolygon::RegPolygon(const RegPolygon & other) : RegPolygon(other.vertices_) {}


const RegPolygon & RegPolygon::operator=(const RegPolygon & other) 
{
    if (this != & other) 
    {
        (*this).Polygon::operator=(other);
    }

    return *this;
}


double RegPolygon::area() const
{
    return shoelace();
}

