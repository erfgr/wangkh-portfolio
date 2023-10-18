#include <iostream>
#include <cmath>
// DO NOT MODIFY THE CODE BELOW
#include <cstddef>

class Array {
public:
    Array();
    explicit Array(std::size_t n);
    explicit Array(int *begin, int *end);
    Array(const Array &other);
    Array &operator=(const Array &other);
    ~Array();
    int &at(std::size_t n);
    const int &at(std::size_t n) const;
    std::size_t size() const;
    bool empty() const;
    void clear();
    Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;
private:
    std::size_t m_size;
    int *m_data;
};

// YOUR CODE STARTS HERE
Array::Array()
{
    m_size = 0;
    m_data =NULL;
}

Array::Array(std::size_t n)
{
    m_size = n;
    m_data = new int[n];
    for (int i = 0; i < n; i++)
    {
        m_data[i] = 0;
    }
}

Array::Array(int *begin, int *end)
{
    m_size = end - begin;
    m_data = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = begin[i];
    }
}

Array::Array(const Array &other)
{
    m_size = other.m_size;
    m_data = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }
}

Array &Array::operator=(const Array &other)
{
    if (this != &other)
    {
        delete[] m_data;
        m_size = other.m_size;
        m_data = new int[m_size];
        for (int i = 0; i < m_size; i++)
        {
            m_data[i] = other.m_data[i];
        }    
    }
    return *this;
}

Array::~Array()
{
    delete[] m_data;
}

int &Array::at(std::size_t n)
//int &at(std::size_t n);
{
    return m_data[n];
}

const int &Array::at(std::size_t n) const
// const int &at(std::size_t n) const;
{
    return m_data[n];
}

std::size_t Array::size() const
{
    return m_size;
}

bool Array::empty() const
{
    return m_size == 0;
}

void Array::clear()
{
    delete[] m_data;
    m_size = 0;
    m_data = NULL;
}

Array Array::slice(std::size_t l, std::size_t r,std::size_t s) const
{
    Array temp;
    int size=0;
    if (l < r && r <= m_size)
    {
        for (int i=l;i<r;i+=s)
        {
            size++;
        }
        temp.m_size = size;
        temp.m_data = new int[temp.m_size];
        for (int i = 0; i < temp.m_size; i++)
        {
            temp.m_data[i] = m_data[l + i * s];
        }
    }
    if (l >= r||r > m_size||l > m_size)
    {
        delete[] temp.m_data;
        temp.m_size = 0;
        temp.m_data =NULL;
    }
    return temp;
}

// YOUR CODE ENDS HERE

int main() {
    // You can test your implementation here, but we will replace the main function on OJ.
    int a[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    Array arr(a, a + 10);
    Array arr2 = arr.slice(2, 5, 2);
    std::cout<<arr2.size()<<std::endl;
    std::cout<<"3232"<<std::endl;
    std::cout<<arr2.at(0)<<std::endl;
    std::cout<<arr2.at(1)<<std::endl;
    return 0;
}