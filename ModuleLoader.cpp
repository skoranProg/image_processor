//
// Created by skoran on 10/30/2023.
//

#include "ModuleLoader.h"

#include "CLI/cli.h"
#include "filters/basic_filters/basic_filters.h"
#include "Image/bmp/bmp.h"

namespace image_processor {

void LoadBaseModules() {
    // Base format:
    img::IMAGE_IOS.AddImageFormatIO(img::bmp::ReadBMP, img::bmp::WriteBMP, img::bmp::FFNAME);
    // Base filters:
    cli::FCREATORS.AddFilterCreator(filters::crop::FNAME, filters::crop::CreateFilter);
    cli::FCREATORS.AddFilterCreator(filters::gs::FNAME, filters::gs::CreateFilter);
    cli::FCREATORS.AddFilterCreator(filters::neg::FNAME, filters::neg::CreateFilter);
    cli::FCREATORS.AddFilterCreator(filters::sharp::FNAME, filters::sharp::CreateFilter);
    cli::FCREATORS.AddFilterCreator(filters::edge::FNAME, filters::edge::CreateFilter);
    cli::FCREATORS.AddFilterCreator(filters::blur::FNAME, filters::blur::CreateFilter);
    cli::FCREATORS.AddFilterCreator(filters::oil::FNAME, filters::oil::CreateFilter);
}

void LoadPlugins() {
}

void LoadModules() {
    LoadBaseModules();
    LoadPlugins();
}

}  // namespace image_processor