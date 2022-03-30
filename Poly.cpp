#include "Poly.h"

Poly::Poly()
{
    this->size = 1;
    coeffPtr = new int[this->size];
    coeffPtr[0] = 0;
}

Poly::Poly(int coeff)
{
    this->size = 1;
    coeffPtr = new int[this->size];
    coeffPtr[0] = coeff;
}

Poly::Poly(const int coeff, const int power)
{
    this->size = power + 1;
    coeffPtr = new int[this->size];

    for (int i = 0; i < this->size; i++) 
    {
        coeffPtr[i] = 0;
    }
    coeffPtr[power] = coeff;
}

Poly::Poly(const Poly &input)
{
    this->size = input.size;
    coeffPtr = new int[size];

    for (int i = 0; i < this->size; i++) 
    {
        coeffPtr[i] = input.coeffPtr[i];
    }
}

Poly::~Poly() 
{
    delete[] coeffPtr;
    coeffPtr = NULL;
}

int Poly::getCoeff(const int power) const 
{
    if (power >= 0 && power < this->size) 
    {
        return coeffPtr[power];
    } 
    else 
    {
        return 0;
    }
}

void Poly::setCoeff(const int coeff, const int power)
{
    if (power >= 0) 
    {
        if (power < this->size) 
        {
            coeffPtr[power] = coeff;
        } 
        else 
        {
            int *temp = new int[power + 1];
            for (int i = 0; i < this->size; i++) 
            {
                temp[i] = coeffPtr[i];
            }
            for (int j = this->size; j < power + 1; j++) 
            {
                temp[j] = 0;
            }
            temp[power] = coeff;

            delete[] coeffPtr;
            coeffPtr = NULL;
            coeffPtr = temp;
            temp = NULL;
            this->size = power + 1;
        }
    }
}

Poly Poly::operator+(const Poly &other) const
{
    if (other.size > this->size) 
    {
        Poly sum(0, other.size);

        for (int i = 0; i < other.size; i++) 
        {
            sum.coeffPtr[i] = other.coeffPtr[i];
        }

        for (int i = 0; i < this->size; i++) 
        {
            sum.coeffPtr[i] += this->coeffPtr[i];
        }
        return sum;
    } 
    else 
    {
        Poly sum(0, this->size);

        for (int i = 0; i < this->size; i++) 
        {
            sum.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int i = 0; i < other.size; i++) 
        {
            sum.coeffPtr[i] += other.coeffPtr[i];
        }
        return sum;
    }
}

Poly Poly::operator-(const Poly &other) const
{
    if (other.size > this->size) 
    {
        Poly dif(0, other.size);

        for (int i = 0; i < this->size; i++) 
        {
            dif.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int i = 0; i < other.size; i++) 
        {
            dif.coeffPtr[i] -= other.coeffPtr[i];
        }
        return dif;
    } 
    else 
    {
        Poly dif(0, this->size);

        for (int i = 0; i < this->size; i++) 
        {
            dif.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int i = 0; i < other.size; i++) 
        {
            dif.coeffPtr[i] = other.coeffPtr[i];
        }
        return dif;
    }
}

Poly Poly::operator*(const Poly &other) const
{
    int tempSize = this->size + other.size;
    Poly prod(0, tempSize);

    for (int i = 0; i < this->size + 1; i++)
    {
       for (int j = 0; j < other.size + 1; j++)
       {
           prod.coeffPtr[i + j] += this->coeffPtr[i] * other.coeffPtr[j];
       }
    }
    return prod;
}

Poly& Poly::operator+=(const Poly &other)
{
    *this = *this + other;
    return *this;
}

Poly& Poly::operator-=(const Poly &other)
{
    *this = *this - other;
    return *this;
}

Poly& Poly::operator*=(const Poly &other)
{
    *this = *this * other;
    return *this;
}

Poly& Poly::operator=(const Poly &other)
{
    if (this->coeffPtr == other.coeffPtr)
    {
        return *this;
    }
    else if (this->size == other.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coeffPtr[i] = other.coeffPtr[i];
        }
    }
    else if (this->size > other.size)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coeffPtr[i] = 0;
        }

        for (int j = 0; j < other.size; j++)
        {
            this->coeffPtr[j] = other.coeffPtr[j];
        }
    }
    else if (this->size < other.size)
    {
        delete[] this->coeffPtr;
        coeffPtr = NULL;
        this->size = other.size;
        this->coeffPtr = new int[this->size];

        for (int i = 0; i < this->size; i++) 
        {
            this->coeffPtr[i] = other.coeffPtr[i];
        }
    }
    return *this;
}

bool Poly::operator==(const Poly &other) const
{
    if (this->size != other.size)
    {
        if (this->size < other.size)
        {
            for (int i = 0; i < this->size + 1; i++)
            {
                if (this->coeffPtr[i] != other.coeffPtr[i])
                {
                    return false;
                }
            }

            for (int i = this->size + 1; i < other.size + 1; i++) 
            {
                if (other.coeffPtr[i] != 0)
                {
                    return false;
                }
            }
        }
        else 
        {
            for (int i = 0; i < other.size + 1; i++) 
            {
                if (this->coeffPtr[i] != other.coeffPtr[i])
                {
                    return false;
                }
            }

            for (int i = other.size + 1; i < this->size + 1; i++) 
            {
                if (this->coeffPtr[i] != 0)
                {
                    return false;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < this->size + 1; i++)
        {
            if (this->coeffPtr[i] != other.coeffPtr[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool Poly::operator!=(const Poly& other) const
{
    return !(*this == other);
}


