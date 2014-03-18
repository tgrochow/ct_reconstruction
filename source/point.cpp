#include "../header/point.hpp"

namespace ct
{
  Point::Point() noexcept :
  data_(std::array<double,4>{0.0,0.0,0.0,1.0})
  {}

  Point::Point(double x,double y,double z) noexcept :
  data_(std::array<double,4>{x,y,z,1.0})
  {}

  void Point::normalize() noexcept
  {
    if(data_[3] != 0.0)

    for(unsigned short index = 0 ; index < 2 ; ++index)
    {
      data_[index] /= data_[3];
    }

    data_[3] = 1.0;
  }

  double & Point::operator [] (unsigned short index) noexcept
  {
    unsigned short last_index = data_.size() - 1;

    if(index > last_index) return data_[last_index]; 

    return data_[index];
  }

  double Point::operator [] (unsigned short index) const noexcept
  {
    unsigned short last_index = data_.size() - 1;

    if(index > last_index) return data_[last_index]; 

    return data_[index];
  }

  void Point::operator += (Vector const& v) noexcept
  {
    for(unsigned short index = 0 ; index < 2 ; ++index)
    {
      data_[index] += v[index];
    }
  }

  void Point::operator -= (Vector const& v) noexcept
  {
    for(unsigned short index = 0 ; index < 2 ; ++index)
    {
      data_[index] -= v[index];
    }
  }

  Point const operator + (Point const& p,Vector const& v) noexcept
  {
    Point p_result(p);
    p_result += v;

    return p_result;
  }

  Point const operator - (Point const& p,Vector const& v) noexcept
  {
    Point p_result(p);
    p_result -= v;

    return p_result;
  }

  Vector const operator - (Point const& p1,Point const& p2) noexcept
  {
    Vector v;

    for(unsigned short index = 0 ; index < 2 ; ++index)
    {
      v[index] = p1[index] - p2[index];
    }

    return v;
  }
}
