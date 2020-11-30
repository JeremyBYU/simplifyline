#include "doctest/doctest.h"
#include "SimplifyLine/SimplifyLine.hpp"
#include <vector>

template <typename T>
int CheckArray(std::vector<T>& a, std::vector<T>& b)
{
    for (size_t i = 0; i < a.size(); i++)
    {
        auto result = a[i] == doctest::Approx(b[i]);
        if (!result) return static_cast<int>(i);
    }
    return -1;
}

TEST_SUITE("VectorMath")
{
    TEST_CASE("Doubles")
    {
        std::vector<double> input{0.0, 1.0, 2.0};
        std::vector<double> expected{0.0, 2.0, 4.0};
        double scalar = 2.0;
        auto output = SimplifyLine::MultiplyByScalar(input, scalar);

        SUBCASE("SameLength") { CHECK_EQ(output.size(), output.size()); }
        SUBCASE("CorrectOuput")
        {
            auto val = CheckArray(output, expected);
            CHECK_MESSAGE(val == -1, "Vectors are not equal");
        }
    }
}

TEST_SUITE("Hello")
{
    TEST_CASE("Name")
    {
        std::string input = "Jeremy";
        std::string output = SimplifyLine::Hello(input);
        std::string expected = "Hello Jeremy";
        CHECK_EQ(output, expected);
    }
}
