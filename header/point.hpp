#ifndef CT_POINT
#define CT_POINT

#include "./vector.hpp"

namespace ct
{
  class Point
  {
    public :

    Point() noexcept;
    Point(double x,double y,double z) noexcept;

    void normalize() noexcept;

    double & operator [] (unsigned short index) noexcept;
    double operator [] (unsigned short index) const noexcept;

    void operator += (Vector const& v) noexcept;
    void operator -= (Vector const& v) noexcept;

    private :

    std::array<double,4> data_;
  };

  Point const operator + (Point const& p,Vector const& v) noexcept;
  Point const operator - (Point const& p,Vector const& v) noexcept;

  Vector const operator - (Point const& p1,Point const& p2) noexcept;
}

#endif
