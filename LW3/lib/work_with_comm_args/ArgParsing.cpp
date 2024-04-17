#include "ArgParsing.h"

bool IsStringNumber(const std::string& argument) {
    uint64_t size_of_string = argument.size();
    for (uint64_t i = 0; i < size_of_string; i++) {
        if (!std::isdigit(argument[i])) {
            return false;
        }
    }
    return true;
}

Arguments Parse(int argc, char* argv[]) {
    Arguments arguments;
    for (int i = 1; i < argc; ++i) {
        std::string current_arg = argv[i];
        if (current_arg == "-m" || current_arg == "--max_iter") {
            if (i + 1 >= argc) {
                std::cerr << "Not enough arguments for max iterations";
                std::exit(EXIT_FAILURE);
            }
            if (!IsStringNumber(argv[i + 1])) {
                std::cerr << "Invalid argument for max iterations";
                std::exit(EXIT_FAILURE);
            }
            arguments.max_iterations = std::stoull(argv[++i]);
        }
        if (current_arg == "-f" || current_arg == "--frequency") {
            if (i + 1 >= argc) {
                std::cerr << "Not enough arguments for frequency";
                std::exit(EXIT_FAILURE);
            }
            if (!IsStringNumber(argv[i + 1])) {
                std::cerr << "Invalid argument for frequency";
                std::exit(EXIT_FAILURE);
            }
            arguments.frequency = std::stoull(argv[++i]);
        }
        if (current_arg == "-i" || current_arg == "--input") {
            if (i + 1 >= argc) {
                std::cerr << "Not enough arguments for input file";
                std::exit(EXIT_FAILURE);
            }
            arguments.input_file = argv[++i];
        }
        if (current_arg == "-o" || current_arg == "--output") {
            if (i + 1 >= argc) {
                std::cerr << "Not enough arguments for output file";
                std::exit(EXIT_FAILURE);
            }
            arguments.output_dir = argv[++i];
        }
    }
    return arguments;
}
