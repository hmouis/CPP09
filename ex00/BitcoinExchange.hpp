#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <map>

class BitcoinExchange
{
    private:
        std::string date;
        float nob;
        std::map<std::string, float> btc;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void FillMap();
        void ParseFile(std::string file);
        int ParseLine(std::string line);

};


#endif