//
// Created by skoran on 10/28/2023.
//

#include "Negative.h"

namespace image_processor::filters::neg {

const FilterName FNAME = "neg";

img::Image& Negative::Apply(img::Image& image) const {
    img::Image& res = image;
    for (size_t i = 0; i < res.GetRowNum(); ++i) {
        for (size_t j = 0; j < res.GetColNum(); ++j) {
            res[i][j] = {1 - res[i][j].b, 1 - res[i][j].g, 1 - res[i][j].r};
        }
    }
    return res;
}

const Filter* CreateFilter(const FilterParams& params) {
    if (!params.empty()) {
        throw FormatError();
    }
    return new Negative();
}

}  // namespace image_processor::filters::neg