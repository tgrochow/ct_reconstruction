#ifndef CT_VECTOR
#define CT_VECTOR

#include <array>
#include <cmath>

namespace ct
{
  class Vector
  {
    public :

    Vector() noexcept;
    Vector(double x,double y,double z)noexcept;

    double operator [] (unsigned short index) const noexcept;
    double & operator [] (unsigned short index) noexcept;

    void operator += (const Vector & v) noexcept;
    void operator -= (const Vector & v) noexcept;
    void operator *= (double scalar) noexcept;

    void normalize() noexcept;
    double length() const noexcept;

    private :

    std::array<double,4> data_;
  };

  Vector const operator + (const Vector & v1,const Vector & v2) noexcept;
  Vector const operator - (const Vector & v1,const Vector & v2) noexcept;
  Vector const operator * (const Vector & v,double scalar) noexcept;
  Vector const operator * (double scalar,const Vector & v) noexcept;

  double operator * (const Vector & v1,const Vector & v2) noexcept;
  Vector const cross(const Vector & v1,const Vector & v2) noexcept;
}

#endif
