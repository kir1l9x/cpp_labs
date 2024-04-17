#include "lib/Array_3D.h"
#include <iostream>

int main() {
    Array_3D array1 = Array_3D::MakeArray(2, 2, 2);
    Array_3D array2 = Array_3D::MakeArray(2, 2, 2);
    array1[0][0][0] = 50000;
    array2[0][0][0] = 15891;
    Array_3D sum = array1 * 2;
    std::cout << sum[0][0][0];
    return 0;
}
