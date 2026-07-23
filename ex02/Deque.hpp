#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <string>
#include <deque>
#include <sys/time.h>

struct IntDe{
    IntDe(int value): value(value) {}
    static int deqcounter;
    int value;
    std::deque<int> ids;
    bool operator<(const IntDe &n);
};
std::ostream& operator<<(std::ostream& out, const IntDe& n);

class Deque
{
    private:
        bool isValidPositiveInteger(const std::string &value, int &number);
        std::deque<IntDe> deq;
        void parseInput(int argc, char **argv);
        void printSequence();
        void mergeInsertSortDeque(std::deque<IntDe> &main);
        void createPairs(std::deque<IntDe>& smalls, std::deque<IntDe>& main);
        void indexPairs(std::deque<IntDe>& smalls, std::deque<IntDe>& bigs);
        void insert(std::deque<IntDe>& smalls, std::deque<IntDe>& bigs);
        void orderTheSmalls(std::deque<IntDe>& smalls, std::deque<IntDe>& main);
        std::deque<int> getJacobsthalSequence(int n);


    public:
        void sortDeque(int ac, char **av);

};

#endif
