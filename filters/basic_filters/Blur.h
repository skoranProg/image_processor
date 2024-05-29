//
// Created by skoran on 10/29/2023.
//

#ifndef CPP_HSE_BLUR_H
#define CPP_HSE_BLUR_H

#include <cmath>

#include "../MatrixFilter.h"

namespace image_processor::filters::blur {

extern const FilterName FNAME;

class Blur : public MatrixFilter {
public:
    explicit Blur(const utils::Matrix<double>& kernel, double sigma)
        : MatrixFilter(kernel), sigma_{sigma}, kernel2_{kernel.Transpose()} {
    }

    img::Image& Apply(img::Image& image) const override;

protected:
    const double sigma_;
    const utils::Matrix<double> kernel2_;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::blur

#endif  // CPP_HSE_BLUR_H
