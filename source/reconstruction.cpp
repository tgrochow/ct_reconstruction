#include <iostream>

#include "../header/processor.hpp"

int main(int argc,char * argv[])
{
  if(argc != 3)

    std::cout << "\n" << argv[0] << "<ct_config.csv> <projection.csv>\n\n";

  else
  {
    ct::Processor processor(argv[1]);
    processor.reconstruct(argv[2]);
  }

  return 0;
}
