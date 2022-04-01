// ------------------------------------------------ Poly.cpp --------------------------------------------------------- 
// Danny Kha
// CSS 343
// Professor Dong Si
// File created: 3/29/22
// Last modification: 
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of this class is the implementation of
// represneting polynomials using arrays. The functions are 
// declared in the Poly.h file while this file contains the implementation.
// Every polynomial is stored within an array where the coefficient and the
// power value of the coefficient is stored. This program can
// set, change, add, subtract, and multiply polynomials.
// -------------------------------------------------------------------------------------------------------------------- 
// Specifications: The only function that is not a part of the overloading
// functions is the largestPoly helper function.
//
// Assumptions: The inputs are valid and that negative powers are not included.  
// Only whole number values are being used as a input (integers)
//
// Features: Uses a dynamically allocated array to hold the polynomial.
// Includes functions for equality check, addition, subtraction, and multiplication of 
// polynomials.
// -------------------------------------------------------------------------------------------------------------------- 

#include "Poly.h"

// ------------------------------------operator >>-----------------------------------------------  
// Description: Input stream overloader that takes from the console two integer values.
// The first input is set to the coefficient and the second is set as the power.
// ---------------------------------------------------------------------------------------------------  
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
}   // end of istream override

// ------------------------------------ostream <<-----------------------------------------------  
// Description: Output stream overloader that outputs the polynomial with console print statements.
// ---------------------------------------------------------------------------------------------------  
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
}   // end of ostream override

// ------------------------------------largestPoly-----------------------------------------------  
// Description: Helper function used to find the larger polynomial between x and y.
// ---------------------------------------------------------------------------------------------------  
int Poly::largestPoly(const Poly &x, const Poly &y) const
{
    int max = x.size;

    if (y.size > x.size)
    {
        max = y.size;
    }
    return max;
} // end of largestPoly

// ------------------------------------Default Poly Constructor-------------------------------------------  
// Description: The default constructor for Poly
// ---------------------------------------------------------------------------------------------------  
Poly::Poly()
{
    this->size = 1;
    coeffPtr = new int[this->size];
    coeffPtr[0] = 0;
} // end of default constructor

// ------------------------------------Poly Constructor One--------------------------------------------  
// Description: Constructor with a single argument
// ---------------------------------------------------------------------------------------------------  
Poly::Poly(int coeff)
{
    this->size = 1;
    coeffPtr = new int[this->size];
    coeffPtr[0] = coeff;
} // end of constructor

// ------------------------------------Poly Constructor Two------------------------------------------  
// Description: Constructor with two arguments.
// Sets the size to power + 1 and coefficient to last index of the array.
// ---------------------------------------------------------------------------------------------------  
Poly::Poly(int coeff, int power)
{
    this->size = power + 1;
    coeffPtr = new int[this->size];

    for (int i = 0; i < this->size; i++)
    {
        coeffPtr[i] = 0;
    }
    coeffPtr[power] = coeff;
} // end of constructor with power

// ------------------------------------Copy Constructor-----------------------------------------------  
// Description: Deep copy constructor of a inputted polynomial.
// ---------------------------------------------------------------------------------------------------  
Poly::Poly(const Poly &input)
{
    this->size = input.size;
    coeffPtr = new int[size];

    for (int i = 0; i < this->size; i++) 
    {
        coeffPtr[i] = input.coeffPtr[i];
    }
} // end of copy constructor

// ------------------------------------Poly Destructor-----------------------------------------------  
// Description: Deletes the coefficient pointer and sets it to nullptr to deallocate the array.
// ---------------------------------------------------------------------------------------------------  
Poly::~Poly() 
{
    delete[] coeffPtr;
    coeffPtr = nullptr;
} // end of destructor

// ------------------------------------getCoeff-----------------------------------------------  
// Description: Returns the coefficient of the inputted power.
// ---------------------------------------------------------------------------------------------------  
int Poly::getCoeff(int power) const 
{
    if ((this->size > power) && (power >= 0)) 
    {
        return coeffPtr[power]; // returns coefficient of the specific index (power)
    } 
    else 
    {
        return 0; // returns 0 if the input power is not present.
    }
} // end of getCoeff

// ------------------------------------setCoeff-----------------------------------------------  
// Description: Sets the inputted coefficient into the array that is indexed by the inputted power.
// A new array is created if the power is out of the existing array range.
// ---------------------------------------------------------------------------------------------------  
void Poly::setCoeff(int coeff, int power)
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
} // end of setCoeff

// ------------------------------------Operator + Overload----------------------------------------  
// Description: Allows the addition of two polynomials and returns the sum of the two polynomials as a poly object.
// ---------------------------------------------------------------------------------------------------  
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
    return sum; // returns sum of the polynomials
} // end of addition overload 

// ------------------------------------Operator - Overload------------------------------------------  
// Description: Allows the subtraction of two polynomials and returns the 
// ---------------------------------------------------------------------------------------------------  
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
} // end of subtraction overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
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
} // end of multiplication overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator+=(const Poly &other)
{
    *this = *this + other;
    return *this;
} // end of addition assignment overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator-=(const Poly &other)
{
    *this = *this - other;
    return *this;
} // end of subtraction assignment overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator*=(const Poly &other)
{
    *this = *this * other;
    return *this;
} // end of multiplication assignment overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
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
} // end of equal overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
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
} // end of equality overload

// ------------------------------------ReadyToQuit-----------------------------------------------  
// Description: 
// ---------------------------------------------------------------------------------------------------  
bool Poly::operator!=(const Poly& other) const
{
    return !(*this == other);
} // end of non-equality overload



