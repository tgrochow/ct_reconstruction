#include "../header/csv_parser.hpp"

namespace ct
{
  Csv_parser::Csv_parser() noexcept :
  path_("./csv/")
  {}

  Csv_parser::Csv_parser(const std::string & path) noexcept :
  path_(path)
  {}

  void Csv_parser::parse(std::string const& name) throw(Exception)
  {
    std::ifstream in;

    in.open(path_+name);

    if(in.is_open() && in.good())
    {
      std::string line;

      while(in.peek() != EOF)
      {
        std::getline(in,line);

        line.erase(remove_if(line.begin(),line.end(),
                   [](char c){return c == ' ' || c == '\t';}),line.end());

        std::vector<std::string> arg;
        int position;

        if((position = line.find(',')) == -1)	arg.push_back(line);

        while((position = line.find(',')) != -1)
        {
          std::string value(line.substr(0,position));
          if(value.size() > 0) arg.push_back(value);
          line.erase(0,position+1);

          if(arg.size() > VALUE_MAXIMUM) 
            throw Exception("\ncsv input error : value maximum");
        }

        if(line.size() > 0) arg.push_back(line);

        argv_.push_back(arg);

        if(argv_.size() > LINE_MAXIMUM) 
          throw Exception("\ncsv input error : line maximum");
      }

      in.close();
    }

    else throw Exception("\ncsv file doesn't exist"); 
  }

  std::vector<std::string> const
  Csv_parser::operator [] (unsigned short line) const throw(Exception)
  {
    if(line > (argv_.size() - 1)) throw(Exception("\ninvalid line index"));

    return argv_[line];
  }

  unsigned short Csv_parser::line_number() const noexcept
  {
    return static_cast<unsigned short> (argv_.size());
  }
}
