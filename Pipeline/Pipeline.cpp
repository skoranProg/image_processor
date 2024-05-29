//
// Created by skoran on 10/25/2023.
//

#include "Pipeline.h"

namespace image_processor {

img::Image& Pipeline::Apply(img::Image& image) const {
    img::Image& res = image;
    for (auto& filter : filters_) {
        filter->Apply(res);
    }
    return res;
}

}  // namespace image_processor