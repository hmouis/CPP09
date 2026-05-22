#include "RPN.hpp"

#include <cctype>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

bool isOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}
int applyOperator(const std::string& token, int left, int right)
{
    if (token == "+")
        return left + right;
    if (token == "-")
        return left - right;
    if (token == "*")
        return left * right;
    if (right == 0)
        throw std::runtime_error("Error");
    return left / right;
}

RPN::RPN() {}
RPN::RPN(const RPN& other) { (void)other; }
RPN& RPN::operator=(const RPN& other) { (void)other; return *this; }
RPN::~RPN() {}

int RPN::evaluate(const std::string& Input)
{
    std::stack<int> values;
    std::istringstream stream(Input);
    std::string token;

    while (stream >> token)
    {
        if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
            values.push(token[0] - '0');
        else if (isOperator(token))
        {
            if (values.size() < 2)
                throw std::runtime_error("Error");
            int right = values.top();
            values.pop();
            int left = values.top();
            values.pop();
            values.push(applyOperator(token, left, right));
        }
        else
            throw std::runtime_error("Error");
    }

    if (values.size() != 1)
        throw std::runtime_error("Error");

    return values.top();
}