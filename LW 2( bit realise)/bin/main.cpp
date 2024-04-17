#include <lib/number.h>
#include <iostream>
#include <ranges>

#define log ^

int main() {
    int2023_t a = from_int(32),b = from_int(2),c;
    c = a log b;

    std::cout << c << std::endl;
    return 0;
}
