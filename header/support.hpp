#ifndef CT_SUPPORT
#define CT_SUPPORT

#include <array>
#include <cmath>
#include <complex>
#include <vector>

#include "./exception.hpp"

#define _USE_MATH_DEFINES

namespace ct
{
  double linear_interpolation
  (double x,double x0,double y0,double x1,double y1) noexcept;

  double bilinear_interpolation
  (std::array<double,2> const& grid_pos,std::array<double,4> const& grid,
   std::array<double,4> const& intensity) noexcept;

  std::vector<std::complex<double> > const 
  dft(std::vector<double> const& samples) noexcept;

  std::vector<double> const
  idft(std::vector<std::complex<double> > const& ft) noexcept;

  double convert(std::string const& s) throw(Exception);
  unsigned long convert_int(std::string const& s) throw(Exception);
}

#endif
