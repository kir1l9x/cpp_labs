#pragma once
#include <iostream>
#include <fstream>
#include <cstdint>

class Arguments {
public:
    uint64_t max_iterations = 0xFFFFFFFFFFFFFFFF;
    uint64_t frequency = 0;
    std::string input_file;
    std::string output_dir;
};

Arguments Parse(int argc, char* argv[]);

bool IsStringNumber(const std::string& argument);
