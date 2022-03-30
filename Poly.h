// ------------------------------------------------ Poly.cpp ----------------------------------------------------------
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


#pragma once
#include <iostream>
using namespace std;

class Poly 
{  

    friend istream &operator>>(istream &input, Poly &other);

    friend ostream &operator<<(ostream &output, const Poly &other);

private:
    int* coeffPtr;
    int size;

public:
    Poly();
    Poly(int coeff);
    Poly(int coeff, int power);
    Poly(const Poly &input);
    ~Poly();

    int getCoeff(int power) const;
    void setCoeff(int coeff, int power);

    Poly operator+(const Poly &other) const;
    Poly operator-(const Poly &other) const;
    Poly operator*(const Poly &other) const;

    Poly& operator+=(const Poly &other);
    Poly& operator-=(const Poly &other);
    Poly& operator*=(const Poly &other);

    Poly& operator=(const Poly &other);

    bool operator==(const Poly &other) const;
    bool operator!=(const Poly &other) const;
};