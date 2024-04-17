#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>

struct PrintFileParams {
    char *filename = nullptr;
    char line_delimiter = '\n';
    uint64_t lines_amount = 0xFFFFFFFFFFFFFFFF;
    bool is_tail = false;
};

PrintFileParams ArgParse(int argc, char* argv[]);

void PrintFile(const char *filename, uint64_t lines_amount, bool is_tail, char line_delimiter);

bool IsStringNumber(const std::string& line);

char IfEscapeSequences(char delimiter);

char TypeOfDelimiterLong(const std::string& argument);

char TypeOfDelimiterShort(const std::string& argument);


