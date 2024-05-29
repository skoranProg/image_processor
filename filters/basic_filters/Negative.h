//
// Created by skoran on 10/28/2023.
//

#ifndef CPP_HSE_NEGATIVE_H
#define CPP_HSE_NEGATIVE_H

#include "../Filter.h"

namespace image_processor::filters::neg {

extern const FilterName FNAME;

class Negative : public Filter {
public:
    img::Image& Apply(img::Image& image) const override;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::neg

#endif  // CPP_HSE_NEGATIVE_H
