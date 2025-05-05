// =====================================================================================
// ConstExpr.cpp
// =====================================================================================

#include <algorithm>
#include <numeric>
#include <array>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <string_view>
#include <print>

namespace ConstExprComplex {

    class Complex
    {
    private:
        float m_real;
        float m_imag;

    public:
        // c'tors
        constexpr Complex() : m_real{ }, m_imag{ } {}
        constexpr Complex(float real, float imag) 
            : m_real{ real }, m_imag{ imag }
        {
            //std::cin >> m_real;
        }

        // getter
        constexpr float real() const { return m_real; }
        constexpr float imag() const { return m_imag; }

        // operators
        constexpr Complex operator+ (const Complex& other) const
        {
            float real = m_real + other.m_real;
            float imag = m_imag + other.m_imag;
            return { real, imag };
        }
    };

    static void testComplex()
    {
        constexpr Complex c0{ };
        constexpr Complex c1{ 1.0, 2.0 };
        constexpr Complex c2{ 3.0, 3.0 };

        constexpr float r1 = c1.real();
        constexpr Complex c3 = c1 + c2;
        constexpr float r2 = c3.real();

        // verify 'constness' with the help of disassembly and
        // https://www.h-schmidt.net/FloatConverter/IEEE754de.html

        std::println("Real: ", c3.real());
        std::println("Imag: ", c3.imag());

        // verify compile time computing
        static_assert (c1.real() == 1.0, "real part shoud be 1.0");
        static_assert (c3.real() == 4.0, "real part shoud be 4.0");
        static_assert (c3.imag() == 5.0, "imaginary part shoud be 5.0");
    }
}

namespace ConstExprDynamicData {

    static constexpr int naiveSum(unsigned int n)
    {
        auto ip = new int[n];
        std::iota(ip, ip + n, 1);
        auto tmp = std::accumulate(ip, ip + n, 0);
        delete[] ip;
        return tmp;
    }

    static void testDynamicData()
    {
        constexpr int sum = naiveSum(10);  // 1+2+3+4+5 = 15
        std::println("Sum from 1 up to 10: {}", sum);
    }
}

namespace ConstExprPow {

    constexpr size_t TableSize = 5;
    constexpr size_t Factor = 4;

    template<size_t F>
    constexpr auto powerTable = [] {

        std::array<size_t, TableSize> table = {};

        size_t index{ 1 };
        for (size_t& elem : table) {

            size_t tmp{ 1 };
            for (size_t i{}; i != F; ++i) {
                tmp *= index;
            }

            elem = tmp;
            ++index;
        }

        return table;
        } ();

    static constexpr size_t sumUpPowerTable()
    {
        static_assert (powerTable<Factor>[0] == 1, "Value should be ");
        static_assert (powerTable<Factor>[1] == 16, "Value should be ");
        static_assert (powerTable<Factor>[2] == 81, "Value should be ");
        static_assert (powerTable<Factor>[3] == 256, "Value should be ");
        static_assert (powerTable<Factor>[4] == 625, "Value should be ");

        size_t total{};

        for (size_t i{}; i != TableSize; ++i) {
            total += powerTable<Factor>[i];
        }

        return total;
    }

    static void testPower_01()
    {
        constexpr size_t total{ sumUpPowerTable() };
        static_assert (total == 979, "Sum should be 979");
        std::println("Total: ", total);
    }

    static void testPower_02()
    {
        int index = 1;
        for (size_t elem : powerTable<Factor>) {
            std::println("{:02}: {}", index++, elem);
        }

        constexpr size_t total = sumUpPowerTable();
        std::println("Total: {}", total);
    }

    static void testPower()
    {
        testPower_01();
        testPower_02();
    }
}

static void test_11() {

    // IIFE - Immediately Invoked Functional Expression:
    // Inline-definition and direct invocation of lambda funtion:

    std::cout << [](int l, int r) { return l + r; } (11, 12) << std::endl;

    // Use case for IIFE:
    // This kind of expression might be useful when you have
    // a complex initialization of a const  object:

    auto constexpr ConstValue = [] () {
        /* several lines of code ... - "very complex" computation */
        return 123;
        } ();

    std::cout << "Const Value: " << ConstValue << std::endl;
}

void main_constexpr_seminar()
{
    [] {};
    [] () {};

    []() {} ();

    auto l1 = []() {};
    l1();

    auto l2 = [](int n, int m) { return n + m; };
    auto result1 = l2(11, 12);

    constexpr auto l3 = [](int n, int m) { return n + m; };
    constexpr auto result2 = l3(11, 12);
}

void main_constexpr()
{
    ConstExprComplex::testComplex();
    ConstExprDynamicData::testDynamicData();
    ConstExprPow::testPower();
}

// =====================================================================================
// End-of-File
// =====================================================================================