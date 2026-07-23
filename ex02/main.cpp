#include "PmergeMe.hpp"
#include "Deque.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char **argv)
{
    try
    {
        PmergeMe s;
        s.sortVector(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    try
    {
        Deque s;
        s.sortDeque(argc, argv);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}