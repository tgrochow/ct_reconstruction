#ifndef CT_PROJECTION
#define CT_PROJECTION

#include <vector>

#include "point.hpp"

namespace ct
{
  class Projection
  {
    public :

    Projection() noexcept;
    Projection(const std::vector<float> & intensity,
               unsigned short collums,unsigned short rows) noexcept;

    std::array<double,2> project
    (Point const& p,double distance_center) const noexcept;

    float intensity(std::array<double,2> const& det_pos) const noexcept;

    void weight(double ldc,double hdc,double dsd) noexcept;

    void set_parameter
    (double projection_angle,double weight = 0.0,
     double uoff = 1.0,double voff = 1.0) noexcept;

    private :

    std::array<double,2> const
    detector_position(unsigned index,double ldc,double hdc) const noexcept;

    std::array<unsigned short,2> const
    grid_position(unsigned index) const noexcept;

    std::vector<float> intensity_;
    unsigned short collums_;
    unsigned short rows_;

    double angle_,weight_;
    std::array<double,2> offset_;
  };
}

#endif
