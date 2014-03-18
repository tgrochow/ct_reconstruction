#include "../header/volume.hpp"

namespace ct
{
  Volume::Volume(const std::array<unsigned short,3> & dimension) noexcept :
  dimension_(dimension),
  unit_size_(std::array<double,3>{1.0,1.0,1.0}),
  data_(std::vector<float>(dimension[0]*dimension[1]*dimension[2],0.0))
  {}
  
  Volume::Volume(const std::array<unsigned short,3> & dimension,
                 const std::array<double,3> & unit_size) noexcept :
  dimension_(dimension),
  unit_size_(unit_size),
  data_(std::vector<float>(dimension[0]*dimension[1]*dimension[2],0.0))
  {}
}
