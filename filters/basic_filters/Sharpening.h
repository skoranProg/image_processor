//
// Created by skoran on 10/29/2023.
//

#ifndef CPP_HSE_SHARPENING_H
#define CPP_HSE_SHARPENING_H

#include "../MatrixFilter.h"

namespace image_processor::filters::sharp {

extern const FilterName FNAME;

class Sharpening : public MatrixFilter {
public:
    explicit Sharpening(const utils::Matrix<double>& kernel) : MatrixFilter(kernel) {
    }

    img::Image& Apply(img::Image& image) const override;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::sharp
#endif  // CPP_HSE_SHARPENING_H
