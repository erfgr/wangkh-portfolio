#include "polynomial.hpp"
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <cmath>
#include <initializer_list>
//Default constructor
Polynomial::Polynomial()
{
    m_coeffs.push_back(0);
}
//constructor from coefficient vectors (both copy and move versions)
Polynomial::Polynomial(const std::vector<double> & coeffs)
{
    m_coeffs = coeffs;
}
Polynomial::Polynomial(std::vector<double> && coeffs)
{
    m_coeffs = std::move(coeffs);
}
//constructor from initializer list
Polynomial::Polynomial( std::initializer_list<double> coeffs )
{
    m_coeffs = coeffs;
}
//constructor from a path to a p*.txt file of coefficients
Polynomial::Polynomial( const std::string & path )
{
    std::ifstream file(path);
    double coeff;
    while(file >> coeff)
    {
        m_coeffs.push_back(coeff);
    }
}
//copy constructor
Polynomial::Polynomial( const Polynomial & p )
{
    m_coeffs = p.m_coeffs;
}
//move constructor
Polynomial::Polynomial( Polynomial && p ) noexcept
{
    m_coeffs = std::move(p.m_coeffs);
}
//copy and move assignments
Polynomial & Polynomial::operator=(const Polynomial & p)
{
    m_coeffs = p.m_coeffs;
    return *this;
}
Polynomial & Polynomial::operator=(Polynomial && p ) noexcept
{
    m_coeffs = std::move(p.m_coeffs);
    return *this;
}
//destructor
Polynomial::~Polynomial()
{
    m_coeffs.clear();
}
//access to polynomial coefficients
double & Polynomial::operator[](int index)
{
    return m_coeffs[index];
}
const double & Polynomial::operator[](int index) const
{
    return m_coeffs[index];
}
//get number of coefficients (equals degree)
int Polynomial::size() const
{
    return m_coeffs.size();
}
//functional operations (self-explanatory)
Polynomial Polynomial::operator+ (const Polynomial & p) const
{
    Polynomial temp;
    if(m_coeffs.size() > p.m_coeffs.size())
    {
        temp.m_coeffs = m_coeffs;
        for(int i = 0; i < p.m_coeffs.size(); i++)
        {
            temp.m_coeffs[i] += p.m_coeffs[i];
        }
    }
    else
    {
        temp.m_coeffs = p.m_coeffs;
        for(int i = 0; i < m_coeffs.size(); i++)
        {
            temp.m_coeffs[i] += m_coeffs[i];
        }
    }
    return temp;
}
Polynomial & Polynomial::operator+=(const Polynomial & p)
{
    *this = *this + p;
    return *this;
}
Polynomial Polynomial::operator- (const Polynomial & p) const
{
    Polynomial temp;
    if(m_coeffs.size() > p.m_coeffs.size())
    {
        temp.m_coeffs = m_coeffs;
        for(int i = 0; i < p.m_coeffs.size(); i++)
        {
            temp.m_coeffs[i] -= p.m_coeffs[i];
        }
    }
    else
    {
        temp.m_coeffs = p.m_coeffs;
        for(int i = 0; i < m_coeffs.size(); i++)
        {
            temp.m_coeffs[i] -= m_coeffs[i];
        }
        for(int i = 0; i < temp.m_coeffs.size(); i++)
        {
            temp.m_coeffs[i] = -temp.m_coeffs[i];
        }
    }
    return temp;
}
Polynomial & Polynomial::operator-=(const Polynomial & p)
{
    *this = *this - p;
    return *this;
}
Polynomial Polynomial::operator* (const Polynomial & p) const
{
    Polynomial temp;
    for(int i = 0; i < m_coeffs.size(); i++)
    {
        for(int j = 0; j < p.m_coeffs.size(); j++)
        {
            if(i+j < temp.m_coeffs.size())
            {
                temp.m_coeffs[i+j] += m_coeffs[i] * p.m_coeffs[j];
            }
            else
            {
                temp.m_coeffs.push_back(m_coeffs[i] * p.m_coeffs[j]);
            }
        }
    }
    return temp;
}
Polynomial & Polynomial::operator*=(const Polynomial & p)
{
    *this = *this * p;
    return *this;
}
Polynomial Polynomial::operator* (double d) const
{
    Polynomial temp;
    for(int i = 0; i < m_coeffs.size(); i++)
    {
        if(i < temp.m_coeffs.size())
        {
            temp.m_coeffs[i] = m_coeffs[i] * d;
        }
        else
        {
            temp.m_coeffs.push_back(m_coeffs[i] * d);
        }
    }
    return temp;
}
//function (polynomial) evaluation
double Polynomial::operator()(double x) const
{
    double result = 0;
    for(int i = 0; i < m_coeffs.size(); i++)
    {
        result += m_coeffs[i] * pow(x, i);
    }
    return result;
}



