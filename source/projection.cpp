#include "../header/projection.hpp"

namespace ct
{
  Projection::Projection() noexcept :
  intensity_(std::vector<float>()),
  collums_(0),
  rows_(0),
  angle_(0.0),
  weight_(0.0),
  offset_(std::array<double,2>{0.0,0.0})
  {} 

  Projection::Projection
  (const std::vector<float> & intensity,
   unsigned short collums,unsigned short rows) noexcept:
  intensity_(intensity),
  collums_(collums),
  rows_(rows),
  angle_(0.0),
  weight_(1.0),
  offset_(std::array<double,2>{0.0,0.0})
  {}

  std::array<double,2> Projection::
  project(Point const& p,double distance_center) const noexcept
  {
    double sinus = sin(angle_),cosinus = cos(angle_),u = 0.0,v = 0.0;

    u = distance_center * (-p[0] * sinus + p[1] * cosinus) /
       (distance_center - p[0] * cosinus + p[1] * sinus);

    v = p[2] * distance_center / 
       (distance_center - p[0] * cosinus + p[1] * sinus);

    return std::array<double,2>{u,v};
  }

  float Projection::
  intensity(std::array<double,2> const& det_pos) const noexcept
  {
    return 1.0;
  }

  void Projection::weight(double ldc,double hdc,double dsd) noexcept
  {
    for(unsigned index = 0 ; index < intensity_.size() ; ++index)
    {
      std::array<double,2> pos(detector_position(index,ldc,hdc));
      Vector det_pos(pos[0],pos[1],dsd);

      intensity_[index] *= dsd / det_pos.length();
    }
  }

  void Projection::set_parameter
  (double projection_angle,double uoff,double voff,double weight) noexcept
  {
    angle_  = projection_angle;
    weight_ = weight;
    offset_ = std::array<double,2>{uoff,voff};
  }

	std::array<double,2> const Projection::
  detector_position(unsigned index,double ldc,double hdc) const noexcept
  {
    std::array<unsigned short,2> grid_pos(grid_position(index));
    std::array<double,2> det_pos;

    det_pos[0] = grid_pos[0] - static_cast<double> (collums_) / 2;
    det_pos[1] = grid_pos[1] - static_cast<double> (rows_)    / 2;

    det_pos[0] *= ldc;
    det_pos[1] *= hdc;

    return det_pos;
  }	

  std::array<unsigned short,2> const Projection::
  grid_position(unsigned index) const noexcept
  {
    std::array<unsigned short,2> pos;

    if(collums_ != 0)
    {
      pos[0] = index % collums_;
      pos[1] = index / collums_;
    }

    return pos;
  }
}
