#include "../header/image_processor.hpp"

namespace ct
{
  Image_processor::Image_processor() noexcept :
  buffer_(nullptr),
  buffer_count_(0),
  channel_number_(0),
  channel_size_(0),
  path_("./projection/")
  {}

  Image_processor::Image_processor(const std::string & path) noexcept :
  buffer_(nullptr),
  buffer_count_(0),
  channel_number_(0),
  channel_size_(0),
  path_(path)
  {}

  Image_processor::~Image_processor() noexcept
  {
    delete_buffer();
  }

  Projection const Image_processor::
  read_image(const std::string & name,unsigned long threshold) throw(Exception)
  {
    int index_extension = name.rfind('.');

    if(index_extension == -1) 

      throw(Exception
      ("\nimage processing error : no file extension -> "+name));

    std::string extension(name.substr((index_extension + 1),(name.size() - 1)));

    if(extension == "tiff" || extension == "tif")

      return read_tiff(name,threshold);

    else
    
      throw(Exception
      ("\nimage processing error : unknown file extension -> "+extension));
  }

  Projection const Image_processor::
  read_tiff(const std::string & name,unsigned long threshold) throw(Exception)
  {
    uint16 width,height;
    std::vector<float> data;

    TIFF* tiff = TIFFOpen((path_+name).c_str(),"r");

    if(tiff)
    {
      const unsigned short information_number = 4;
      unsigned short field = TIFFGetField(tiff,TIFFTAG_IMAGEWIDTH,&width);
      field += TIFFGetField(tiff,TIFFTAG_IMAGELENGTH,&height);
      field += TIFFGetField(tiff,TIFFTAG_SAMPLESPERPIXEL,&channel_number_);
      field += TIFFGetField(tiff,TIFFTAG_BITSPERSAMPLE,&channel_size_);

      if(field != information_number)
      
        throw(Exception
        ("image processing error : missing image information ->" + name));

      auto line_size = TIFFScanlineSize(tiff);
      buffer_ = _TIFFmalloc(line_size);
      buffer_count_ = width;

      for(uint16 row = 0 ; row < height ; ++row)
      {
        if(TIFFReadScanline(tiff,buffer_,row) == -1) 
        
          throw(Exception
          ("\nimage processing error : unknown compression scheme ->" + name));

        std::vector<float> row_data(process_buffer(threshold));
        data.insert(data.end(),row_data.begin(),row_data.end());
      }

      delete_buffer();
      TIFFClose(tiff);
    }

    else throw(Exception
    ("\nimage processing error : unknown file -> " + path_+name));

    return ct::Projection(data,width,height);
  }

  std::vector<float> const 
  Image_processor::process_buffer(unsigned long threshold) throw(Exception)
  {
    std::vector<float> data;

    if(channel_number_ != 1)

      throw(Exception("\nimage processing error : unsupported channel number"));

    switch(channel_size_)
    {
      case 8 :
      {
        auto buffer = static_cast<unsigned char *> (buffer_);

        for(unsigned index = 0 ; index < buffer_count_ ; ++index)
        {
          if(buffer[index] <= threshold) data.push_back(0.0);
          else data.push_back(static_cast<float> (buffer[index]) / UI8_MAX);
        }
        break;
      }

      case 16 :
      {
        auto buffer = static_cast<unsigned short *> (buffer_);

        for(unsigned index = 0 ; index < buffer_count_ ; ++index)
        {
          if(buffer[index] <= threshold) data.push_back(0.0);
          else data.push_back(static_cast<float> (buffer[index]) / UI16_MAX);
        }
        break;
      }

      default :
      {
        throw(Exception("\nimage processing error : unsupported channel size"));
      }
    }

    return data;
  }

  void Image_processor::delete_buffer() noexcept
  {
    if(buffer_ != nullptr)
    {
      switch(channel_size_)
      {
        case 8	:
        {
          auto buffer = static_cast<unsigned char *> (buffer_);
          delete[] buffer;
          break;
        }

        case 16 :
        {
          auto buffer = static_cast<unsigned short *> (buffer_);
          delete[] buffer;
          break;
        }
      }

      buffer_count_ = 0;
      buffer_ = nullptr;
    }
  }
}
