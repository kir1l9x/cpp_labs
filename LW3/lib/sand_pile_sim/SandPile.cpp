#include "Sandpile.h"

void SandPileParameters::StartSandPile() {
    field = new uint64_t*[length];
    for (int i = 0; i < length; ++i) {
        field[i] = new uint64_t[width];
        std::memset(field[i], 0, sizeof(uint64_t) * width);
    }
}

bool SandPileParameters::IsStable() const {
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < width; ++j)
            if (field[i][j] > kMaxGrainsInPoint) {
                return false;
            }

    }

    return true;
}

void SandPileParameters::AddColumnRight() {
    right_line_offset = how_many;
    for (int i = 0; i < length; ++i) {
        uint64_t* new_column = new uint64_t[width + how_many];

        for (int j = 0; j < width; ++j) {
            new_column[j] = field[i][j];
        }

        for (int j = width; j < width + how_many; ++j) {
            new_column[j] = 0;
        }

        delete[] field[i];
        field[i] = new_column;
    }
    width += how_many;
}

void SandPileParameters::AddColumnLeft() {
    left_line_offset = how_many;
    for (int i = 0; i < length; ++i) {
        uint64_t* new_column = new uint64_t[width + how_many];

        for (int j = 0; j < how_many; ++j) {
            new_column[j] = 0;
        }

        for (int j = how_many; j < width + how_many; ++j) {
            new_column[j] = field[i][j - how_many];
        }

        delete[] field[i];
        field[i] = new_column;
    }
    width += how_many;
}

void SandPileParameters::AddRowAbove() {
    high_line_offset = how_many;
    uint64_t** new_field = new uint64_t*[length + how_many];

    for (int i = 0; i < how_many; ++i) {
        new_field[i] = new uint64_t[width + how_many]();
    }

    for (int i = how_many; i < length + how_many; ++i) {
        new_field[i] = field[i - how_many];
    }

    delete[] field;
    field = new_field;
    length += how_many;
}

void SandPileParameters::AddRowUnder() {
    low_line_offset = how_many;
    uint64_t** new_field = new uint64_t*[length + how_many];

    for (int i = 0; i < length; ++i) {
        new_field[i] = field[i];
    }

    for (int i = length; i < length + how_many; ++i) {
        new_field[i] = new uint64_t[width + how_many]();
    }

    delete[] field;
    field = new_field;
    length += how_many;
}

void SandPileParameters::ToppleOneDeck(int64_t x, int64_t y) {
    field[y][x] -= 4;
    if (x + 1 >= width) {
        AddColumnRight();
    }
    if (x - 1 < 0) {
        AddColumnLeft();
        x += how_many;
    }
    if (y + 1 >= length) {
        AddRowUnder();
    }
    if (y - 1 < 0) {
        AddRowAbove();
        y += how_many;
    }
    if (x == width - right_line_offset - 1) {
        --right_line_offset;
    }
    if (x == left_line_offset) {
        --left_line_offset;
    }
    if (y == high_line_offset) {
        --high_line_offset;
    }
    if (y == length - low_line_offset - 1) {
        --low_line_offset;
    }
    ++field[y - 1][x];
    ++field[y + 1][x];
    ++field[y][x - 1];
    ++field[y][x + 1];
}

void SandPileParameters::ToppleAllOnce() {
    uint32_t current_high_line_offset = high_line_offset;
    uint32_t current_low_line_offset = low_line_offset;
    uint32_t current_left_line_offset = left_line_offset;
    uint32_t current_right_line_offset = right_line_offset;
    for (int i = current_high_line_offset; i < length - current_low_line_offset; ++i) {
        for (int j = current_left_line_offset; j < width - current_right_line_offset; ++j) {
            uint64_t grains_in_point = field[i][j];
            if (grains_in_point > kMaxGrainsInPoint) {
                ToppleOneDeck(j, i);
            }
        }
    }
}

void SandPileParameters::ToppleAll() {
    uint32_t current_high_line_offset;
    uint32_t current_low_line_offset;
    uint32_t current_left_line_offset;
    uint32_t current_right_line_offset;
    bool is_unstable = true;
    while (is_unstable) {
        is_unstable = false;
        current_high_line_offset = high_line_offset;
        current_low_line_offset = low_line_offset;
        current_left_line_offset = left_line_offset;
        current_right_line_offset = right_line_offset;
        for (int i = current_high_line_offset; i < length - current_low_line_offset; ++i) {
            for (int j = current_left_line_offset; j < width - current_right_line_offset; ++j) {
                uint64_t grains_in_point = field[i][j];
                if (grains_in_point > kMaxGrainsInPoint) {
                    is_unstable = true;
                    ToppleOneDeck(j, i);
                }
            }
        }
    }
}

void SandPileParameters::FastToppleOneDeck(int64_t x, int64_t y) {
    uint64_t grains_in_point = field[y][x];
    field[y][x] %= (kMaxGrainsInPoint + 1);

    if (x + 1 >= width) {
        AddColumnRight();
    }
    if (x - 1 < 0) {
        AddColumnLeft();
        x += how_many;
    }
    if (y + 1 >= length) {
        AddRowUnder();
    }
    if (y - 1 < 0) {
        AddRowAbove();
        y += how_many;
    }
    field[y - 1][x] += grains_in_point / (kMaxGrainsInPoint + 1);
    field[y + 1][x] += grains_in_point / (kMaxGrainsInPoint + 1);
    field[y][x - 1] += grains_in_point / (kMaxGrainsInPoint + 1);
    field[y][x + 1] += grains_in_point / (kMaxGrainsInPoint + 1);
    if (x == width - right_line_offset - 1) {
        --right_line_offset;
    }
    if (x == left_line_offset) {
        --left_line_offset;
    }
    if (y == high_line_offset) {
        --high_line_offset;
    }
    if (y == length - low_line_offset - 1) {
        --low_line_offset;
    }
}


void SandPileParameters::FastToppleAll() {
    uint32_t current_high_line_offset;
    uint32_t current_low_line_offset;
    uint32_t current_left_line_offset;
    uint32_t current_right_line_offset;
    bool is_unstable = true;
    while (is_unstable) {
        is_unstable = false;
        current_high_line_offset = high_line_offset;
        current_low_line_offset = low_line_offset;
        current_left_line_offset = left_line_offset;
        current_right_line_offset = right_line_offset;
        for (int i = current_high_line_offset; i < length - current_low_line_offset; ++i) {
            for (int j = current_left_line_offset; j < width - current_right_line_offset; ++j) {
                uint64_t grains_in_point = field[i][j];
                if (grains_in_point > kMaxGrainsInPoint) {
                    is_unstable = true;
                    FastToppleOneDeck(j, i);
                }
            }
        }
    }
}

void SandPileParameters::SetHowMany(uint32_t amount) {
    how_many = amount;
}

void SandPileParameters::FastToppleAllOnce() {
    uint32_t current_high_line_offset = high_line_offset;
    uint32_t current_low_line_offset = low_line_offset;
    uint32_t current_left_line_offset = left_line_offset;
    uint32_t current_right_line_offset = right_line_offset;
    for (int i = current_high_line_offset; i < length - current_low_line_offset; ++i) {
        for (int j = current_left_line_offset; j < width - current_right_line_offset; ++j) {
            uint64_t grains_in_point = field[i][j];
            if (grains_in_point > kMaxGrainsInPoint) {
                FastToppleOneDeck(j, i);
            }
        }
    }
}
