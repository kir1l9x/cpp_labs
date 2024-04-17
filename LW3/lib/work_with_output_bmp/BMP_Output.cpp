#include "BMP_Output.h"
#include <fstream>
#include <sstream>
#include <cstring>

void WriteToBMP(const SandPileParameters& sand, const std::string& output_dir, uint64_t iteration) {
    uint32_t width = sand.width - sand.left_line_offset - sand.right_line_offset;
    uint32_t length = sand.length - sand.high_line_offset - sand.low_line_offset;

    std::stringstream file_name;
    file_name << output_dir << "/sandpile(" << iteration << ").bmp";

    BMPHeader header = {};
    BMPInfoHeader info_header = {};

    int64_t row_size = ((4 * width + 31) / 32) * 4;
    int64_t image_size = row_size * length;

    header.type = 0x4D42;
    header.file_size = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + 64 + image_size;
    header.offset = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + 64;

    info_header.size = sizeof(BMPInfoHeader);
    info_header.width = width;
    info_header.height = length;
    info_header.planes = 1;
    info_header.bits_per_pixel = 4;
    info_header.compression = 0;
    info_header.image_size = image_size;
    info_header.x_pixels_per_meter = 2835;
    info_header.y_pixels_per_meter = 2835;
    info_header.colors_used = 16;
    info_header.colors_important = 16;

    std::ofstream file(file_name.str(), std::ios::binary);

    file.write(reinterpret_cast<char*>(&header), sizeof(header));
    file.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    file.put(255); file.put(255); file.put(255); file.put(0);
    file.put(0);   file.put(255); file.put(0);   file.put(0);
    file.put(0);   file.put(255); file.put(255); file.put(0);
    file.put(255); file.put(0);   file.put(255); file.put(0);

    for (int i = 4; i < 16; ++i) {
        file.put(0); file.put(0); file.put(0); file.put(0);
    }

    for (int64_t i = sand.length - sand.low_line_offset - 1; i >= sand.high_line_offset; --i) {
        int j = sand.left_line_offset;
        while (j < sand.width - sand.right_line_offset) {
            uint8_t value = 0;
            if (sand.field[i][j] > kMaxGrainsInPoint) {
                value |= 4 << 4;
            } else {
                value |= sand.field[i][j] << 4;
            }

            ++j;
            if (j < sand.width - sand.right_line_offset) {
                if (sand.field[i][j] > kMaxGrainsInPoint) {
                    value |= 4;
                } else {
                    value |= sand.field[i][j];
                }
            } else {
                value |= 0;
            }

            ++j;
            file.put(value);
        }

        int padding = row_size - ((width + 1) / 2);
        for (int k = 0; k < padding; ++k) {
            file.put(0);
        }
    }

    file.close();
}
