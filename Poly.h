// ------------------------------------------------ Poly.h ----------------------------------------------------------
// Danny Kha
// CSS 343
// Professor Dong Si
// File created on 3/29/22
// Last modification date was 4/7/22
// Created using C++11 
// IDE: VScode
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Poly.h is the decleration of the operators to implement an array to represent
// polynomials. 
// -------------------------------------------------------------------------------------------------------------------- 
// Specifications: The only function that is not a part of the overloading
// functions is the largestDegree helper function.
//
// Assumptions: The inputs are valid and that negative powers are not included.  
// Only whole number values are being used as a input (integers)
//
// Features: Uses a dynamically allocated array to hold the polynomial.
// Includes functions for equality check, addition, subtraction, and multiplication of 
// polynomials.
// -------------------------------------------------------------------------------------------------------------------- 

#pragma once
#include <iostream>
using namespace std;

class Poly 
{  
    // Input stream overload operator.
    friend istream &operator>>(istream &input, Poly &polyNom);
    // Output stream overload operator.
    friend ostream &operator<<(ostream &output, const Poly &polyNom);

private:
    int* coeffPtr; // Array pointer.
    int size; // Size of array. 
    int largestDegree(const Poly &x, const Poly &y) const; // largest value function.

public:
    // Constructors, destructor, and assignment operators.
    Poly();
    Poly(int coeff);
    Poly(int coeff, int power);
    Poly(const Poly &input);
    ~Poly();
    Poly& operator=(const Poly &other);

    // Functions for getter and setter of coefficients.
    int getCoeff(int power) const;
    void setCoeff(int coeff, int power);

    // Addition, subtraction, and multiplication operators.
    Poly operator+(const Poly &other) const;
    Poly operator-(const Poly &other) const;
    Poly operator*(const Poly &other) const;

    // Addition, subtraction, and multiplication compounded operators.
    Poly& operator+=(const Poly &other);
    Poly& operator-=(const Poly &other);
    Poly& operator*=(const Poly &other);

    // Comparison operators.
    bool operator==(const Poly &other) const;
    bool operator!=(const Poly &other) const;
};