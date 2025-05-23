// =====================================================================================
// StringView.cpp // Klasse std::string_view
// =====================================================================================


#include <string>
#include <string_view>
#include <print>

static std::string_view sv = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";

namespace StringViewDemonstration {

    static void test_01()
    {
        const char* cp = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
       // cp[0] = '!';

        std::string_view sv = "AAAAAAAAAAAAAAAAAAAAAAAAAAAA";  // Konstante Zeichenkette

        std::string s{ "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" };        //  Heap

       // sv[0] = '?';   // error
        char ch{ sv[0] };
    }

    static void test_02()
    {
        std::string s{ "AAAAAAAAAAAAAAAAAAAAAAAAAAAA" };

        const char* ptr = s.data();  // L�nge
        size_t size = s.size();      
        // genau das steht in std::string_view drin + Klasse + OO + lesende Methoden.

        std::string_view sv{ s };

        std::println("{}", sv);

        s += "BBBBBBBBBBBBBBBBBBBBBBBBBBBB";  // the content of s is reallocated !

        std::println("{}", sv);
    }

    static void test_03()
    {
        using namespace std::literals;      // easiest way to access the s and sv suffixes

        std::println("{}", "foo");         // no suffix: C-style string literal
        std::println("{}", "goo"s);        // s suffix:  std::string literal
        std::println("{}", "moo"sv);       // sv suffix: std::string_view literal
    }

    static size_t countUpperCaseChars(std::string_view sv) {

        size_t result{};

        for (char c : sv) {
            if (std::isupper(c)) {
                ++result;
            }
        }

        return result;
    }

    static void test_04()
    {
        std::string_view sv{ "DiesIstEinLangerSatz" };
        size_t count{ countUpperCaseChars(sv) };
        std::println("countUpperCaseChars: {}", count);

        std::string s{ "AuchDasWiederIstEinLangerSatz" };
        count = countUpperCaseChars(s);
        std::println("countUpperCaseChars: {}", count);

        count = countUpperCaseChars("NurKurzJetzt");
        std::println("countUpperCaseChars: {}", count);

        // works too 
        count = countUpperCaseChars({ &s[25] }); // "Satz"
        std::println("countUpperCaseChars: {}", count);

        // works too
        count = countUpperCaseChars({ &s[26], 2 }); // "at"
        std::println("countUpperCaseChars: {}", count);
    }
}

void main_string_view()
{
    using namespace StringViewDemonstration;
    test_01();
    test_02();
    test_03();
    test_04();
}

// =====================================================================================
// End-of-File
// =====================================================================================