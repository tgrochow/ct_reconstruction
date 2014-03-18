#include "../header/exception.hpp"

namespace ct
{
  Exception::Exception() noexcept :
  message_("unknown error")
  {}

  Exception::Exception(const std::string & message) noexcept :
  message_(message)
  {}

  Exception::~Exception() noexcept
  {}

  const char * Exception::what() const noexcept
  {
    return message_.c_str();
  }
}
