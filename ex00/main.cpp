#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{


    if (ac != 2){
        std::cout << "Error: Invalid number of arguments\n";
        return 1;
    }
    try{
        
        BitcoinExchange b;
        b.FillMap();
        b.ParseFile(av[1]);
    }
    catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }


    return 0;
}