//
// Created by skoran on 10/30/2023.
//

#include "OilFilter.h"

namespace image_processor::filters::oil {

const FilterName FNAME = "oil";

const Filter* CreateFilter(const FilterParams& params) {
    if (params.size() > 2) {
        throw FormatError();
    }
    int64_t radius = 0;
    double intensity = 0;
    try {
        if (!params.empty()) {
            radius = std::stoll(params[0]);
            if (params.size() == 2) {
                intensity = std::stod(params[1]);
            }
        }
    } catch (...) {
        throw FormatError();
    }
    return new OilFilter(radius, intensity);
}

img::Image& OilFilter::Apply(img::Image& image) const {
    img::Image res = image;
    int64_t pixel_intensity{};
    int64_t row_pos = 0;
    int64_t col_pos = 0;
    img::Pixel p;
    for (int64_t i = 0; i < static_cast<int64_t>(res.GetRowNum()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(res.GetColNum()); ++j) {
            std::map<int64_t, std::pair<int64_t, img::Pixel>> pixel_intensities;
            for (int64_t ki = -radius_; ki <= radius_; ++ki) {
                row_pos = std::min(static_cast<int64_t>(static_cast<int64_t>(image.GetRowNum()) - 1L),
                                   std::max(static_cast<int64_t>(0LL), i + ki));
                for (int64_t kj = -radius_; kj <= radius_; ++kj) {
                    col_pos = std::min(static_cast<int64_t>(static_cast<int64_t>(image.GetColNum()) - 1L),
                                       std::max(static_cast<int64_t>(0LL), j + kj));
                    p = image[row_pos][col_pos];
                    static const double CHANNEL_NUMBER = 3.0;
                    pixel_intensity = static_cast<int64_t>(((p.r + p.g + p.b) / CHANNEL_NUMBER) * intensity_);
                    ++pixel_intensities[pixel_intensity].first;
                    pixel_intensities[pixel_intensity].second.r += p.r;
                    pixel_intensities[pixel_intensity].second.g += p.g;
                    pixel_intensities[pixel_intensity].second.b += p.b;
                }
            }
            std::pair<int64_t, img::Pixel> mx{0, {}};
            for (const auto& it : pixel_intensities) {
                if (mx.first < it.second.first) {
                    mx = it.second;
                }
            }
            res[i][j] = {mx.second.b / static_cast<double>(mx.first), mx.second.g / static_cast<double>(mx.first),
                         mx.second.r / static_cast<double>(mx.first)};
        }
    }
    img::Image::Swap(res, image);
    return image;
}

}  // namespace image_processor::filters::oil