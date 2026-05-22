#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

class RPN
{
    private:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

    public:
        static int evaluate(const std::string& Input);
};

#endif