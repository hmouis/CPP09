#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp

#include <iostream>
#include <iterator>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <sstream>
#include <cerrno>
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
        int ValidDate(float y, float m, float d);
        int ValidNumberOfBitcoin(std::string _nob);
        void ParseFile(std::string file);
        int ParseLine(std::string line);

};


#endif