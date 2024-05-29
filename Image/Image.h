//
// Created by skoran on 10/18/2023.
//

#ifndef CPP_HSE_IMAGE_H
#define CPP_HSE_IMAGE_H

#include <cstdint>
#include <map>

#include "../config.h"
#include "../utils/Matrix.h"

namespace image_processor::img {

struct Pixel {
    double b{}, g{}, r{};
};

using Image = image_processor::utils::Matrix<Pixel>;
using ImageReader = Image (*)(const std::string& path);
using ImageWriter = void (*)(const Image& img, const std::string& path);

class ImageIOS {
public:
    Image Read(std::string path, ImageFormat format) const;

    void Write(const Image& img, std::string path, ImageFormat format) const;

    void AddImageFormatIO(ImageReader in, ImageWriter out, ImageFormat format) const;

protected:
    mutable std::map<ImageFormat, std::pair<ImageReader, ImageWriter>> image_io_;
} extern const IMAGE_IOS;

}  // namespace image_processor::img
#endif  // CPP_HSE_IMAGE_H
