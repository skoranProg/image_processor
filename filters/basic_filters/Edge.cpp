//
// Created by skoran on 10/29/2023.
//

#include "Edge.h"

#include "array"

namespace image_processor::filters::edge {

const FilterName FNAME = "edge";

img::Image& Edge::Apply(img::Image& image) const {
    img::Image res = MatrixApply(gs_->Apply(image));
    for (size_t i = 0; i < res.GetRowNum(); ++i) {
        for (size_t j = 0; j < res.GetColNum(); ++j) {
            if (res[i][j].r > threshold_) {
                res[i][j] = {1, 1, 1};
            } else {
                res[i][j] = {0, 0, 0};
            }
        }
    }
    return image = res;
}

const Filter* CreateFilter(const FilterParams& params) {
    if (params.size() > 1) {
        throw FormatError();
    }
    double threshold = 0;
    if (!params.empty()) {
        try {
            threshold = std::stod(params[0]);
        } catch (...) {
            throw FormatError();
        }
    }
    static const utils::Matrix<double> KERNEL{
        std::array<std::array<double, 3>, 3>{{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}}};
    return new Edge(KERNEL, threshold);
}

}  // namespace image_processor::filters::edge