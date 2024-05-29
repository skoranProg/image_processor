//
// Created by skoran on 10/25/2023.
//

#ifndef CPP_HSE_PIPELINE_H
#define CPP_HSE_PIPELINE_H

#include <memory>

#include "../config.h"
#include "../filters/Filter.h"

namespace image_processor {

using filters::Filter;

class Pipeline {
public:
    explicit Pipeline(std::vector<std::shared_ptr<const Filter>> filters) : filters_{filters} {
    }

    img::Image& Apply(img::Image& image) const;

    img::Image New(const img::Image& image) const {
        img::Image res = image;
        Apply(res);
        return res;
    }

protected:
    std::vector<std::shared_ptr<const Filter>> filters_;
};

}  // namespace image_processor

#endif  // CPP_HSE_PIPELINE_H
