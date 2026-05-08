#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(): sep(0), nob(0){
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    sep = other.sep;
    date = other.date;
    nob = other.nob;
    btc = other.btc;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if (this == &other)
        return *this;
    sep = other.sep;
    date = other.date;
    nob = other.nob;
    btc = other.btc;
    return *this;
}
BitcoinExchange::~BitcoinExchange(){};

void BitcoinExchange::FillMap(){
    std::string line;

    std::ifstream file("data.csv");
    if (!file.is_open())
        throw std::runtime_error("Can't open the file");
    std::getline(file, line);
    while (std::getline(file, line)){
        std::string key = strtok((char *)line.c_str(), ",");
        float val = strtof(strtok(NULL, ","), NULL);
        btc[key] = val;
    }
    file.close();
}
