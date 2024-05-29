//
// Created by skoran on 10/28/2023.
//

#ifndef CPP_HSE_GRAYSCALE_H
#define CPP_HSE_GRAYSCALE_H

#include <iostream>

#include "../Filter.h"

namespace image_processor::filters::gs {

extern const FilterName FNAME;

class Grayscale : public Filter {
public:
    img::Image& Apply(img::Image& image) const override;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::gs

#endif  // CPP_HSE_GRAYSCALE_H
