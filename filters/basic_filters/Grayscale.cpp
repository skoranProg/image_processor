//
// Created by skoran on 10/28/2023.
//

#include "Grayscale.h"

#include <memory>

namespace image_processor::filters::gs {

const FilterName FNAME = "gs";

img::Image& Grayscale::Apply(img::Image& image) const {
    static const double RED_CF = 0.299;
    static const double GREEN_CF = 0.587;
    static const double BLUE_CF = 0.114;
    for (size_t i = 0; i < image.GetRowNum(); ++i) {
        for (size_t j = 0; j < image.GetColNum(); ++j) {
            image[i][j].b = image[i][j].g = image[i][j].r =
                RED_CF * image[i][j].r + GREEN_CF * image[i][j].g + BLUE_CF * image[i][j].b;
        }
    }
    return image;
}

const Filter* CreateFilter(const FilterParams& params) {
    if (!params.empty()) {
        throw FormatError();
    }
    return new Grayscale();
}

}  // namespace image_processor::filters::gs