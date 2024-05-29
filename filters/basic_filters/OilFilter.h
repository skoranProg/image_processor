//
// Created by skoran on 10/30/2023.
//

#ifndef CPP_HSE_OILFILTER_H
#define CPP_HSE_OILFILTER_H

#include "../Filter.h"

namespace image_processor::filters::oil {

extern const FilterName FNAME;

class OilFilter : public Filter {
public:
    OilFilter() = delete;

    explicit OilFilter(int64_t radius = 0, double intensity = 1) : radius_{radius}, intensity_{intensity} {
    }

    img::Image& Apply(img::Image& image) const override;

protected:
    int64_t radius_;
    double intensity_;
};

const Filter* CreateFilter(const FilterParams& params);

}  // namespace image_processor::filters::oil

#endif  // CPP_HSE_OILFILTER_H
