#include "Deque.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <set>

int IntDe::deqcounter = 0;
std::ostream& operator<<(std::ostream& out, const IntDe& n){
    out << n.value;
    return out;
}
bool IntDe::operator<(const IntDe &n) {
    deqcounter++;
    return value < n.value;
}

Deque::Deque(){}

Deque::Deque(const Deque& other)
{
    *this = other;
}

Deque& Deque::operator=(const Deque& other)
{
    if (this != &other)
        deq = other.deq;
    return *this;
}

Deque::~Deque(){}

bool Deque::isValidPositiveInteger(const std::string &value, int &number){
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
void Deque::parseInput(int argc, char **argv){
    std::set<int> seen;
    if (argc < 2)
        throw std::runtime_error("Error, No arguments");
    for (int i = 1; i < argc; ++i)
    {
        int number = 0;
        if (!isValidPositiveInteger(argv[i], number))
            throw std::runtime_error("Error, Invalid positive integer");
        if (seen.count(number))
            throw std::runtime_error("Error, Duplicate");
        seen.insert(number);
        deq.push_back(IntDe(number));
    }
    seen.clear();
}
void Deque::printSequence(){
    for (size_t i = 0; i < deq.size(); ++i)
    {
        if (i != 0)
            std::cout << ' ';
        std::cout << deq[i];
    }
    std::cout << std::endl;
}
void Deque::createPairs(std::deque<IntDe>& smalls, std::deque<IntDe>& main){
    std::deque<IntDe> bigs;
    int strag = 0;
    if (main.size() % 2)
        strag = 1;
    for (int i = 0; i < main.size(); i += 2){
        if (i == main.size() - 1)
            break;
        if (main[i] < main[i + 1]){
            bigs.push_back(main[i + 1]);
            smalls.push_back(main[i]);
        }
        else{
            bigs.push_back(main[i]);
            smalls.push_back(main[i + 1]);
        }
    }
    if (strag)
        smalls.push_back(*(main.rbegin()));
    main = bigs;
}
void Deque::indexPairs(std::deque<IntDe>& smalls, std::deque<IntDe>& bigs){
    for (int i = 0; i < bigs.size(); i++)
        bigs[i].ids.push_back(i);
    for (int i = 0; i < smalls.size(); i++)
        smalls[i].ids.push_back(i);
}
void Deque::orderTheSmalls(std::deque<IntDe>& smalls, std::deque<IntDe>& bigs){
    std::deque<IntDe> ordered;

    for (int i = 0; i < bigs.size(); i++){
        int index = bigs[i].ids.back();
        if (bigs[i].ids.size() > 1)
            bigs[i].ids.pop_back();
        std::deque<IntDe>::iterator it;
        for (it = smalls.begin(); it != smalls.end(); it++){
            if (it->ids.back() == index)
                break;
        }
        ordered.push_back(*it);
        if (ordered.back().ids.size() > 1)
            ordered.back().ids.pop_back();
        smalls.erase(it);
    }
    if (smalls.size() == 1){
        ordered.push_back(smalls.back());
        if (ordered.back().ids.size() > 1)
            ordered.back().ids.pop_back();
    }
    smalls.clear();
    smalls = ordered;
}
void Deque::mergeInsertSortDeque(std::deque<IntDe>& main){
    std::deque<IntDe> smalls;
    
    if (main.size() <= 1)
        return ;
    createPairs(smalls, main);
    indexPairs(smalls, main);
    mergeInsertSortDeque(main);
    orderTheSmalls(smalls, main);
    insert(smalls, main);

}
std::deque<int> Deque::getJacobsthalSequence(int n){
    std::deque<int> sequence;
    std::deque<int> newsequence;
    if (n <= 1){
        sequence.push_back(n);
        return sequence;
    }
    sequence.push_back(0);
    sequence.push_back(1);
    while (true){
        int next = sequence[sequence.size() - 1] + 2 * sequence[sequence.size() - 2];
        sequence.push_back(next);
        if (next >= n)
            break;
    }

    for (int i = 2; i < sequence.size(); ++i)
        newsequence.push_back(sequence[i]);
    return newsequence;
}
void Deque::insert(std::deque<IntDe>& smalls, std::deque<IntDe>& bigs){
    std::deque<int> seq;
    std::deque<IntDe> main;

    seq = getJacobsthalSequence(bigs.size());
    main.push_back(smalls[0]);
    int prev = 0;
    for (int i = 0; i < seq.size(); i++)
    {
        int curr_seq = seq[i];
        for (int j = prev; j < curr_seq && j < bigs.size(); j++)
            main.push_back(bigs[j]);

        if (curr_seq >= smalls.size())
            curr_seq = smalls.size() - 1;
        int pair = 0;
        for (int j = curr_seq; j > prev; j--)
        {
            std::deque<IntDe>::iterator it;
            it = std::lower_bound(main.begin(), main.end() - pair, smalls[j].value);
            main.insert(it, smalls[j]);
            pair++;
        }
        prev = seq[i];
    }
    bigs = main;
}
void Deque::sortDeque(int ac, char **av)
{
    parseInput(ac, av);
    struct timeval start, end;
    gettimeofday(&start, NULL);
    mergeInsertSortDeque(deq);
    gettimeofday(&end, NULL);
    double time = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << std::fixed << std::setprecision(3) << time << " us" << std::endl;
}