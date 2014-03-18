#ifndef CT_VOLUME
#define CT_VOLUME

#include <array>
#include <vector>

namespace ct
{
  class Volume
  {
    public :

    Volume(const std::array<unsigned short,3> & dimension) noexcept;
    Volume(const std::array<unsigned short,3> & dimension,
           const std::array<double,3> & unit_size) noexcept;

    private :

    std::array<unsigned short,3> dimension_;
    std::array<double,3> unit_size_;
    std::vector<float> data_;
  };
}

#endif
