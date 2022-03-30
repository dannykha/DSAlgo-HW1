// ------------------------------------------------ Poly.cpp --------------------------------------------------------- 
// Danny Kha
// CSS 343
// Professor Dong Si
// File created on 3/29/22
// Last modification date was 
// --------------------------------------------------------------------------------------------------------------------
// Purpose - a brief statement of the program's function  
// -------------------------------------------------------------------------------------------------------------------- 
// Notes on specifications, special algorithms, and assumptions.  
// -------------------------------------------------------------------------------------------------------------------- 

#include "Poly.h"

istream &operator>>(istream &input, Poly &polyNom)
{
    bool cont = true;
    int tempCoeff= 0;
    int tempPower = 0;

    while (cont)    
    {
        input >> tempCoeff;
        input >> tempPower;

        if ((tempCoeff == -1) && (tempPower == -1)) 
        {
            cont = false;
        } 
        else {
            polyNom.setCoeff(tempCoeff, tempPower); 
        }
    }
    return input;
}   


ostream &operator<<(ostream &output, const Poly &polyNom)
{
    bool zeroCheck = true;

    for (int i = polyNom.size - 1; i >= 0; i--)
    {
        if (polyNom.coeffPtr[i] != 0)
        {
            zeroCheck = false;
            output << " ";
            if (polyNom.coeffPtr[i] > 0)
            {
                output << "+";
            }
            if (i == 0)
            {
                output << polyNom.coeffPtr[i];
            }
            else if (i == 1)
            {
                output << polyNom.coeffPtr[i] << "x";
            }
            else
            {
                output << polyNom.coeffPtr[i] << "x^" << i;
            }
        }
    }
    if (zeroCheck == false)
    {
        return output;
    }
    else
    {
        return output << "0";
    }
}   

int Poly::largestPoly(const Poly &x, const Poly &y) const
{
    int max = x.size;

    if (y.size > x.size)
    {
        max = y.size;
    }
    return max;
}

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
    coeffPtr = nullptr;
}

int Poly::getCoeff(int power) const 
{
    if ((power >= 0) && (power < this->size)) 
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
        if (power > this->size)   
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
            coeffPtr = nullptr;    
            coeffPtr = temp; 
            temp = nullptr;     
            this->size = power + 1;   
        }
        else
        {
            coeffPtr[power] = coeff;
        }
    }
}

Poly Poly::operator+(const Poly &other) const
{
    int tempSize = largestPoly(*this, other);
    Poly sum(0, tempSize);

    for (int i = 0; i < this->size; i++)
    {
        sum.coeffPtr[i] = this->coeffPtr[i];
    }

    for (int j = 0; j < other.size; j++)
    {
        sum.coeffPtr[j] += other.coeffPtr[j];
    }
    return sum;
}

Poly Poly::operator-(const Poly &other) const
{
    int tempSize = largestPoly(*this, other);
    Poly dif(0, tempSize);

    for (int i = 0; i < this->size ; i++)
    {
        dif.coeffPtr[i] = this->coeffPtr[i];
    }

    for (int j = 0; j < other.size; j++)
    {
        dif.coeffPtr[j] -= other.coeffPtr[j];
    }
    return dif;
}

Poly Poly::operator*(const Poly &other) const
{
    int tempSize = this->size + other.size;
    Poly prod(0, tempSize);

    for (int i = 0; i < this->size; i++)
    {
       for (int j = 0; j < other.size; j++)
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
            for (int i = 0; i < this->size; i++)
            {
                if (this->coeffPtr[i] != other.coeffPtr[i])
                {
                    return false;
                }
            }

            for (int i = this->size; i < other.size; i++) 
            {
                if (other.coeffPtr[i] != 0)
                {
                    return false;
                }
            }
        }
        else 
        {
            for (int i = 0; i < other.size; i++) 
            {
                if (this->coeffPtr[i] != other.coeffPtr[i])
                {
                    return false;
                }
            }

            for (int i = other.size; i < this->size; i++) 
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
        for (int i = 0; i < this->size; i++)
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



