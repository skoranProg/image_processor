//
// Created by skoran on 10/29/2023.
//

#ifndef CPP_HSE_MATRIXFILTER_H
#define CPP_HSE_MATRIXFILTER_H

#include <algorithm>

#include "Filter.h"
namespace image_processor::filters {

class MatrixFilter : public Filter {
public:
    MatrixFilter() = delete;

    explicit MatrixFilter(const utils::Matrix<double>& kernel) : kernel_{kernel} {
    }

protected:
    img::Image MatrixApply(const img::Image& image, const utils::Matrix<double>* kernel = nullptr) const;

protected:
    const utils::Matrix<double> kernel_;
};

}  // namespace image_processor::filters

#endif  // CPP_HSE_MATRIXFILTER_H
