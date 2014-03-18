#include "../header/support.hpp"

namespace ct
{
  double linear_interpolation
  (double x,double x0,double y0,double x1,double y1) noexcept
  {
    if(x1 - x0 == 0.0) return y0;

    return y0 + (y1 - y0) * (x - x0) / (x1 - x0);
  }

  double bilinear_interpolation
  (std::array<double,2> const& grid_pos,std::array<double,4> const& grid,
   std::array<double,4> const& intensity) noexcept
  {
    double i0,i1;

    i0 = 

    linear_interpolation(grid_pos[0],grid[0],intensity[0],grid[2],intensity[1]);

    i1 =

    linear_interpolation(grid_pos[0],grid[0],intensity[2],grid[2],intensity[3]);

    return linear_interpolation(grid_pos[1],grid[1],i0,grid[3],i1);
  }

  std::vector<std::complex<double> > const 
  dft(std::vector<double> const& samples) noexcept
  {
    unsigned short sequence = samples.size();
    std::vector<std::complex<double> > ft(sequence);

    for(unsigned short i = 0 ; i < sequence ; ++i)
    {
      double real = 0.0 , imag = 0.0;

      for(unsigned short j = 0 ; j < sequence ; ++j)
      {
        double phase = 2 * i * j * M_PI / sequence;
        
        real += samples[j] * cos(phase);
        imag += -samples[j] * sin(phase);
      }

      ft[i].real(real);
      ft[i].imag(imag);
    }

    return ft;
  }

  std::vector<double> const
  idft(std::vector<std::complex<double> > const& ft) noexcept
  {
    unsigned short sequence = ft.size();
    std::vector<double> samples(sequence);

    for(unsigned short i = 0 ; i < sequence ; ++i)
    {
      std::complex<double> sum(0.0,0.0);

      for(unsigned short j = 0 ; j < sequence ; ++j)
      {
        double phase = 2 * i * j * M_PI / sequence;

        sum += ft[j] * std::complex<double>(cos(phase),sin(phase));
      }

      samples[i] = sum.real() / sequence;
    }
    
    return samples;
  }

  double convert(std::string const& s) throw(Exception)
  {
    double d;

    try
    {
      d = std::stod(s);
    }

    catch(std::invalid_argument const& ia)
    {
      throw(Exception("\ninvalid argument : " + s));
    }

    catch(std::out_of_range const& oor)
    {
      throw(Exception("\nout of range : " + s));
    }

    return d;
  }

  unsigned long convert_int(std::string const& s) throw(Exception)
  {
    unsigned long i;

    try
    {
      i = std::stoul(s);
    }

    catch(std::invalid_argument const& ia)
    {
      throw(Exception("\ninvalid argument : " + s));
    }

    catch(std::out_of_range const& oor)
    {
      throw(Exception("\nout of range : " + s));
    }

    return i;
  }
}
