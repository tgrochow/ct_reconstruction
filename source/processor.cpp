#include "../header/processor.hpp"

namespace ct
{
  Processor::Processor(std::string const& ct_config) noexcept :
  error_(false),
  error_message_("")
  {
    input_config(ct_config);
    if(!error_)valid_config();
  }

  Processor::~Processor() noexcept
  {
    if(error_) std::cout << error_message_ << std::endl << std::endl;
  }

  void Processor::reconstruct(std::string const& proj_config) noexcept
  {
    Csv_parser csv;

    if(!error_) try
    {
      csv.parse(proj_config);
    }

    catch(const Exception & e)
    {
      error_ = true;
      error_message_ += e.what();
    }

    if(!error_)
    {
      for(unsigned short index = 0 ; index < csv.line_number() ; ++index)
      {
        std::vector<std::string> line(csv[index]);

        if(line.size() != 6)
        {
          error_ = true;

          error_message_ 

            += std::string("\ninvalid csv line : ")
            +  std::to_string((index + 1))
            +  std::string("\n\nsyntax : <name> <angle> <uoff> <voff>")
            +  std::string("<air_norm> <weight>");

          break;   
        }

        Projection p(load_projection(line));
        if(error_) break;
      }
    }
  }

  Projection const Processor::load_projection
  (std::vector<std::string> const& parameter) noexcept
  {
    Image_processor ip;
    Projection p;

    double angle = 0.0 , uoff = 0.0 , voff = 0.0 , weight = 0.0;

    try
    {
      unsigned long air_norm;

      angle    = convert(parameter[1]);
      uoff     = convert(parameter[2]); 
      voff     = convert(parameter[3]);
      weight   = convert(parameter[5]); 
      air_norm = convert_int(parameter[4]);

      p = ip.read_image(parameter[0],air_norm);
    }

    catch(Exception const& e)
    {
      error_ = true;
      error_message_ += e.what();
    }

    p.set_parameter(angle,uoff,voff,weight);
    
    std::array<double,2> det(p.project(Point(10.0,6.0,0.0),100));

    return p;
  }

  void Processor::input_config(std::string const& ct_config) noexcept
  {
    Csv_parser csv;

    try
    {
      csv.parse(ct_config);
    }

    catch(const Exception & e)
    {
      error_ = true;
      error_message_ += e.what();
    }

    if(!error_ && csv.line_number() == 1 && csv[0].size() == 6)
    {
      try
      {
        dist_trajectory_[0] = convert(csv[0][0]);
        dist_trajectory_[1] = convert(csv[0][1]);
        panel_dim_[0] = static_cast<unsigned short> (convert_int(csv[0][2]));
        panel_dim_[1] = static_cast<unsigned short> (convert_int(csv[0][3]));
        det_metrics_[0] = convert(csv[0][4]);
        det_metrics_[1] = convert(csv[0][5]);
      }

      catch(Exception const& e)
      {
        error_ = true;
        error_message_ += e.what();
      }
    }

    else if(!error_)
    {
      error_ = true;

      error_message_ 

      += std::string("\ninvalid config file\n")
      +  std::string("\n<distance source center> <distance source detector> ")
      +  std::string("<panel width> <panel height> <detector width (cm)> ")
      +  std::string("<detector height (cm)>");
    }
  }

  void Processor::valid_config() noexcept
  {
    if(dist_trajectory_[0] <= 10.0 || dist_trajectory_[0] > 500.0)
    {
      error_ = true;
      error_message_ += "\ninvalid config : distance to rotation center";
    }

    if(dist_trajectory_[1] <= 15.0 || dist_trajectory_[1] > 1000.0)
    {
      error_ = true;
      error_message_ += "\ninvalid config : distance to detector center";
    }

    if(dist_trajectory_[1] <= (dist_trajectory_[0] * 1.1))
    {
      error_ = true;
      error_message_ += "\ninvalid config : ratio dsc - dsd";
    }

    if(panel_dim_[0] < 10   || panel_dim_[0] < 10 ||
       panel_dim_[1] > 1000 || panel_dim_[1] >1000)
    {
      error_ = true;
      error_message_ += "\ninvalid config : panel dimension";
    }

    if(det_metrics_[0] <= 0.0 || det_metrics_[0] > 1.0)
    {
      error_ = true;
      error_message_ += "\ninvalid config : length of one detection cell";
    }

    if(det_metrics_[1] <= 0.0 || det_metrics_[1] > 1.0)
    {
      error_ = true;
      error_message_ += "\ninvalid config : height of one detection cell";
    }
  }
}
