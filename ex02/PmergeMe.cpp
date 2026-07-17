#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <set>

bool PmergeMe::isValidPositiveInteger(const std::string &value, int &number)
{
    if (value.empty())
        return false;
    for (size_t i = 0; i < value.size(); ++i){
        if (!std::isdigit(value[i]))
            return false;
    }
    errno = 0;
    long parsed = std::strtol(value.c_str(), NULL, 10);
    if (errno != 0 || parsed < 0 || parsed > INT_MAX)
        return false;
    number = static_cast<int>(parsed);
    return true;
}

void PmergeMe::parseInput(int argc, char **argv)
{
    std::set<int> seen;
    if (argc < 2)
        throw std::runtime_error("Error");
    for (int i = 1; i < argc; ++i)
    {
        int number = 0;
        if (!isValidPositiveInteger(argv[i], number))
            throw std::runtime_error("Error");
        if (seen.count(number))
            throw std::runtime_error("Error");
        seen.insert(number);
        numbers.push_back(number);
    }
}

void PmergeMe::printSequence()
{
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        if (i != 0)
            std::cout << ' ';
        std::cout << numbers[i];
    }
    std::cout << std::endl;
}