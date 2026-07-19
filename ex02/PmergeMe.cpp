#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <set>

std::ostream& operator<<(std::ostream& out, const Int& n){
    out << n.value;
    return out;
}
bool Int::operator<(const Int &n) const{
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
    for (int i = 0; i < bigs.size(); i++)
        smalls[i].ids.push_back(i);
}
void PmergeMe::mergeInsertSortVect(std::vector<Int>& main){
    std::vector<Int> smalls;
    
    if (main.size() <= 1)
        return ;
    createPairs(smalls, main);
    indexPairs(smalls, main);
    mergeInsertSortVect(main);

    insert(smalls, main);

}
void PmergeMe::insert(std::vector<Int>& smalls, std::vector<Int>& bigs){
    
}
void PmergeMe::sortVector(int ac, char **av)
{
    parseInput(ac, av);
    std::cout << "Before: ";
    printSequence();
    std::cout << "After: ";
    mergeInsertSortVect(vec);
    for (int i = 0; i < vec.size(); i++)
        std::cout << ' ' << vec[i];
    std::cout << '\n';
}