#include "lib/Array_3D.h"
#include "gtest/gtest.h"

// Тест на создание массива с помощью статического метода MakeArray
TEST(Array3DTests, CreateArray) {
    Array_3D array = Array_3D::MakeArray(10, 2, 30);
    EXPECT_EQ(array.GetLength(), 10);
    EXPECT_EQ(array.GetWidth(), 2);
    EXPECT_EQ(array.GetHeight(), 30);
}

// Тест на операторы индексации [] для чтения и записи значений в массив
TEST(Array3DTests, Indexing) {
    Array_3D array = Array_3D::MakeArray(3, 3, 3);

    // Запись и чтение значений
    array[1][1][1] = 42;
    EXPECT_EQ(array[1][1][1].ToInt(), 42);
}

// Тест на оператор умножения (*)
TEST(Array3DTests, Multiplication) {
    Array_3D array1 = Array_3D::MakeArray(2, 2, 2);
    Array_3D array2 = Array_3D::MakeArray(2, 2, 2);

    // Умножение на число
    int multiplier = 5;
    Array_3D result = array1 * multiplier;

    // Проверка результатов
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                EXPECT_EQ(result[x][y][z].ToInt(), array1[x][y][z].ToInt() * multiplier);
            }
        }
    }
}

// Тест на оператор сложения (+)
TEST(Array3DTests, Addition) {
    Array_3D array1 = Array_3D::MakeArray(2, 2, 2);
    Array_3D array2 = Array_3D::MakeArray(2, 2, 2);

    // Заполнение массивов
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                array1[x][y][z] = 5;
                array2[x][y][z] = 7;
            }
        }
    }

    // Сложение массивов
    Array_3D result = array1 + array2;

    // Проверка результатов
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                EXPECT_EQ(result[x][y][z].ToInt(), array1[x][y][z].ToInt() + array2[x][y][z].ToInt());
            }
        }
    }
}

// Тест на оператор вычитания (-)
TEST(Array3DTests, Subtraction) {
    Array_3D array1 = Array_3D::MakeArray(2, 2, 2);
    Array_3D array2 = Array_3D::MakeArray(2, 2, 2);

    // Заполнение массивов
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                array1[x][y][z] = 10;
                array2[x][y][z] = 3;
            }
        }
    }

    // Вычитание массивов
    Array_3D result = array1 - array2;

    // Проверка результатов
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                EXPECT_EQ(result[x][y][z].ToInt(), array1[x][y][z].ToInt() - array2[x][y][z].ToInt());
            }
        }
    }
}

// Тест на операторы ввода (>>) и вывода (<<)
TEST(Array3DTests, InputOutput) {
    Array_3D array = Array_3D::MakeArray(2, 2, 2);

    // Запись и чтение значений с использованием потоков
    std::stringstream ss;
    ss << "42 17 8 99";
    ss >> array[0][0][0] >> array[0][0][1] >> array[0][1][0] >> array[1][0][0];

    // Проверка результатов
    std::stringstream output;
    output << array[0][0][0] << " " << array[0][0][1] << " " << array[0][1][0] << " " << array[1][0][0];

    EXPECT_EQ(output.str(), "42 17 8 99");
}

// Тест на переполнение при сложении
TEST(Array3DTests, AdditionOverflow) {
    Array_3D array1 = Array_3D::MakeArray(1, 1, 1);
    Array_3D array2 = Array_3D::MakeArray(1, 1, 1);
    array1[0][0][0] = MaxUINT17Value;
    array2[0][0][0] = 1;

    EXPECT_THROW(array1 + array2, std::overflow_error);
}

// Тест на переполнение при умножении
TEST(Array3DTests, MultiplicationOverflow) {
    Array_3D array = Array_3D::MakeArray(1, 1, 1);
    array[0][0][0] = MaxUINT17Value / 2 + 1;

    EXPECT_THROW(array * 2, std::overflow_error);
}

// Тест на корректность представления данных
TEST(Array3DTests, DataRepresentation) {
    Array_3D array = Array_3D::MakeArray(1, 1, 1);
    array[0][0][0] = 0b10000000000000001;  // 17 бит

    EXPECT_EQ(array[0][0][0].ToInt(), 0b10000000000000001);
}

// Тест на чтение и запись с перекрытием битов
TEST(Array3DTests, BitOverlap) {
    Array_3D array = Array_3D::MakeArray(2, 2, 2);
    array[0][0][0] = 0xFFFF;  // Записываем максимальное 17-битное значение
    array[0][0][1] = 0x1;    // Записываем минимальное ненулевое значение

    EXPECT_EQ(array[0][0][0].ToInt(), 0xFFFF);
    EXPECT_EQ(array[0][0][1].ToInt(), 0x1);
}

// Тест на проверку инициализации нулевыми значениями
TEST(Array3DTests, ZeroInitialization) {
    Array_3D array = Array_3D::MakeArray(2, 2, 2);

    // Проверяем, что все значения инициализированы нулями
    for (int x = 0; x < 2; ++x) {
        for (int y = 0; y < 2; ++y) {
            for (int z = 0; z < 2; ++z) {
                EXPECT_EQ(array[x][y][z].ToInt(), 0);
            }
        }
    }
}

// Тест на запись и чтение граничных значений
TEST(Array3DTests, EdgeValues) {
    Array_3D array = Array_3D::MakeArray(1, 1, 1);
    array[0][0][0] = MaxUINT17Value;  // Максимальное значение

    EXPECT_EQ(array[0][0][0].ToInt(), MaxUINT17Value);
}

// Тест на диапазон значений
TEST(Array3DTests, ValueRange) {
    Array_3D array = Array_3D::MakeArray(1, 1, 1);

    // Проверка ряда значений в диапазоне
    for (uint32_t val = 0; val < 100; ++val) {
        array[0][0][0] = val;
        EXPECT_EQ(array[0][0][0].ToInt(), val);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
