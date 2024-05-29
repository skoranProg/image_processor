//
// Created by skoran on 10/29/2023.
//

#include "MatrixFilter.h"

namespace image_processor::filters {

img::Image MatrixFilter::MatrixApply(const img::Image& image, const utils::Matrix<double>* kernel) const {
    if (!kernel) {
        kernel = &kernel_;
    }
    img::Image res(image.GetRowNum(), image.GetColNum(), {0, 0, 0});
    int64_t row_pos = 0;
    int64_t col_pos = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(image.GetRowNum()); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(image.GetColNum()); ++j) {
            for (int64_t ki = 0; ki < static_cast<int64_t>(kernel->GetRowNum()); ++ki) {
                row_pos = i + ki - static_cast<int64_t>(kernel->GetRowNum()) / 2LL;
                row_pos = std::min(static_cast<int64_t>(static_cast<int64_t>(image.GetRowNum()) - 1L),
                                   std::max(static_cast<int64_t>(0LL), row_pos));
                for (int64_t kj = 0; kj < static_cast<int64_t>(kernel->GetColNum()); ++kj) {
                    col_pos = j + kj - static_cast<int64_t>(kernel->GetColNum()) / 2LL;
                    col_pos = std::min(static_cast<int64_t>(static_cast<int64_t>(image.GetColNum()) - 1LL),
                                       std::max(static_cast<int64_t>(0LL), col_pos));
                    res[i][j].r += (*kernel)[ki][kj] * image[row_pos][col_pos].r;
                    res[i][j].g += (*kernel)[ki][kj] * image[row_pos][col_pos].g;
                    res[i][j].b += (*kernel)[ki][kj] * image[row_pos][col_pos].b;
                }
            }
            res[i][j].r = std::min(1.0, std::max(0.0, res[i][j].r));
            res[i][j].g = std::min(1.0, std::max(0.0, res[i][j].g));
            res[i][j].b = std::min(1.0, std::max(0.0, res[i][j].b));
        }
    }
    return res;
}

}  // namespace image_processor::filters