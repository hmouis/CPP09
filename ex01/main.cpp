#include "RPN.hpp"

#include <iostream>
#include <stdexcept>

int main(int argc, char** argv)
{
    try
    {
        if (argc != 2)
            throw std::runtime_error("Error");

        std::cout << RPN::evaluate(argv[1]) << std::endl;
    }
    catch (const std::exception&)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    return 0;
}