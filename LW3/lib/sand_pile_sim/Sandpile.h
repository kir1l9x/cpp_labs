#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>

const uint8_t kMaxGrainsInPoint = 3;

class SandPileParameters {
public:
    uint32_t length;
    uint32_t width;
    uint64_t** field;
    uint32_t high_line_offset;
    uint32_t low_line_offset;
    uint32_t right_line_offset;
    uint32_t left_line_offset;
    uint64_t how_many = 7;

    void StartSandPile();

    void ReadFromTSV(std::string& input) const;

    bool IsStable() const;

    void SetSize(std::string& input);

    void ToppleAllOnce();

    void ToppleAll();

    void FastToppleAll();

    void SetHowMany(uint32_t amount);

    void FastToppleAllOnce();

private:
    void ToppleOneDeck(int64_t x, int64_t y);

    void FastToppleOneDeck(int64_t x, int64_t y);

    void AddColumnRight();

    void AddColumnLeft();

    void AddRowAbove();

    void AddRowUnder();
};