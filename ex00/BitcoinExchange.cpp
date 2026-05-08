#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(): nob(0){
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other){
    date = other.date;
    nob = other.nob;
    btc = other.btc;
}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other){
    if (this == &other)
        return *this;
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
std::string trim(std::string str, char c) {
    size_t first = str.find_first_not_of(c);
    if (first == std::string::npos) return ""; 
    size_t last = str.find_last_not_of(c);
    return str.substr(first, (last - first + 1));
}

float strtofloat(std::string data){

}

int BitcoinExchange::ParseLine(std::string line)
{
    int count = std::count(line.begin(), line.end(), '|');
    if (count != 1){
        std::cout << "There is no or more than one `|`\n";
        return 1;
    }
    date = trim(strtok((char *)line.c_str(), "|"), ' ');
    count = std::count(date.begin(), date.end(), '-');
    if (count != 2){
        std::cout << "There is one or more than two `-`\n";
        return 1;
    }
    
    
        
}

void BitcoinExchange::ParseFile(std::string file)
{
    std::string line;
    std::ifstream inputfile(file.c_str());
    while (std::getline(inputfile, line)){

    }
}