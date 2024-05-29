//
// Created by skoran on 10/20/2023.
//

#ifndef CPP_HSE_CONFIG_H
#define CPP_HSE_CONFIG_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace image_processor {

using FilterName = std::string;
using FileFormatName = std::string;
using ImageFormat = std::string;
using FilterParams = std::vector<std::string>;

namespace filters {

class Filter;

}

class FormatError : public std::runtime_error {
public:
    FormatError() : runtime_error("Wrong format!") {
    }

    explicit FormatError(const char* str) : std::runtime_error(str) {
    }
};

class FileFormatError : public FormatError {
public:
    FileFormatError() : FormatError("Wrong file format!") {
    }

    explicit FileFormatError(const char* str) : FormatError(str) {
    }
};

}  // namespace image_processor
#endif  // CPP_HSE_CONFIG_H
