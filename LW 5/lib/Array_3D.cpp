#include "Array_3D.h"

uint32_t uint17_t::ToInt() const{
    const int array_idx = index >> 4;
    const int half1 = value[array_idx] >> (index & 0xF);
    int half2 = value[array_idx + 1] & (0xFFFF >> (15- (index & 0xF)));
    half2 <<= 16 - (index & 0xF);

    return half1 + half2;
}

uint17_t& uint17_t::operator=(uint32_t val) {
    int array_idx = index >> 4;
    value[array_idx] = (value[array_idx] & (0xFFFF >> (16 - (index & 0xF)))) + (val << (index & 0xF));
    val >>= 16 - (index & 0xF);
    value[array_idx + 1] = (value[array_idx + 1] & (0xFFFF << ((index & 0xF) + 1))) + (val & (0xFFFF >> (15 - (index & 0xF))));

    return *this;
}

std::ostream& operator<<(std::ostream& os, const uint17_t& value) {
    os << value.ToInt();
    return os;
}

std::istream& operator>>(std::istream& is, uint17_t value) {
    uint32_t val;
    is >> val;
    value = val;
    return is;
}

Array_3D Array_3D::MakeArray(const uint16_t len, const uint16_t wid, const uint16_t hgt) {
    return Array_3D(len, wid, hgt);
}

Array_3D::Array_2D Array_3D::operator[](const uint16_t x) {
    return Array_2D(*this, x);
}

Array_3D::Array_2D::Array_1D Array_3D::Array_2D::operator[](const uint16_t y) {
    return Array_1D(array, x, y);
}

uint17_t Array_3D::Array_2D::Array_1D::operator[](const uint16_t z) {
    const int valueIndex = (x * array.width * array.height + y * array.height + z) * 17;

    return uint17_t(array.data, valueIndex);
}

uint16_t Array_3D::GetLength() const {
    return length;
}

uint16_t Array_3D::GetWidth() const {
    return width;
}

uint16_t Array_3D::GetHeight() const {
    return height;
}

Array_3D operator+(Array_3D& lhs, Array_3D& rhs) {
    if (lhs.GetLength() != rhs.GetLength() ||
        lhs.GetWidth() != rhs.GetWidth() ||
        lhs.GetHeight() != rhs.GetHeight()) {
        throw std::invalid_argument("Undefined Behavior");
    }
    Array_3D result(lhs.GetLength(), lhs.GetWidth(), lhs.GetHeight());
    for (int x = 0; x < lhs.GetLength(); ++x) {
        for (int y = 0; y < lhs.GetWidth(); ++y) {
            for (int z = 0; z < lhs.GetHeight(); ++z) {
                const int lhs_value = lhs[x][y][z].ToInt();
                const int rhs_value = rhs[x][y][z].ToInt();
                if (lhs_value + rhs_value > MaxUINT17Value) {
                    throw std::overflow_error("Overflow");
                }
                result[x][y][z] = lhs_value + rhs_value;
            }
        }
    }

    return result;
}

Array_3D operator-(Array_3D& lhs, Array_3D& rhs) {
    if (lhs.GetLength() != rhs.GetLength() ||
        lhs.GetWidth() != rhs.GetWidth() ||
        lhs.GetHeight() != rhs.GetHeight()) {
        throw std::invalid_argument("Undefined Behavior");
        }
    Array_3D result(lhs.GetLength(), lhs.GetWidth(), lhs.GetHeight());
    for (int x = 0; x < lhs.GetLength(); ++x) {
        for (int y = 0; y < lhs.GetWidth(); ++y) {
            for (int z = 0; z < lhs.GetHeight(); ++z) {
                const uint32_t lhs_value = lhs[x][y][z].ToInt();
                const uint32_t rhs_value = rhs[x][y][z].ToInt();
                if (lhs_value < rhs_value) {
                    throw std::overflow_error("Underflow");
                }
                result[x][y][z] = lhs_value - rhs_value;
            }
        }
    }

    return result;
}

Array_3D operator*(Array_3D& arr, const int16_t multiplier) {
    Array_3D result(arr.GetLength(), arr.GetWidth(), arr.GetHeight());
    for (int x = 0; x < arr.GetLength(); ++x) {
        for (int y = 0; y < arr.GetWidth(); ++y) {
            for (int z = 0; z < arr.GetHeight(); ++z) {
                if (arr[x][y][z].ToInt() * multiplier > MaxUINT17Value) {
                    throw std::overflow_error("Overflow");
                }
                result[x][y][z] = arr[x][y][z].ToInt() * multiplier;
            }
        }
    }

    return result;
}
