#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>

class PmergeMe
{
    private:
        static bool isValidPositiveInteger(const std::string &value, int &number);

    public:
        static std::vector<int> parseInput(int argc, char **argv);
        static void printSequence(const std::vector<int> &sequence);
};

#endif