#ifndef CT_EXCEPTION
#define CT_EXCEPTION

#include <exception>
#include <string>

namespace ct
{
  class Exception : public std::exception
  {
    public :

    Exception() noexcept;
    Exception(const std::string & message) noexcept;
    ~Exception() noexcept;

    const char * what() const noexcept;

    private :

    std::string message_;
  };
}


#endif
