#include <iostream>

int main()
{
    int value = 7;

    struct LambdaS1
    {
        LambdaS1(int v) : capturedValue{v}
        {
        }

        int operator() (int x) { return capturedValue * x; }

    private:
        const int capturedValue;
    } lambdaS1{value};

    auto lambdaL1 = [value](int x) { return value * x; };

    std::cout << std::boolalpha << (lambdaS1(10) == lambdaL1(10));

    //================================================================================

    struct LambdaS2
    {
        int operator() (int x) { return 2 * x; }
    } lambdaS2;

    auto lambdaL2 = [](int x) { return 2 * x; };

    std::cout << " " << (lambdaS2(42) == lambdaL2(42)) << '\n';

    //==== c++14 capture initializer example
    auto l3 = [v = 2]() mutable { return v++; };

    std::cout << "l3: " << (l3() == 2) << " " << (l3() == 3) << " " << (l3() == 4) << '\n';
}
