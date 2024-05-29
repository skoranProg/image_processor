//
// Created by skoran on 10/28/2023.
//

#ifndef CPP_HSE_CROP_H
#define CPP_HSE_CROP_H

#include "../../CLI/cli.h"
#include "../Filter.h"

namespace image_processor::filters::crop {

extern const FilterName FNAME;

class Crop : public Filter {
public:
    Crop(size_t width, size_t height) : width_{width}, height_{height} {
    }

    img::Image& Apply(img::Image& image) const override;

protected:
    size_t width_, height_;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::crop

#endif  // CPP_HSE_CROP_H
