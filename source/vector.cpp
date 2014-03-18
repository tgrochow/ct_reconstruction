#include "../header/vector.hpp"

namespace ct
{
  Vector::Vector() noexcept :
  data_(std::array<double,4>{0.0,0.0,-1.0,0.0})
  {}

  Vector::Vector(double x,double y,double z) noexcept :
  data_(std::array<double,4>{x,y,z,0.0})
  {}

  void Vector::normalize() noexcept
  {
    double l = length();

    if(l != 0.0)

    for(unsigned short index = 0 ; index < 3 ; ++index)
    {	
      data_[index ] /= l;
    }
  }

  double Vector::length() const noexcept
  {
    return sqrt(pow(data_[0],2) + pow(data_[1],2) + pow(data_[2],2));
  }

  double Vector::operator [] (unsigned short index) const noexcept
  {
    unsigned short last_index = data_.size() - 1;

    if(index > last_index) return data_[last_index]; 

    return data_[index];
  }

  double & Vector::operator [] (unsigned short index) noexcept
  {
    unsigned short last_index = data_.size() - 1;

    if(index > last_index) return data_[last_index]; 

    return data_[index];
  }

  void Vector::operator += (const Vector & v) noexcept
  {
    for(unsigned short index = 0 ; index < 3 ; ++index)
    {	
      data_[index] += v[index];
    }	
  }

  void Vector::operator -= (const Vector & v) noexcept
  {
    for(unsigned short index = 0 ; index < 3 ; ++index)
    {	
      data_[index] -= v[index];
    }	
  }

  void Vector::operator *= (double scalar) noexcept
  {
    for(unsigned short index = 0 ; index < 3 ; ++index)
    {	
      data_[index] *= scalar;
    }	
  }

  Vector const operator + (Vector const& v1,Vector const& v2) noexcept
  {
    Vector v(v1);
    v += v2;

    return v;
  }

  Vector const operator - (Vector const& v1,Vector const& v2) noexcept
  {
    Vector v(v1);
    v -= v2;

    return v;
  }

  Vector const operator * (Vector const& v,double scalar) noexcept
  {
    Vector v_result(v);
    v_result *= scalar;

    return v_result;
  }

  Vector const operator * (double scalar,Vector const& v) noexcept  
  {
    return v * scalar;
  }

  double operator * (Vector const& v1,Vector const& v2) noexcept
  {
    double scalar = 0.0;

    for(unsigned short index = 0 ; index < 3 ; ++index)
    {	
      scalar += v1[index] * v2[index];
    }	

    return scalar;
  }

  Vector const cross(Vector const& v1,Vector const& v2) noexcept
  {
    Vector v_result;

    v_result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    v_result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    v_result[2] = v1[0] * v2[1] - v1[1] * v2[0];

    return v_result;
  }
}
