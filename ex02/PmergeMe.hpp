#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>

class PmergeMe
{
    private:
        bool isValidPositiveInteger(const std::string &value, int &number);
        std::vector<int> numbers;

    public:
        void parseInput(int argc, char **argv);
        void printSequence();
};

#endif