#pragma once
#include <cinttypes>
#include <iostream>
#include <cstring>

const uint8_t kBytesInNumber = 253;

struct Byte{
    uint8_t b_1 : 1;
    uint8_t b_2 : 1;
    uint8_t b_3 : 1;
    uint8_t b_4 : 1;
    uint8_t b_5 : 1;
    uint8_t b_6 : 1;
    uint8_t b_7 : 1;
    uint8_t b_8 : 1;
} ;

struct int2023_t {
    Byte number[253]{0};
};


static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

int2023_t from_int(int32_t i);

int2023_t from_string(const char* buff);

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs);

bool operator==(const int2023_t& lhs, const int2023_t& rhs);

bool operator!=(const int2023_t& lhs, const int2023_t& rhs);

std::ostream& operator<<(std::ostream& stream, const int2023_t& value);

int2023_t operator<<(int2023_t value, uint16_t shift);

int2023_t MakeBitwiseNot(const int2023_t& value);

bool IsNegative(int2023_t value);

void SetPositive(int2023_t& value);

void SetNegative(int2023_t& value);

bool IsAllZeros(const char* arr, int len);

int CompareAbs(const int2023_t& lhs, const int2023_t& rhs);

int2023_t operator^(int2023_t value1, int2023_t value2);


