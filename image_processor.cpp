#include <iostream>

#include "CLI/cli.h"
#include "config.h"
#include "filters/basic_filters/basic_filters.h"
#include "Image/bmp/bmp.h"
#include "Image/Image.h"
#include "ModuleLoader.h"
#include "Pipeline/Pipeline.h"

int main(int argc, char** argv) {
    image_processor::LoadModules();
    image_processor::cli::ParsedArgs args = image_processor::cli::ParseCLArguments(argc, argv);
    if (args.in_path.empty()) {
        return 0;
    }
    try {
        image_processor::img::Image image =
            image_processor::img::IMAGE_IOS.Read(args.in_path, image_processor::img::bmp::FFNAME);
        image_processor::Pipeline pl(args.filters);
        image = pl.Apply(image);
        image_processor::img::IMAGE_IOS.Write(image, args.out_path, image_processor::img::bmp::FFNAME);
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown Error!" << std::endl;
    }
    return 0;
}
