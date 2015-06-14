// A basic Reverse Polish Notation (RPN) calculator

#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>

double RPN(std::string expr)
{
    std::stack<double> stck;
    std::stringstream ss{expr};
    std::string token;
    while (ss >> token)
    {
        if (token != "+" && token != "-" && token != "*" && token != "/")
        {
            stck.push(std::stod(token));
        }
        else
        {
            double x = stck.top();
            stck.pop();
            double y = stck.top();
            stck.pop();

            if (token == "+")
                stck.push(y + x);
            else if (token == "-")
                stck.push(y - x);
            else if (token == "*")
                stck.push(y * x);
            else if (token == "/")
                stck.push(y / x);
        }
    }
    if (stck.size() != 1)
        throw std::runtime_error("Invalid expression!");
    return stck.top();
}

int main()
{
    std::string expr = "9 7 + 5 3 - /";
    std::cout << RPN(expr) << std::endl;
}