#ifndef CT_CSV_PARSER
#define CT_CSV_PARSER

#include <algorithm>
#include <fstream>
#include <vector>

#include "./exception.hpp"

#define VALUE_MAXIMUM 25
#define LINE_MAXIMUM 1000

namespace ct
{
  class Csv_parser
  {
    public :

    Csv_parser() noexcept;
    Csv_parser(const std::string & path) noexcept;

    void parse(std::string const& name) throw(Exception);

    std::vector<std::string> const
    operator [] (unsigned short line) const throw(Exception);

    unsigned short line_number() const noexcept;

    private :

    std::vector<std::vector<std::string> > argv_;
    std::string path_;
  };
}

#endif
