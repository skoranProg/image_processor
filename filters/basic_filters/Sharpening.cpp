//
// Created by skoran on 10/29/2023.
//

#include "Sharpening.h"

#include <array>

namespace image_processor::filters::sharp {

const FilterName FNAME = "sharp";

img::Image& Sharpening::Apply(img::Image& image) const {
    return image = MatrixApply(image);
}

const Filter* CreateFilter(const FilterParams& params) {
    if (!params.empty()) {
        throw FormatError();
    }
    static const utils::Matrix<double> KERNEL{
        std::array<std::array<double, 3>, 3>{{{0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}}}};
    return new Sharpening(KERNEL);
}

}  // namespace image_processor::filters::sharp
