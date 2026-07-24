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
        throw std::runtime_error("Error: could not open file.");
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
    if (first == std::string::npos) 
        return ""; 
    size_t last = str.find_last_not_of(c);
    return str.substr(first, (last - first + 1));
}

int BitcoinExchange::ValidDate(float y, float m, float d)
{
    if (y < 2009 || (double)y > 2147483647){
        std::cout << "Error: Invalid date => " << date << std::endl;
        return 1;
    }
    if (m < 1 || m > 12){
        std::cout << "Error: Invalid date => " << date << std::endl;
        return 1;
    }
    if (y == 2009 && m == 1 && d < 2){
        std::cout << "Error: Invalid date => " << date << std::endl;
        return 1;       
    }
    if ((m == 2 && (d < 1 || d > 28)) || ((m == 4 || m == 6 || m == 9 || m == 11) && (d < 1 || d > 30)) || (d < 1 || d > 31)){
        std::cout << "Error: Invalid date => " << date << std::endl;
        return 1;
    }
    return 0;
}
int BitcoinExchange::ValidNumberOfBitcoin(std::string _nob){
    if (_nob.empty()){
        std::cout << "Error: Bad Number of bitcoin => " << _nob << std::endl;
        return 1;
    }
    char *endptr;
    nob = strtof(_nob.c_str(), &endptr);
    if (*endptr){
        std::cout << "Error: Bad Number of bitcoin => " << _nob << std::endl;
        return 1;
    }
    if (nob > 1000){
        std::cout << "Error: Too large number" << std::endl;
        return 1;
    }
    else if (nob < 0){
        std::cout << "Error: Not a positive number" << std::endl;
        return 1;
    }

    return 0;
}

int BitcoinExchange::ParseLine(std::string line)
{
    float y, m, d;
    char d1, d2, d3;

    int count = std::count(line.begin(), line.end(), '|');
    if (count != 1){
        std::cout << "Error: Bad input => " << line << std::endl;
        return 1;
    }
    if (*line.rbegin() == '|'){
        std::cout << "Error: Bad input => " << line << std::endl;
        return 1;
    }
    std::stringstream s(line);
    if (s >> y >> d1 >> m >> d2 >> d >> d3){
        if (d1 != '-' || d2 != '-' || d3 != '|'){
            std::cout << "Error: Bad input => " << line << std::endl;
            return 1;
        }
    }
    else{
        std::cout << "Error: Bad input => " << line << std::endl;
        return 1;
    }
    date = trim(strtok((char *)line.c_str(), "|"), ' ');
    if (date.length() != 10){
        std::cout << "Error: Bad input => " << date << std::endl;
        return 1;
    }
    if (ValidDate(y, m, d)) 
        return 1;
    if (ValidNumberOfBitcoin(trim(strtok(NULL, "|"), ' ')))
        return 1;
    return 0;
}

void BitcoinExchange::ParseFile(std::string file)
{
    std::string line;
    std::ifstream inputfile(file.c_str());
    if (!inputfile.is_open())
        throw std::runtime_error("Error: Can't open the file");
    while (std::getline(inputfile, line)){
        if (line == "date | value")
            continue;
        if (ParseLine(line))
            continue;
        std::map<std::string, float>::iterator it;
        it = btc.upper_bound(date);
        if (it != btc.begin())
            it--;
        std::cout << date << " => " << nob << " = " << it->second * nob << std::endl;
    }
}