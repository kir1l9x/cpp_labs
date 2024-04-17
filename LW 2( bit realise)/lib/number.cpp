#include "number.h"

bool IsNegative(int2023_t value) {
    if (value.number[kBytesInNumber - 1].b_8 == 1) {
        return true;
    }
    return false;
}

void SetPositive(int2023_t& value) {
    value.number[kBytesInNumber - 1].b_8 = 0;
}

void SetNegative(int2023_t& value) {
    value.number[kBytesInNumber - 1].b_8 = 1;
}

int2023_t MakeBitwiseNot(const int2023_t& value) {
    int2023_t result;
    for (int i = 0; i < kBytesInNumber; ++i) {
        result.number[i].b_1 = !value.number[i].b_1;
        result.number[i].b_2 = !value.number[i].b_2;
        result.number[i].b_3 = !value.number[i].b_3;
        result.number[i].b_4 = !value.number[i].b_4;
        result.number[i].b_5 = !value.number[i].b_5;
        result.number[i].b_6 = !value.number[i].b_6;
        result.number[i].b_7 = !value.number[i].b_7;
        result.number[i].b_8 = !value.number[i].b_8;
    }
    return result + from_int(1);
}

bool IsAllZeros(const char* arr, int len) {
    for (int i = 0; i < len; ++i) {
        if (arr[i] != '0') {
            return false;
        }
    }
    return true;
}

int2023_t operator^(int2023_t value2, int2023_t value1) {
    int2023_t result = {};
    while (CompareAbs(value2, from_int(0)) > 0) {
        value2 = value2 / value1;
        result = result + from_int(1);
    }
    return result - from_int(1);
}

int2023_t operator<<(int2023_t value, uint16_t shift) {
    int2023_t result = value;
    if (shift <= 0) {
        return result;
    }
    for (int s = 0; s < shift; ++s) {
        uint8_t prev_bit = 0;
        for (int i = 0; i < kBytesInNumber; ++i) {
            uint8_t current_bit;
            current_bit = result.number[i].b_1;
            result.number[i].b_1 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_2;
            result.number[i].b_2 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_3;
            result.number[i].b_3 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_4;
            result.number[i].b_4 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_5;
            result.number[i].b_5 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_6;
            result.number[i].b_6 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_7;
            result.number[i].b_7 = prev_bit;
            prev_bit = current_bit;

            current_bit = result.number[i].b_8;
            result.number[i].b_8 = prev_bit;
            prev_bit = current_bit;
        }
    }

    return result;
}

int CompareAbs(const int2023_t& lhs, const int2023_t& rhs) {
    for (int i = kBytesInNumber - 1; i >= 0; --i) {
        if (lhs.number[i].b_8 > rhs.number[i].b_8) {
            return 1;
        } else if (lhs.number[i].b_8 < rhs.number[i].b_8) {
            return -1;
        }

        if (lhs.number[i].b_7 > rhs.number[i].b_7) {
            return 1;
        } else if (lhs.number[i].b_7 < rhs.number[i].b_7) {
            return -1;
        }

        if (lhs.number[i].b_6 > rhs.number[i].b_6) {
            return 1;
        } else if (lhs.number[i].b_6 < rhs.number[i].b_6) {
            return -1;
        }

        if (lhs.number[i].b_5 > rhs.number[i].b_5) {
            return 1;
        } else if (lhs.number[i].b_5 < rhs.number[i].b_5) {
            return -1;
        }

        if (lhs.number[i].b_4 > rhs.number[i].b_4) {
            return 1;
        } else if (lhs.number[i].b_4 < rhs.number[i].b_4) {
            return -1;
        }

        if (lhs.number[i].b_3 > rhs.number[i].b_3) {
            return 1;
        } else if (lhs.number[i].b_3 < rhs.number[i].b_3) {
            return -1;
        }

        if (lhs.number[i].b_2 > rhs.number[i].b_2) {
            return 1;
        } else if (lhs.number[i].b_2 < rhs.number[i].b_2) {
            return -1;
        }

        if (lhs.number[i].b_1 > rhs.number[i].b_1) {
            return 1;
        } else if (lhs.number[i].b_1 < rhs.number[i].b_1) {
            return -1;
        }
    }
    return 0;
}

int2023_t from_int(int32_t i) {
    int2023_t result;

    if (i < 0) {
        result.number[kBytesInNumber -1].b_8 = 1;
        if(i == INT32_MIN) {
            i = INT32_MAX;
        } else {
            i = -i;
        }
    }
    uint8_t c = 0;
    while (i > 0 && c < kBytesInNumber) {
        result.number[c].b_1 = i & 1;
        result.number[c].b_2 = (i & 2) >> 1;
        result.number[c].b_3 = (i & 4) >> 2;
        result.number[c].b_4 = (i & 8) >> 3;
        result.number[c].b_5 = (i & 16) >> 4;
        result.number[c].b_6 = (i & 32) >> 5;
        result.number[c].b_7 = (i & 64) >> 6;
        result.number[c].b_8 = (i & 128) >> 7;
        ++c;
        i >>= 8;
    }

    return result;
}

