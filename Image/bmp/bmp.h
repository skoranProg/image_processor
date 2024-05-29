//
// Created by skoran on 10/26/2023.
//

#ifndef CPP_HSE_BMP_H
#define CPP_HSE_BMP_H

#include <string>

#include "../Image.h"

namespace image_processor::img::bmp {

// TODO: Consider making a class

extern const FileFormatName FFNAME;

Image ReadBMP(const std::string& path);

void WriteBMP(const Image& img, const std::string& path);

}  // namespace image_processor::img::bmp

#endif  // CPP_HSE_BMP_H
