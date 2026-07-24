#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>
#include <sys/time.h>

struct Int{
    Int(int value);
    static int counter;
    int value;
    std::vector<int> ids;
    bool operator<(const Int &n);
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
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void sortVector(int ac, char **av);

};

#endif
