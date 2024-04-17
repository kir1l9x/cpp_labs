#include "PrintFile.h"

bool IsStringNumber(const std::string& argument) {
    uint64_t size_of_string = argument.size();
    for (uint64_t i = 0; i < size_of_string; i++) {
        if (!std::isdigit(argument[i])) {
            return false;
        }
    }
    return true;
}


char IfEscapeSequences(char delimiter) {
    if (delimiter == 't') {
        return '\t';
    }
    if (delimiter == 'n') {
        return '\n';
    }
    if (delimiter == 'r') {
        return '\r';
    }
    if (delimiter == '0') {
        return '\0';
    }
    if (delimiter == 'v') {
        return '\v';
    }
    std::cerr << "Invalid argument for delimiter, which starts with \\";
    std::exit(EXIT_FAILURE);
}


char TypeOfDelimiterLong(const std::string& argument) {
    if (argument.size() == 13) {
        return argument[12];
    } else if (argument.size() == 14 && argument[12] == '\\') {
        return IfEscapeSequences(argument[13]);
    }
    std::cerr << "Too long/short/invalid argument for delimiter(long)";
    std::exit(EXIT_FAILURE);
}


char TypeOfDelimiterShort(const std::string& argument) {
    if (argument.size() == 1) {
        return argument[0];
    } else if (argument.size() == 2 && argument.starts_with('\\')) {
        return IfEscapeSequences(argument[1]);
    }
    std::cerr << "Too long/short/invalid argument for delimiter(short)";
    std::exit(EXIT_FAILURE);
}


PrintFileParams ArgParse(int argc, char* argv[]) {
    PrintFileParams params;

    for (int i = 1; i < argc; i++) {
        std::string current_arg = argv[i];
        if (current_arg.starts_with("--lines=")) {
            if (!IsStringNumber(current_arg.substr(8))) {
                std::cerr << "Invalid argument for lines amount";
                std::exit(EXIT_FAILURE);
            }
            params.lines_amount = std::stoull(current_arg.substr(8));
        } else if (current_arg == "--tail" || current_arg == "-t") {
            params.is_tail = true;
        } else if (current_arg.starts_with("--delimiter=")) {
            params.line_delimiter = TypeOfDelimiterLong(current_arg);
        } else if (current_arg == "-l") {
            if (i + 1 >= argc) {
                std::cerr << "Not enough arguments for lines amount";
                std::exit(EXIT_FAILURE);
            }
            if (!IsStringNumber(argv[i + 1])) {
                std::cerr << "Invalid argument for lines amount";
                std::exit(EXIT_FAILURE);
            }
            params.lines_amount = std::stoull(argv[i + 1]);
            i++;
        } else if (current_arg == "-d") {
            if (i + 1 >= argc) {
                std::cerr << "Not enough arguments for delimiter";
                std::exit(EXIT_FAILURE);
            }
            std::string next_arg = argv[i + 1];
            params.line_delimiter = TypeOfDelimiterShort(next_arg);
            i++;
        } else {
            params.filename = argv[i];
        }
    }
    if (!params.filename) {
        std::cerr << "Please give me a file";
        std::exit(EXIT_FAILURE);
    }
    return params;
}


void PrintFile(const char* filename, uint64_t lines_amount, bool is_tail, char line_delimiter) {
    std::ifstream file(filename);
    char c;
    if (!file) {
        std::cerr << "Can't open file/File doesn't exist";
        std::exit(EXIT_FAILURE);
    }
    if (!is_tail) {
        while (lines_amount > 0 && file.get(c)) {
            std::cout << c;
            if (c == line_delimiter) {
                --lines_amount;
            }
        }
    } else {
        file.seekg(0, std::ios::end);
        uint64_t size = file.tellg();
        uint64_t del_counter = 0;
        uint64_t back_start = 0;
        for (uint64_t i = 1; i <= size; ++i) {
            file.seekg(-static_cast<std::streamoff>(i), std::ios::end);
            file.get(c);
            if (c == line_delimiter) {
                del_counter++;
                i++;
            }
            if (del_counter == lines_amount || i == size) {
                back_start = -i;
                break;
            }
        }
        file.seekg(static_cast<std::streamoff>(back_start), std::ios::end);
        while (file.get(c)) {
            std::cout << c;
        }
    }
}

