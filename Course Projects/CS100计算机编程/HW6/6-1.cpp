#include <cstddef>
#include <iostream>
#include <cmath>

class Matrix {
public:
    typedef double Scalar;
    typedef std::size_t Index;

    explicit Matrix(Index rows, Index cols);
    Matrix(const Matrix &other);
    Matrix& operator=(const Matrix &other);
    ~Matrix();
    Index rows() const;
    Index cols() const;
    Scalar& at(Index r, Index c);
    const Scalar& at(Index r, Index c) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix transpose() const;
    Matrix block(Index r, Index c, Index p, Index q) const; // Block of size p x q, starting at (r,c)
    Scalar trace() const; // For square matrix
    Scalar determinant() const; // For square matrix

private:
    // Define your private member variables and functions here
    Index m_rows;
    Index m_cols;
    Scalar *m_data;
};

Matrix::Matrix(Index rows, Index cols)
{
    //Create a matrix of size rows×cols and set all the elements to 0.
    m_rows = rows;
    m_cols = cols;
    m_data = new Scalar[rows*cols];
    for (int i = 0; i < rows*cols; i++)
    {
        m_data[i] = 0;
    }
}

Matrix::Matrix(const Matrix &other)
{
    //Copy constructor: Copy all elements from the other Matrix instance.
    m_rows = other.m_rows;
    m_cols = other.m_cols;
    m_data = new Scalar[m_rows*m_cols];
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        m_data[i] = other.m_data[i];
    }
}

Matrix& Matrix::operator=(const Matrix &other)
{
    //Assignment operator: Copy all elements from the other Matrix instance.
    if (this != &other)
    {
        delete[] m_data;
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = new Scalar[m_rows*m_cols];
        for (int i = 0; i < m_rows*m_cols; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }
    return *this;
}

Matrix::~Matrix()
{
    //Destructor: Delete all dynamically allocated memory.
    delete[] m_data;
}   

Matrix::Index Matrix::rows() const
{
    //Return the number of rows.
    return m_rows;
}

Matrix::Index Matrix::cols() const
{
    //Return the number of columns.
    return m_cols;
}

double &Matrix::at(Index r, Index c)
{
    return m_data[r*m_cols+c];
}

const double &Matrix::at(Index r, Index c) const
{
    return m_data[r*m_cols+c];
}

Matrix Matrix::operator+(const Matrix &other) const
{
    //Return the sum of this Matrix and the other Matrix.
    Matrix result(m_rows, m_cols);
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        result.m_data[i] = m_data[i] + other.m_data[i];
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    //Return the difference of this Matrix and the other Matrix.
    Matrix result(m_rows, m_cols);
    for (int i = 0; i < m_rows*m_cols; i++)
    {
        result.m_data[i] = m_data[i] - other.m_data[i];
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    //Return the product of this Matrix and the other Matrix.
    Matrix result(m_rows, other.m_cols);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < other.m_cols; j++)
        {
            result.m_data[i*other.m_cols + j] = 0;
            for (int k = 0; k < m_cols; k++)
            {
                result.m_data[i*other.m_cols + j] += m_data[i*m_cols + k] * other.m_data[k*other.m_cols + j];
            }
        }
    }
    return result;
}

Matrix Matrix::transpose() const
{
    //Return the transpose of this Matrix.
    Matrix result(m_cols, m_rows);
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            result.m_data[j*m_rows + i] = m_data[i*m_cols + j];
        }
    }
    return result;
}

Matrix Matrix::block(Index r, Index c, Index p, Index q) const
{
    //Return the block of size p x q, starting at (r,c).
    Matrix result(p, q);
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < q; j++)
        {
            result.m_data[i*q + j] = m_data[(r+i)*m_cols + (c+j)];
        }
    }
    return result;
}

Matrix::Scalar Matrix::trace() const
{
    //Return the trace of this Matrix.
    Scalar result = 0;
    for (int i = 0; i < m_rows; i++)
    {
        result += m_data[i*m_cols + i];
    }
    return result;
}

Matrix::Scalar Matrix::determinant() const
{
    //Return the determinant of this Matrix.
    Scalar result = 0;
    if(this->rows() == 1)return this->at(0,0);
    else if(this->rows() == 2)return this->at(0,0)*this->at(1,1) - this->at(0,1)*this->at(1,0);
    else{
        for(int i = 0; i < m_rows; i++){
            Matrix A(m_rows-1, m_cols-1);
            for(int j=0; j<m_rows-1; j++)
                for(int k=0; k<m_cols-1; k++){
                    int x=0;
                    if(k>=i)x=1;
                    A.at(j,k) = (*this).at(j+1,k+x);
                }
            if(i%2==0)result += this->at(0,i)*A.determinant();
            else result -= this->at(0,i)*A.determinant();
        }
    }
    return result;
}

int main(){
    //测试样例
    Matrix A(3,3);
    A.at(0,0) = 1;
    A.at(0,1) = 1;
    A.at(0,2) = 2;
    A.at(1,0) = 2;
    A.at(1,1) = 2;
    A.at(1,2) = 1;
    A.at(2,0) = 3;
    A.at(2,1) = 1;
    A.at(2,2) = 2;

    //求行列式
    std::cout << A.determinant() << std::endl;
}
