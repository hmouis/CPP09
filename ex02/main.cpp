#include "PmergeMe.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    try
    {
        PmergeMe p;
        p.parseInput(argc, argv);
        std::cout << "Before: ";
        p.printSequence();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}