int2023_t from_string(const char* buff) {
    int2023_t result = {};
    uint16_t begin = 0;
    uint16_t buff_length = strlen(buff);
    bool is_negative = false;
    if (buff[0] == '-') {
        is_negative = true;
        ++begin;
        --buff_length;
    }

    char number[buff_length];
    for (int i = 0; i < buff_length; ++i) {
        number[i] = buff[begin];
        ++begin;
    }
    uint16_t start = 0;
    uint16_t current_res_pos = 1;
    uint16_t carry = 10;
    bool is_carry = false;
    while (!IsAllZeros(number, buff_length)) {
        if (current_res_pos % 8 == 1) {
            result.number[current_res_pos / 8].b_1 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 2) {
            result.number[current_res_pos / 8].b_2 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 3) {
            result.number[current_res_pos / 8].b_3 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 4) {
            result.number[current_res_pos / 8].b_4 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 5) {
            result.number[current_res_pos / 8].b_5 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 6) {
            result.number[current_res_pos / 8].b_6 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 7) {
            result.number[current_res_pos / 8].b_7 = (number[buff_length - 1] - '0') % 2;
        } else if (current_res_pos % 8 == 0) {
            result.number[current_res_pos / 8 - 1].b_8 = (number[buff_length - 1] - '0') % 2;
        }

        for (int i = start; i < buff_length; ++i) {
            if (number[i] != '0') {
                start = i;
                break;
            }
        }
        for (int i = start; i < buff_length; ++i) {
            if (!is_carry) {
                is_carry = (number[i] - '0') % 2;
                number[i] = ((number[i] - '0') / 2) + '0';
            } else {
                is_carry = (number[i] - '0') % 2;
                number[i] = (number[i] - '0' + carry) / 2 + '0';
            }
        }
        ++current_res_pos;
        is_carry = false;
    }
    if (is_negative) {
        SetNegative(result);
    } else {
        SetPositive(result);
    }

    return result;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result = {};
    if (IsNegative(lhs) != IsNegative(rhs)) {
        int2023_t abs_lhs = lhs;
        int2023_t abs_rhs = rhs;
        SetPositive(abs_lhs);
        SetPositive(abs_rhs);
        if (CompareAbs(abs_lhs, abs_rhs) > 0) {
            SetNegative(abs_rhs);
            int2023_t inverse_rhs = MakeBitwiseNot(abs_rhs);
            result = abs_lhs + inverse_rhs;
            if (IsNegative(lhs)) {
                SetNegative(result);
            }
        } else if (CompareAbs(abs_lhs, abs_rhs) < 0) {
            SetNegative(abs_lhs);
            int2023_t inverse_lhs = MakeBitwiseNot(abs_lhs);
            result = abs_rhs + inverse_lhs;
            if (IsNegative(rhs)) {
                SetNegative(result);
            }
        }
    } else {
        int carry = 0;
        for (int i = 0; i < kBytesInNumber; i++) {
            int bit_sum = 0;
            bit_sum += lhs.number[i].b_1 + rhs.number[i].b_1;
            result.number[i].b_1 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_2 + rhs.number[i].b_2;
            result.number[i].b_2 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_3 + rhs.number[i].b_3;
            result.number[i].b_3 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_4 + rhs.number[i].b_4;
            result.number[i].b_4 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_5 + rhs.number[i].b_5;
            result.number[i].b_5 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_6 + rhs.number[i].b_6;
            result.number[i].b_6 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_7 + rhs.number[i].b_7;
            result.number[i].b_7 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;

            bit_sum = lhs.number[i].b_8 + rhs.number[i].b_8;
            result.number[i].b_8 = (bit_sum + carry) % 2;
            carry = (bit_sum + carry) / 2;
        }
        if (IsNegative(lhs)) {
            SetNegative(result);
        } else {
            SetPositive(result);
        }
    }

    return result;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result = {};
    if (IsNegative(lhs) && !IsNegative(rhs)) {
        int2023_t abs_lhs = lhs;
        SetPositive(abs_lhs);
        result = abs_lhs + rhs;
        SetNegative(result);
    }
    if (!IsNegative(lhs) && IsNegative(rhs)) {
        int2023_t abs_rhs = rhs;
        SetPositive(abs_rhs);
        result = lhs + abs_rhs;
        SetPositive(result);
    }
    if (!IsNegative(lhs) && !IsNegative(rhs)) {
        int2023_t minus_rhs = rhs;
        SetNegative(minus_rhs);
        result = lhs + minus_rhs;
    }
    if (IsNegative(lhs) && IsNegative(rhs)) {
        int2023_t abs_rhs = rhs;
        SetPositive(abs_rhs);
        result = lhs + abs_rhs;
    }

    return result;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t abs_lhs = lhs;
    int2023_t abs_rhs = rhs;
    SetPositive(abs_lhs);
    SetPositive(abs_rhs);
    if (CompareAbs(abs_lhs, abs_rhs) < 0) {
        int2023_t change = abs_rhs;
        abs_rhs = abs_lhs;
        abs_lhs = change;
    }
    uint16_t shift_amount = 0, bit_num = 1;
    int2023_t result = {};
    uint8_t current_rhs_byte = 0;
    while (current_rhs_byte < kBytesInNumber) {
        int2023_t current_value = abs_lhs;
        uint8_t current_bit = 0;
        if (bit_num % 8 == 1) {
            current_bit = abs_rhs.number[current_rhs_byte].b_1;
        } else if (bit_num % 8 == 2) {
            current_bit = abs_rhs.number[current_rhs_byte].b_2;
        } else if (bit_num % 8 == 3) {
            current_bit = abs_rhs.number[current_rhs_byte].b_3;
        } else if (bit_num % 8 == 4) {
            current_bit = abs_rhs.number[current_rhs_byte].b_4;
        } else if (bit_num % 8 == 5) {
            current_bit = abs_rhs.number[current_rhs_byte].b_5;
        } else if (bit_num % 8 == 6) {
            current_bit = abs_rhs.number[current_rhs_byte].b_6;
        } else if (bit_num % 8 == 7) {
            current_bit = abs_rhs.number[current_rhs_byte].b_7;
        } else if (bit_num % 8 == 0) {
            current_bit = abs_rhs.number[current_rhs_byte].b_8;
        }
        if (bit_num % 8 == 0) {
            current_rhs_byte++;
        }
        if (current_bit == 1) {
            result = result + (current_value << shift_amount);
        }
        shift_amount++;
        bit_num++;
    }
    if (IsNegative(lhs) != IsNegative(rhs)) {
        SetNegative(result);
    } else {
        SetPositive(result);
    }

    return result;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t result = {};
    int2023_t abs_lhs = lhs;
    int2023_t abs_rhs = rhs;
    SetPositive(abs_lhs);
    SetPositive(abs_rhs);
    if (CompareAbs(abs_lhs, abs_rhs) < 0 || abs_lhs == from_int(0)) {
        return result;
    } else if (abs_rhs == from_int(0)) {
        std::cerr << "Division by zero";
    } else if (abs_rhs == from_int(1)) {
        if (IsNegative(lhs) != IsNegative(rhs)) {
            SetNegative(abs_lhs);
        }
        return abs_lhs;
    }
    int2023_t current_num = {};
    uint16_t current_lhs_bit_num = 2024;
    while (current_lhs_bit_num > 0) {
        uint8_t current_lhs_bit = 0;
        if (current_lhs_bit_num % 8 == 1) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_1;
        } else if (current_lhs_bit_num % 8 == 2) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_2;
        } else if (current_lhs_bit_num % 8 == 3) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_3;
        } else if (current_lhs_bit_num % 8 == 4) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_4;
        } else if (current_lhs_bit_num % 8 == 5) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_5;
        } else if (current_lhs_bit_num % 8 == 6) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_6;
        } else if (current_lhs_bit_num % 8 == 7) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8].b_7;
        } else if (current_lhs_bit_num % 8 == 0) {
            current_lhs_bit = abs_lhs.number[current_lhs_bit_num / 8 - 1].b_8;
        }
        if (current_lhs_bit == 1) {
            current_num = current_num << 1;
            current_num.number[0].b_1 = 1;
        } else {
            current_num = current_num << 1;
        }
        if (CompareAbs(current_num, abs_rhs) >= 0) {
            current_num = current_num - abs_rhs;
            result = result << 1;
            result.number[0].b_1 = 1;
        } else if (CompareAbs(current_num, abs_rhs) < 0){
            result = result << 1;
        }
        --current_lhs_bit_num;
    }
    if (IsNegative(lhs) != IsNegative(rhs)) {
        SetNegative(result);
    } else {
        SetPositive(result);
    }

    return result;
}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    if (IsNegative(lhs) == IsNegative(rhs) && CompareAbs(lhs, rhs) == 0) {
        return true;
    }
    return false;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    for (int i = kBytesInNumber - 1; i >= 0; --i) {
        uint8_t bits[8] = {
                value.number[i].b_8,
                value.number[i].b_7,
                value.number[i].b_6,
                value.number[i].b_5,
                value.number[i].b_4,
                value.number[i].b_3,
                value.number[i].b_2,
                value.number[i].b_1
        };

        for (int j = 0; j < 8; ++j) {
            stream << static_cast<int>(bits[j]);
        }
    }

    return stream;
}
