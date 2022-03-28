#pragma once
#include <iostream>
using namespace std;

class Poly 
{  
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
    Poly& operator=(const Poly &other);

    Poly& operator+=(const Poly &other);
    Poly& operator-=(const Poly &other);
    Poly& operator*=(const Poly &other);

    bool operator==(const Poly &other) const;
    bool operator!=(const Poly &other) const;

    friend istream &operator>>(istream &input, Poly &ogVal);

    friend ostream &operator<<(ostream &output, const Poly &ogPoly);
};