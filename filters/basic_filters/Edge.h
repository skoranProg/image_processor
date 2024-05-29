//
// Created by skoran on 10/29/2023.
//

#ifndef CPP_HSE_EDGE_H
#define CPP_HSE_EDGE_H

#include "../MatrixFilter.h"
#include "Grayscale.h"

namespace image_processor::filters::edge {

extern const FilterName FNAME;

class Edge : public MatrixFilter {
public:
    explicit Edge(const utils::Matrix<double>& kernel, double threshold)
        : MatrixFilter(kernel), threshold_{threshold}, gs_{new gs::Grayscale()} {
    }

    img::Image& Apply(img::Image& image) const override;

protected:
    double threshold_;
    const std::unique_ptr<const gs::Grayscale> gs_;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::edge
#endif  // CPP_HSE_EDGE_H
