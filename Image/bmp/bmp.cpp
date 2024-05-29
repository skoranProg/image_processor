//
// Created by skoran on 10/26/2023.
//

#include "bmp.h"

#include <fstream>
#include <stdexcept>

namespace image_processor::img::bmp {

const FileFormatName FFNAME = "bmp";

struct DiscretePixel {
    uint8_t b, g, r;
};

static const double MAX_COLOR_VALUE = 255.0;

struct BmpHeader {
    uint8_t header_field[2];
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
} __attribute__((packed));

static const BmpHeader TYPICAL_BMP_HEADER = {
    {'B', 'M'}, 0, 0, 0, 54,
};

struct DibHeader {
    uint32_t header_size;
    int32_t bitmap_width;
    int32_t bitmap_height;
    uint16_t color_planes_num;
    uint16_t color_depth;
    uint32_t compression_method;
    uint32_t image_size;
    int32_t horizontal_resolution;
    int32_t vertical_resolution;
    uint32_t colors_num;
    uint32_t important_colors_num;
} __attribute__((packed));

static const DibHeader TYPICAL_DIB_HEADER = {40, 0, 0, 1, 24, 0, 0, 1, 1, 0, 0};

// BMP header I/O

bool ValidateBMPHeader(const BmpHeader& bmph) {
    return bmph.header_field[0] == TYPICAL_BMP_HEADER.header_field[0] &&
           bmph.header_field[1] == TYPICAL_BMP_HEADER.header_field[1] &&
           bmph.file_size >= sizeof(BmpHeader) + sizeof(DibHeader);
}

BmpHeader ReadBmpHeader(std::istream& in) {
    BmpHeader bmp_header;
    in.read(reinterpret_cast<char*>(&bmp_header), sizeof(BmpHeader));
    if (!ValidateBMPHeader(bmp_header)) {
        throw FileFormatError();
    }
    return bmp_header;
}

void WriteBMPHeader(std::ostream& out, const Image& img) {
    BmpHeader bmp_header = TYPICAL_BMP_HEADER;
    bmp_header.file_size = sizeof(BmpHeader) + sizeof(DibHeader) +
                           img.GetRowNum() * ((img.GetColNum() * sizeof(DiscretePixel) + 3) / 4) * 4;
    out.write(reinterpret_cast<const char*>(&bmp_header), sizeof(BmpHeader));
}

// DIB header I/O

bool ValidateDIBHeader(const DibHeader& dibh) {
    return dibh.header_size == sizeof(DibHeader) && dibh.color_planes_num == TYPICAL_DIB_HEADER.color_planes_num &&
           dibh.color_depth == TYPICAL_DIB_HEADER.color_depth &&
           dibh.compression_method == TYPICAL_DIB_HEADER.compression_method &&
           (dibh.image_size == 0 ||
            dibh.image_size == ((dibh.bitmap_width * sizeof(DiscretePixel) + 3ul) / 4ul) * 4 * dibh.bitmap_height) &&
           dibh.colors_num == TYPICAL_DIB_HEADER.colors_num &&
           dibh.important_colors_num == TYPICAL_DIB_HEADER.important_colors_num;
}

DibHeader ReadDibHeader(std::istream& in) {
    DibHeader dib_header;
    in.read(reinterpret_cast<char*>(&dib_header), sizeof(DibHeader));
    if (!ValidateDIBHeader(dib_header)) {
        throw FileFormatError();
    }
    return dib_header;
}

void WriteDIBHeader(std::ostream& out, const Image& img) {
    DibHeader dib_header = TYPICAL_DIB_HEADER;
    dib_header.bitmap_width = static_cast<int32_t>(img.GetColNum());
    dib_header.bitmap_height = static_cast<int32_t>(img.GetRowNum());
    out.write(reinterpret_cast<const char*>(&dib_header), sizeof(DibHeader));
}

// DiscretePixel data I/O

Image ReadBMPData(std::istream& in, size_t width, size_t height) {
    Image res(height, width);
    DiscretePixel* p = new DiscretePixel[width];
    for (size_t i = 0; i < height; ++i) {
        if (in.eof()) {
            delete[] p;
            throw FileFormatError();
        }
        in.read(reinterpret_cast<char*>(p), static_cast<std::streamsize>(sizeof(DiscretePixel) * width));
        in.seekg((4 - (static_cast<std::streamsize>(sizeof(DiscretePixel) * width) % 4)) % 4, std::istream::cur);
        if (in.fail()) {
            delete[] p;
            throw FileFormatError();
        }
        for (size_t j = 0; j < width; ++j) {
            res[height - i - 1][j].b = static_cast<double>(p[j].b) / MAX_COLOR_VALUE;
            res[height - i - 1][j].g = static_cast<double>(p[j].g) / MAX_COLOR_VALUE;
            res[height - i - 1][j].r = static_cast<double>(p[j].r) / MAX_COLOR_VALUE;
        }
    }
    delete[] p;
    return res;
}

void WriteBMPData(std::ostream& out, const Image& img) {
    DiscretePixel p;
    for (size_t i = 0; i < img.GetRowNum(); ++i) {
        for (size_t j = 0; j < img.GetColNum(); ++j) {
            p.b = static_cast<uint8_t>(img[img.GetRowNum() - i - 1][j].b * MAX_COLOR_VALUE);
            p.g = static_cast<uint8_t>(img[img.GetRowNum() - i - 1][j].g * MAX_COLOR_VALUE);
            p.r = static_cast<uint8_t>(img[img.GetRowNum() - i - 1][j].r * MAX_COLOR_VALUE);
            out.write(reinterpret_cast<const char*>(&p), sizeof(DiscretePixel));
        }
        out.write("\0\0\0\0", (4 - (static_cast<std::streamsize>(sizeof(DiscretePixel) * img.GetColNum()) % 4)) % 4);
    }
}

// Image I/O

Image ReadBMP(const std::string& path) {
    std::ifstream in(path, std::ifstream::binary);
    if (!in.is_open()) {
        throw std::runtime_error("Cannot open File!");
    }
    static const std::ifstream::pos_type DIB_HEADER_OFFSET = 14;
    Image res;
    try {
        in.seekg(0);
        BmpHeader bmp_header = ReadBmpHeader(in);
        in.seekg(DIB_HEADER_OFFSET);
        DibHeader dib_header = ReadDibHeader(in);
        in.seekg(bmp_header.offset);
        res = ReadBMPData(in, dib_header.bitmap_width, dib_header.bitmap_height);
    } catch (std::runtime_error& e) {
        in.close();
        throw e;
    }
    in.close();
    return res;
}

void WriteBMP(const Image& img, const std::string& path) {
    std::ofstream out(path, std::ofstream::binary);
    if (!out.is_open()) {
        throw std::runtime_error("Cannot open File!");
    }
    try {
        WriteBMPHeader(out, img);
        WriteDIBHeader(out, img);
        WriteBMPData(out, img);
    } catch (std::runtime_error& e) {
        out.close();
        throw e;
    }
    out.close();
}

}  // namespace image_processor::img::bmp