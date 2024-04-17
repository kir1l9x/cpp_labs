#include "PrintFile.h"

int main(int argc, char* argv[]) {
    PrintFileParams params = ArgParse(argc, argv);
    PrintFile(params.filename, params.lines_amount, params.is_tail, params.line_delimiter);

    return 0;
}