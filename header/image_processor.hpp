#ifndef CT_IMAGE_PROCESSOR
#define CT_IMAGE_PROCESSOR

#include <cmath>
#include <vector>

#include <tiffio.h>

#include "./exception.hpp"
#include "./projection.hpp"

#define UI8_MAX 255
#define UI16_MAX 65535

namespace ct
{
  class Image_processor
  {
    public :

    Image_processor() noexcept;
    Image_processor(const std::string & path) noexcept;
    ~Image_processor() noexcept;

    Projection const read_image
    (const std::string & name,unsigned long threshold = 0) throw(Exception);

    private :

    Projection const read_tiff
    (const std::string & name,unsigned long threshold) throw(Exception);

    std::vector<float> const 
    process_buffer(unsigned long threshold) throw(Exception);
    void delete_buffer() noexcept;

    void * buffer_;
    unsigned buffer_count_;
    unsigned short channel_number_,channel_size_;
    std::string path_;
  };
}

#endif
