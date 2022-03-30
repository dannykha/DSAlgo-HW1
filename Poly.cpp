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

Poly::Poly(int coeff, int power)
{
    this->size = power + 1;
    coeffPtr = new int[this->size];

    for (int i = 0; i < this->size; i++) {
        coeffPtr[i] = 0;
    }
    coeffPtr[power] = coeff;
}

Poly::Poly(const Poly &input)
{
    this->size = input.size;
    coeffPtr = new int[size];

    for (int i = 0; i < this->size; i++) {
        coeffPtr[i] = input.coeffPtr[i];
    }
}

Poly::~Poly() 
{
    delete[] coeffPtr;
    coeffPtr = NULL;
}

int Poly::getCoeff(int power) const 
{
    if (power >= 0 && power < this->size) {
        return coeffPtr[power];
    } else {
        return 0;
    }
}

void Poly::setCoeff(int coeff, int power)
{
    if (power >= 0) {
        if (power < this->size) {
            coeffPtr[power] = coeff;
        } else {
            int *temp = new int[power + 1];
            for (int i = 0; i < this->size; i++) {
                temp[i] = coeffPtr[i];
            }
            for (int j = this->size; j < power + 1; j++) {
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
    if (other.size > this->size) {
        Poly sum(0, other.size);

        for (int i = 0; i < other.size; i++) {
            sum.coeffPtr[i] = other.coeffPtr[i];
        }

        for (int j = 0; j < this->size; j++) {
            sum.coeffPtr[j] += this->coeffPtr[j];
        }
        return sum;
    } else {
        Poly sum(0, this->size);

        for (int i = 0; i < this->size; i++) {
            sum.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int j = 0; j < other.size; j++) {
            sum.coeffPtr[j] += other.coeffPtr[j];
        }
        return sum;
    }
}

Poly Poly::operator-(const Poly &other) const
{
    if (other.size > this->size) {
        Poly dif(0, other.size);

        for (int i = 0; i < this->size; i++) {
            dif.coeffPtr[i] = this->coeffPtr[i];
        }

        for (int j = 0; j < other.size; j++) {
            dif.coeffPtr[j] -= other.coeffPtr[j];
        }
        return dif;
    } else {
        Poly dif(0, this->size);

        for (int i = 0; i < other.size; i++) {
            dif.coeffPtr[i] = other.coeffPtr[i];
        }

        for (int j = 0; j < this->size; j++) {
            dif.coeffPtr[j] = this->coeffPtr[j];
        }
    }
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

bool Poly::operator==(const Poly &other) const
{
    if (this->size == other.size) {
        for (int i = 0; i < this->size; i++) {
            if (coeffPtr[i] != other.coeffPtr[i]) {
                return false;
            }
        }
        return true;
    } else {
        
    }
}
