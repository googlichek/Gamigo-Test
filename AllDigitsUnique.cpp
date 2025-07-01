#include <iostream>
#include <vector>

bool AllDigitsUnique(unsigned int value)
{
    if (value == 0)
    {
        return true;
    }

    std::vector<bool> Seen(10, false);
    while (value > 0)
    {
        const unsigned int Digit = value % 10;
        if (Seen[Digit])
        {
            return false;
        }

        Seen[Digit] = true;
        value /= 10;
    }

    return true;
}

// int main(int argc, char* argv[])
// {
//     unsigned int TestValue1 = 48778584;
//     unsigned int TestValue2 = 17308459;
//
//     std::cout << "Testing AllDigitsUnique():\n";
//     std::cout << TestValue1 << " : " << (AllDigitsUnique(TestValue1) ? "true" : "false") << "\n";
//     std::cout << TestValue2 << " : " << (AllDigitsUnique(TestValue2) ? "true" : "false") << "\n\n";
//
//     std::cout << "Press any key to exit...";
//     std::cin.get();
//
//     return 0;
// }
