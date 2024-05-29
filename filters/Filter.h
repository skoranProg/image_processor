//
// Created by skoran on 10/18/2023.
//

#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H

#include <string>
#include <vector>

#include "../config.h"
#include "../Image/Image.h"

namespace image_processor::filters {

class Filter {
public:
    virtual ~Filter() {
    }

    virtual img::Image& Apply(img::Image& image) const = 0;

    img::Image New(img::Image img) const {
        return Apply(img);
    }
};

}  // namespace image_processor::filters
#endif  // CPP_HSE_FILTER_H
