#include "polynomial_parser.hpp"
#include <string>
#include <map>
#include <functional>
#include <stack>
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctype.h>
#include <initializer_list>
#include <vector>
Polynomial PolynomialParser::compute_polynomial(const std::string& expression, std::map<std::string, Polynomial>& polys)
{
    std::stack<Polynomial> nums;
    std::stringstream ss(expression);
    while(!ss.eof())
    {
        std::string token;
        ss >> token;
        if(isdigit(token[0]))
        {
            nums.push(Polynomial(token));
        }
        else
        {
            if(token == "+")
            {
                Polynomial p1 = nums.top();
                nums.pop();
                Polynomial p2 = nums.top();
                nums.pop();
                nums.push(p1 + p2);
            }
            else if(token == "-")
            {
                Polynomial p1 = nums.top();
                nums.pop();
                Polynomial p2 = nums.top();
                nums.pop();
                nums.push(p2 - p1);
            }
            else if(token == "*")
            {
                Polynomial p1 = nums.top();
                nums.pop();
                Polynomial p2 = nums.top();
                nums.pop();
                nums.push(p1 * p2);
            }
            else
            {
                Polynomial p = polys[token];
                nums.push(p);
            }
        }
    }
    return nums.top();
}

typedef std::function<double(double)> scalarFct;


scalarFct PolynomialParser::compute_lambda(const std::string& expression, std::map<std::string, Polynomial>& polys)
{
    Polynomial p = compute_polynomial(expression, polys);
    scalarFct fct = [p](double x)
    {
        double result = 0;
        for(int i = 0; i < p.size(); i++)
        {
            result += p[i] * pow(x, i);
        }
        return result;
    };
    return fct;
}