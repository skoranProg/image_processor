//
// Created by skoran on 10/28/2023.
//

#include "Crop.h"

namespace image_processor::filters::crop {

const FilterName FNAME = "crop";

img::Image& Crop::Apply(img::Image& image) const {
    img::Image res(std::min(image.GetRowNum(), height_), std::min(image.GetColNum(), width_));
    for (size_t i = 0; i < res.GetRowNum(); ++i) {
        for (size_t j = 0; j < res.GetColNum(); ++j) {
            res[i][j] = image[i][j];
        }
    }
    return image = res;
}

const Filter* CreateFilter(const FilterParams& params) {
    size_t width = SIZE_MAX;
    size_t height = SIZE_MAX;
    switch (params.size()) {
        case 0:
            break;
        case 1:
            width = std::stoull(params[0]);
            break;
        case 2:
            width = std::stoull(params[0]);
            height = std::stoull(params[1]);
            break;
        default:
            throw FormatError();
    }
    return new Crop(width, height);
}

}  // namespace image_processor::filters::crop