//
// Created by skoran on 10/20/2023.
//

#include "cli.h"

#include <iostream>

namespace image_processor::cli {

const FilterCreators FCREATORS;

void FilterCreators::AddFilterCreator(image_processor::FilterName fname,
                                      image_processor::cli::FilterCreatorPtr fcreator) const {
    filter_creators_[fname] = fcreator;
}

const Filter* FilterCreators::CreateFilter(FilterName filter_name, const FilterParams& params) const {
    return filter_creators_.at(filter_name)(params);
}

ParsedArgs ParseCLArguments(int argc, char** argv) {
    if (argc == 1) {
        PrintHelp();
        return {};
    }
    if (argc < 3) {
        std::cerr << "Missing required arguments" << std::endl;
        return {};
    }
    ParsedArgs res;
    res.in_path = argv[1];
    res.out_path = argv[2];
    std::vector<std::shared_ptr<const Filter>>& filters = res.filters;
    try {
        for (const auto& i : SplitCLArguments(argc - 3, argv + 3)) {
            try {
                const Filter* tmp_ptr = FCREATORS.CreateFilter(i.first, i.second);
                filters.emplace_back(std::shared_ptr<const Filter>(tmp_ptr));
            } catch (const std::out_of_range& e) {
                std::cerr << "No such filter: \"" << i.first << "\" !" << std::endl;
                return {};
            }
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return {};
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return {};
    }
    return res;
}

std::vector<std::pair<FilterName, FilterParams>> SplitCLArguments(int argc, char** argv) {
    if (argc == 0) {
        return {};
    }
    std::vector<std::pair<FilterName, FilterParams>> res;
    int j = 0;
    if (argv[0][0] != '-') {
        throw FormatError();
    }
    for (int i = 0; i < argc; i = j) {
        ++j;
        res.emplace_back(argv[i] + 1, FilterParams());
        while (j < argc && argv[j][0] != '-') {
            res.back().second.emplace_back(argv[j]);
            ++j;
        }
    }
    return res;
}

static const std::string USAGE =
    "Usage:\n\t{program_name} {input_file} {output_file} [-{filter_name} [filter_param1] [filter_param2] ...] "
    "[-{filter_name} [filter_param1] [filter_param2] ...] ...";

void PrintHelp() {
    std::cout << USAGE << std::endl;
}

}  // namespace image_processor::cli
