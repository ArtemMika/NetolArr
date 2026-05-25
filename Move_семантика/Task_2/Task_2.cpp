#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

class big_integer
{
private:
    std::string digits;
    bool is_negative;

    static bool is_digit(char c)
    {
        return c >= '0' && c <= '9';
    }

    void remove_leading_zeros() 
    {
        size_t start = 0;
        while (start < digits.length() - 1 && digits[start] == '0') 
        {
            ++start;
        }
        digits = digits.substr(start);
    }

public:
    explicit big_integer(const std::string& num = "0") : is_negative(false)
    {
        if (num.empty())
        {
            throw std::invalid_argument("Empty string is not a valid number");
        }

        size_t start = 0;
        if (num[0] == '-')
        {
            is_negative = true;
            start = 1;
        }
        else if (num[0] == '+')
        {
            start = 1;
        }

        if (start >= num.length())
        {
            throw std::invalid_argument("Sign without digits");
        }

        for (size_t i = start; i < num.length(); ++i)
        {
            if (!is_digit(num[i])) 
            {
                throw std::invalid_argument("Invalid character in number: " + std::string(1, num[i]));
            }
        }

        digits = num.substr(start);
        remove_leading_zeros();

        if (digits == "0") 
        {
            is_negative = false;
        }
    }

    big_integer(big_integer&& other) noexcept
        : digits(std::move(other.digits)), is_negative(other.is_negative)
    {
        other.is_negative = false;
    }

    big_integer& operator=(big_integer&& other) noexcept 
    {
        if (this != &other) 
        {
            digits = std::move(other.digits);
            is_negative = other.is_negative;
            other.is_negative = false;
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const
    {
        if (is_negative != other.is_negative) 
        {
            big_integer temp = other;
            temp.is_negative = !temp.is_negative;
            return *this - temp;
        }

        std::string result;
        std::string num1 = digits;
        std::string num2 = other.digits;

        size_t max_len = std::max(num1.length(), num2.length());
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());

        num1.resize(max_len, '0');
        num2.resize(max_len, '0');

        int carry = 0;
        for (size_t i = 0; i < max_len; ++i) 
        {
            int sum = (num1[i] - '0') + (num2[i] - '0') + carry;
            result.push_back('0' + (sum % 10));
            carry = sum / 10;
        }

        if (carry) 
        {
            result.push_back('0' + carry);
        }

        std::reverse(result.begin(), result.end());

        big_integer res(result);
        res.is_negative = is_negative;
        return res;
    }

    big_integer operator*(int multiplier) const 
    {
        if (multiplier == 0) 
        {
            return big_integer("0");
        }

        bool result_negative = is_negative ^ (multiplier < 0);
        multiplier = std::abs(multiplier);

        std::string result;
        std::string num = digits;
        std::reverse(num.begin(), num.end());

        int carry = 0;
        for (char digit : num) 
        {
            int product = (digit - '0') * multiplier + carry;
            result.push_back('0' + (product % 10));
            carry = product / 10;
        }

        while (carry) 
        {
            result.push_back('0' + (carry % 10));
            carry /= 10;
        }

        std::reverse(result.begin(), result.end());
        big_integer res(result);
        res.is_negative = result_negative;
        res.remove_leading_zeros();
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) 
    {
        if (num.is_negative) 
        {
            os << '-';
        }
        os << num.digits;
        return os;
    }

    big_integer(const big_integer&) = default;

    big_integer& operator=(const big_integer&) = default;
};

int main() 
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl; // 193099

    auto number3 = big_integer("12345");
    auto result2 = number3 * 123;
    std::cout << result2 << std::endl; // 1518435

    return 0;
}