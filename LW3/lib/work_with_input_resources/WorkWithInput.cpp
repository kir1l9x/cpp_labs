#include "../sand_pile_sim/Sandpile.h"

void SandPileParameters::SetSize(std::string& input) {
    std::ifstream file(input);
    if (!file) {
        std::cerr << "Can't open file/File doesn't exist";
        std::exit(EXIT_FAILURE);
    }
    uint16_t start_length = 0;
    uint16_t start_width = 0;
    int16_t current_length;
    int16_t current_width;
    uint64_t third;
    while (file >> current_width >> current_length >> third) {
        if (current_length > start_length) {
            start_length = current_length;
        }
        if (current_width > start_width) {
            start_width = current_width;
        }
    }
    length = start_length + 1;
    width = start_width + 1;
}

void SandPileParameters::ReadFromTSV(std::string& input) const {
    std::ifstream file(input);
    int16_t x;
    int16_t y;
    uint64_t grains_amount;
    while (file >> y >> x >> grains_amount) {
        field[x][y] = grains_amount;
    }
}
