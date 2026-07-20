#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>

struct Int{
    Int(int value): value(value) {}
    int value;
    std::vector<int> ids;
    bool operator<(const Int &n) const;
};
std::ostream& operator<<(std::ostream& out, const Int& n);

class PmergeMe
{
    private:
        bool isValidPositiveInteger(const std::string &value, int &number);
        std::vector<Int> vec;
        void parseInput(int argc, char **argv);
        void printSequence();
        void mergeInsertSortVect(std::vector<Int> &main);
        void createPairs(std::vector<Int>& smalls, std::vector<Int>& main);
        void indexPairs(std::vector<Int>& smalls, std::vector<Int>& bigs);
        void insert(std::vector<Int>& smalls, std::vector<Int>& bigs);
        void orderTheSmalls(std::vector<Int>& smalls, std::vector<Int>& main);
        std::vector<int> getJacobsthalSequence(int n);


    public:
        void sortVector(int ac, char **av);

};

#endif
