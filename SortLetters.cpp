#include <iostream>
#include <string>
#include <vector>

std::string SortLetters(const std::string& Input, const std::string& SortOrder)
{
    std::vector<int> Count(256, 0);
    for (char Character : Input)
    {
        Count[static_cast<unsigned char>(Character)]++;
    }

    std::string Result;
    for (char Character : SortOrder)
    {
        unsigned char Index = static_cast<unsigned char>(Character);
        Result.append(Count[Index], Character);
        Count[Index] = 0;
    }

    for (int i = 0; i < 256; ++i)
    {
        if (Count[i] > 0)
        {
            Result.append(Count[i], static_cast<char>(i));
        }
    }

    return Result;
}

// int main(int argc, char* argv[])
// {
//     std::string InputString = "trion world network";
//     std::string SortOrderString = " oinewkrtdl";
//
//     std::string ResultString = SortLetters(InputString, SortOrderString);
//     std::string ResultVerificationString = "  oooinnewwkrrrttdl";
//
//     std::cout << "Testing SortLetters():\n";
//     std::cout << "Input: \"" << InputString << "\"\n";
//     std::cout << "Sort Order: \"" << SortOrderString << "\"\n";
//     std::cout << "Result: \"" << ResultString << "\"\n";
//     std::cout << "Expected: \"" << ResultVerificationString << "\"\n";
//
//     if (ResultString == ResultVerificationString)
//     {
//         std::cout << "PASSED!\n";
//     }
//     else
//     {
//         std::cout << "FAILED!\n";
//     }
//
//     std::cout << "\nPress any key to exit...";
//     std::cin.get();
//
//     return 0;
// }
