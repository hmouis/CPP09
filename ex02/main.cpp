#include "PmergeMe.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    try
    {
        std::vector<int> numbers = PmergeMe::parseInput(argc, argv);
        std::cout << "Before: ";
        PmergeMe::printSequence(numbers);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}