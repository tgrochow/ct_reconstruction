#ifndef CT_PROCESSOR
#define CT_PROCESSOR

#include <array>
#include <cmath>
#include <iostream>

#include "./csv_parser.hpp"
#include "./image_processor.hpp"
#include "./support.hpp"

namespace ct
{
  class Processor
  {
    public :

    Processor(std::string const& ct_config) noexcept;
    ~Processor() noexcept;

    void reconstruct(std::string const& proj_config) noexcept;

    private :

    Projection const load_projection
    (std::vector<std::string> const& parameter) noexcept;
    void input_config(std::string const& ct_config) noexcept;
    void valid_config() noexcept;

    std::array<unsigned short,2> panel_dim_;
    std::array<double,2> dist_trajectory_;
    std::array<double,2> det_metrics_;

    bool error_;
    std::string error_message_;
  };
}

#endif
