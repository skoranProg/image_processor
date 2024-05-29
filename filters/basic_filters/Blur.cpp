//
// Created by skoran on 10/29/2023.
//

#include "Blur.h"

namespace image_processor::filters::blur {

const FilterName FNAME = "blur";

img::Image& Blur::Apply(img::Image& image) const {
    return image = MatrixApply(MatrixApply(image, &kernel2_), &kernel_);
}

const Filter* CreateFilter(const FilterParams& params) {
    if (params.size() > 1) {
        throw FormatError();
    }
    static const double DEFAULT_SIGMA = 1;
    double sigma = DEFAULT_SIGMA;
    if (!params.empty()) {
        try {
            sigma = std::stod(params[0]);
        } catch (...) {
            throw FormatError();
        }
    }
    static const size_t RADIUS = 10;
    int64_t kernel_size = std::ceil(RADIUS * sigma);
    if (kernel_size % 2 == 0) {
        ++kernel_size;
    }
    static const double GAUSS_CF = 1.0 / (std::sqrt(2.0 * std::numbers::pi) * sigma);
    static const double GAUSS_CF_2 = 2.0 * sigma * sigma;
    utils::Matrix<double> kernel(kernel_size, 1, GAUSS_CF);
    for (int64_t i = 0; i < kernel_size; ++i) {
        kernel[i][0] *= std::exp(static_cast<double>((kernel_size / 2 - i) * (i - kernel_size / 2)) / GAUSS_CF_2);
    }
    return new Blur(kernel, sigma);
}

}  // namespace image_processor::filters::blur