#pragma once
#include <iostream>
#include <cstdint>

const uint32_t MaxUINT17Value = 131071;

class uint17_t {
private:
    uint16_t* value;
    int index;

public:
    uint17_t(uint16_t* data, const int idx): value(data), index(idx) {}

    [[nodiscard]] uint32_t ToInt() const;
    uint17_t& operator=(uint32_t value);
    friend std::ostream& operator<<(std::ostream& os, const uint17_t& value);
    friend std::istream& operator>>(std::istream& is, uint17_t value);
};

class Array_3D {
private:

    uint16_t length;
    uint16_t width;
    uint16_t height;

public:
    uint16_t* data;
    Array_3D(uint16_t len, uint16_t wid, uint16_t hgt) : length(len), width(wid), height(hgt) {
        data = new uint16_t[(length * width * height * 17 + 15) / 16]();
    }
    ~Array_3D() {
        delete[] data;
    }
    Array_3D(const Array_3D& other)
        : length(other.length), width(other.width), height(other.height) {
        data = new uint16_t[(length * width * height * 17 + 15) / 16];
        std::copy(other.data, other.data + (length * width * height * 17 + 15) / 16, data);
    }
    Array_3D& operator=(const Array_3D& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            width = other.width;
            height = other.height;
            data = new uint16_t[(length * width * height * 17 + 15) / 16];
            std::copy(other.data, other.data + (length * width * height * 17 + 15) / 16, data);
        }
        return *this;
    }

    static Array_3D MakeArray(uint16_t len, uint16_t wid, uint16_t hgt);

    class Array_2D {
    private:
        Array_3D& array;
        uint16_t x;

    public:
        Array_2D(Array_3D& arr, uint16_t x) : array(arr), x(x) {}
        class Array_1D {
        private:
            Array_3D& array;
            uint16_t x;
            uint16_t y;
        public:
            Array_1D(Array_3D& arr, uint16_t x, uint16_t y) : array(arr), x(x), y(y) {}
            uint17_t operator[](uint16_t z);
        };
        Array_1D operator[](uint16_t y);
    };
    Array_2D operator[](uint16_t x);
    [[nodiscard]] uint16_t GetLength() const;
    [[nodiscard]] uint16_t GetWidth() const;
    [[nodiscard]] uint16_t GetHeight() const;
};

Array_3D operator+(Array_3D& lhs, Array_3D& rhs);
Array_3D operator-(Array_3D& lhs, Array_3D& rhs);
Array_3D operator*(Array_3D& arr, int16_t multiplier);