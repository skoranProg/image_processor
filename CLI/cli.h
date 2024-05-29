//
// Created by skoran on 10/20/2023.
//

#ifndef CPP_HSE_CLI_H
#define CPP_HSE_CLI_H

#include <map>
#include <memory>

#include "../config.h"
#include "../filters/Filter.h"

namespace image_processor::cli {

using filters::Filter;

using FilterCreatorPtr = const Filter* (*)(const FilterParams& string_params);

struct ParsedArgs {
    std::string in_path;
    std::string out_path;
    std::vector<std::shared_ptr<const Filter>> filters;
};

class FilterCreators {
public:
    const Filter* CreateFilter(FilterName filter_name, const FilterParams& params) const;

    void AddFilterCreator(FilterName fname, FilterCreatorPtr fcreator) const;

protected:
    mutable std::map<FilterName, FilterCreatorPtr> filter_creators_;
} extern const FCREATORS;

ParsedArgs ParseCLArguments(int argc, char** argv);

std::vector<std::pair<FilterName, FilterParams>> SplitCLArguments(int argc, char** argv);

void PrintHelp();

}  // namespace image_processor::cli

#endif  // CPP_HSE_CLI_H
