//
// Created by skoran on 10/26/2023.
//

#include "Image.h"

namespace image_processor::img {

const ImageIOS IMAGE_IOS;

Image ImageIOS::Read(std::string path, ImageFormat format) const {
    return image_io_.at(format).first(path);
}

void ImageIOS::Write(const Image &img, std::string path, ImageFormat format) const {
    image_io_.at(format).second(img, path);
}

void ImageIOS::AddImageFormatIO(ImageReader in, ImageWriter out, ImageFormat format) const {
    image_io_[format] = std::make_pair(in, out);
}

}  // namespace image_processor::img