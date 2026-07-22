#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <set>

int Int::counter = 0;
std::ostream& operator<<(std::ostream& out, const Int& n){
    out << n.value;
    return out;
}
bool Int::operator<(const Int &n) {
    counter++;
    return value < n.value;
}

bool PmergeMe::isValidPositiveInteger(const std::string &value, int &number){
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
void PmergeMe::parseInput(int argc, char **argv){
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
        vec.push_back(Int(number));
    }
    seen.clear();
}
void PmergeMe::printSequence(){
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i != 0)
            std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << std::endl;
}
void PmergeMe::createPairs(std::vector<Int>& smalls, std::vector<Int>& main){
    std::vector<Int> bigs;
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
void PmergeMe::indexPairs(std::vector<Int>& smalls, std::vector<Int>& bigs){
    for (int i = 0; i < bigs.size(); i++)
        bigs[i].ids.push_back(i);
    for (int i = 0; i < smalls.size(); i++)
        smalls[i].ids.push_back(i);
}
void PmergeMe::orderTheSmalls(std::vector<Int>& smalls, std::vector<Int>& bigs){
    std::vector<Int> ordered;

    for (int i = 0; i < bigs.size(); i++){
        int index = bigs[i].ids.back();
        if (bigs[i].ids.size() > 1)
            bigs[i].ids.pop_back();
        std::vector<Int>::iterator it;
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
void PmergeMe::mergeInsertSortVect(std::vector<Int>& main){
    std::vector<Int> smalls;
    
    if (main.size() <= 1)
        return ;
    createPairs(smalls, main);
    indexPairs(smalls, main);
    mergeInsertSortVect(main);
    orderTheSmalls(smalls, main);
    insert(smalls, main);

}
std::vector<int> PmergeMe::getJacobsthalSequence(int n){
    std::vector<int> sequence;
    std::vector<int> newsequence;
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
void PmergeMe::insert(std::vector<Int>& smalls, std::vector<Int>& bigs){
    std::vector<int> seq;
    std::vector<Int> main;

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
            std::vector<Int>::iterator it;
            it = std::lower_bound(main.begin(), main.end() - pair, smalls[j].value);
            // std::cout << "Inserting " << smalls[j] << " at position " << std::distance(main.begin(), it) << std::endl;
            main.insert(it, smalls[j]);
            pair++;
        }
        prev = seq[i];
    }
    bigs = main;
}
void PmergeMe::sortVector(int ac, char **av)
{
    parseInput(ac, av);
    std::cout << "Before: ";
    printSequence();
    mergeInsertSortVect(vec);
    std::cout << "After: ";
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << ' ';
    std::cout << '\n';
    std::cout << "comparisons: " << Int::counter << std::endl;
}