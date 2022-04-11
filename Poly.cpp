// ------------------------------------------------ Poly.cpp --------------------------------------------------------- 
// Danny Kha
// CSS 343
// Professor Dong Si
// File created: 3/29/22
// Last modification: 4/7/22
// Created using C++11 
// IDE: VScode
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of this class is the implementation of
// represneting polynomials using arrays. The functions are 
// declared in the Poly.h file while this file contains the implementation.
// Every polynomial is stored within an array where the coefficient and the
// power value of the coefficient is stored. This program can
// set, change, add, subtract, and multiply polynomials.
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

    while (cont) // takes in values from input.
    {
        input >> tempCoeff;
        input >> tempPower;

        if ((tempCoeff == -1) && (tempPower == -1)) // checks when values are -1 -1 to stop.
        {
            cont = false;
        } 
        else {
            polyNom.setCoeff(tempCoeff, tempPower); // assigns values to Poly.
        }
    }
    return input;
}   // end of istream override

// ------------------------------------ostream <<-----------------------------------------------  
// Description: Output stream overloader that outputs the polynomial with console print statements.
// ---------------------------------------------------------------------------------------------------  
ostream &operator<<(ostream &output, const Poly &polyNom)
{
    bool zeroCheck = true; // checks if the poly has zeroes

    for (int i = polyNom.size - 1; i >= 0; i--) // loops through array 
    {
        if (polyNom.coeffPtr[i] != 0) // check if the index is not zero
        {
            zeroCheck = false; // sets false.
            output << " ";
            if (polyNom.coeffPtr[i] > 0) // if the coeff is greater then 0
            {
                output << "+"; // coeff greater then 0 is a positive, +.
            }
            if (i == 0) // if it is zero then just output it.
            {
                output << polyNom.coeffPtr[i];
            }
            else if (i == 1) // checking to see if x is valid to print.
            {
                output << polyNom.coeffPtr[i] << "x";
            }
            else // last case is printing polys with powers to them.
            {
                output << polyNom.coeffPtr[i] << "x^" << i;
            }
        }
    }
    if (zeroCheck == false) 
    {
        return output; // returning output.
    }
    else
    {
        return output << "0"; // returning zeroes if poly is all zeroes.
    }
}   // end of ostream override

// ------------------------------------largestDegree-----------------------------------------------  
// Description: Helper function used to find the larger degree between two polynomials
// ---------------------------------------------------------------------------------------------------  
int Poly::largestDegree(const Poly &x, const Poly &y) const
{
    int max = x.size;

    if (y.size > x.size)
    {
        max = y.size;
    }
    return max;
} // end of largestDegree

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
    coeffPtr[0] = coeff; // set 0th index to the coeff
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
    coeffPtr[power] = coeff; // set the coeff to the corresponding power.
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
        coeffPtr[i] = input.coeffPtr[i]; // setting the poly object to the input.
    }
} // end of copy constructor

// ------------------------------------Poly Destructor-----------------------------------------------  
// Description: Deletes the coefficient pointer and sets it to nullptr to deallocate the array.
// ---------------------------------------------------------------------------------------------------  
Poly::~Poly() 
{
    delete[] coeffPtr; // delete array.
    coeffPtr = nullptr; 
} // end of destructor

// ------------------------------------Assignment Operator-----------------------------------------------  
// Description: Assigns the other right hand side Poly object to the left hand side poly Object.
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator=(const Poly &other)
{
    if (this->coeffPtr == other.coeffPtr) // checking if they are equal, true return Poly.
    {
        return *this;
    }
    else if (this->size == other.size) // if left
    {
        for (int i = 0; i < this->size; i++)
        {
            this->coeffPtr[i] = other.coeffPtr[i];
        }
    }
    else if (this->size > other.size) // now checking for sizes.
    {
        for (int i = 0; i < this->size; i++) 
        {
            this->coeffPtr[i] = 0; // sets all the indexes to 0.
        }

        for (int j = 0; j < other.size; j++)
        {
            this->coeffPtr[j] = other.coeffPtr[j]; // then sets all indexes of other to this Poly.
        }
    }
    else if (this->size < other.size) // checking for opposite sizes.
    {
        delete[] this->coeffPtr; // deletes the Poly object.
        coeffPtr = nullptr; 
        this->size = other.size; // copies the size
        this->coeffPtr = new int[this->size]; // creates the new array

        for (int i = 0; i < this->size; i++) 
        {
            this->coeffPtr[i] = other.coeffPtr[i]; // now copies values of other to the new array.
        }
    }
    return *this; // returns the new array Poly object.
} // end of assignment overload

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
    if (power >= 0) // checking that the index is valid (positive).
    {
        if (power > this->size) // Check if power is not larger then the size of the array.
        {
            int *temp = new int[power + 1];  // Temp array created.

            for (int i = 0; i < this->size; i++)
            {
                temp[i] = coeffPtr[i];  // Copies the poly object array to temp array.
            }

            for (int j = this->size; j < power + 1; j++)
            {
                temp[j] = 0; // sets the rest of the array full of zeroes.
            }
            temp[power] = coeff; // Assigns coefficient to the correct index of array.

            delete[] coeffPtr; 
            coeffPtr = nullptr;    
            coeffPtr = temp; 
            temp = nullptr;     
            this->size = power + 1;   
        }
        else
        {
            coeffPtr[power] = coeff; // assigns the coeff to the correct power index.
        }
    }
} // end of setCoeff

// ------------------------------------Operator + Overload----------------------------------------  
// Description: Allows the addition of two polynomials and returns the sum of the two polynomials as a poly object.
// ---------------------------------------------------------------------------------------------------  
Poly Poly::operator+(const Poly &other) const
{
    int tempSize = largestDegree(*this, other); // comparing the size between this and other obj.
    Poly sum(0, tempSize); // creates a new Poly object to be sum with the power (size) from tempSize.

    for (int i = 0; i < this->size; i++) 
    {
        sum.coeffPtr[i] = this->coeffPtr[i]; // copying values to the sum array
    }

    for (int j = 0; j < other.size; j++)
    {
        sum.coeffPtr[j] += other.coeffPtr[j]; // adding the other to the sum of the array.
    }
    return sum; // returns the sum poly object.
} // end of addition overload 

// ------------------------------------Operator - Overload------------------------------------------  
// Description: Allows the subtraction of two polynomials and returns the difference of the polynomials.
// ---------------------------------------------------------------------------------------------------  
Poly Poly::operator-(const Poly &other) const
{
    int tempSize = largestDegree(*this, other); // comparing the size between this and other obj.
    Poly dif(0, tempSize); // creates a new Poly object to be dif with the power (size) from tempSize.

    for (int i = 0; i < this->size ; i++)
    {
        dif.coeffPtr[i] = this->coeffPtr[i]; // copying values tothe dif array.
    }

    for (int j = 0; j < other.size; j++)
    {
        dif.coeffPtr[j] -= other.coeffPtr[j]; // subtracting the other to the dif of the array.
    }
    return dif; // returns the difference poly object.
} // end of subtraction overload

// ----------------------------------Operator * Overload-----------------------------------------------  
// Description: Allows the multiplication of two polynomials and returns the product of the polynomials
// ---------------------------------------------------------------------------------------------------  
Poly Poly::operator*(const Poly &other) const
{
    int tempSize = this->size + other.size; // checking the size between this and other obj.
    Poly prod(0, tempSize); // creates a new Poly object to be product with the power (size) from tempSize.

    for (int i = 0; i < this->size; i++) 
    {
       for (int j = 0; j < other.size; j++)
       {
           prod.coeffPtr[i + j] += this->coeffPtr[i] * other.coeffPtr[j]; 
           // multiplying between this and other polys and then adding it to the product.
       }
    }
    return prod; // returns the product poly object.
} // end of multiplication overload

// ------------------------------------Operator += Overload-------------------------------------------  
// Description: Allows the addition of two polynomials and assigns the left polynomial to the sum. 
// Returns the left polynomial after addition.
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator+=(const Poly &other)
{
    *this = *this + other;
    return *this;
} // end of addition assignment overload

// ------------------------------------Operator -= Overload-------------------------------------------  
// Description: Allows the subtraction of two polynomials and assigns the left polynomial to the difference.
// Returns the left polynomial after subtraction.
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator-=(const Poly &other)
{
    *this = *this - other;
    return *this;
} // end of subtraction assignment overload

// ------------------------------------Operator *= Overload-------------------------------------------  
// Description: Allows the multiplication of two polynomials and assigns the left polynomial to the sum.
// Returns the left polynomial after multiplication. 
// ---------------------------------------------------------------------------------------------------  
Poly& Poly::operator*=(const Poly &other)
{
    *this = *this * other;
    return *this;
} // end of multiplication assignment overload

// ------------------------------------Operator == Overload------------------------------------  
// Description: Checks the equality between polynomial objects if they contain the same polynomials.
// Returns true if the polynomial objects are the same and false otherwise.
// ---------------------------------------------------------------------------------------------------  
bool Poly::operator==(const Poly &other) const
{
    if (this->size != other.size) // checking that both Poly objects are not equal size 
    {
        if (this->size < other.size) // Then checking if lhs is smaller then rhs.
        {
            for (int i = 0; i < this->size; i++)
            {
                if (this->coeffPtr[i] != other.coeffPtr[i]) // Making sure they are not equal.
                {
                    return false; // return false if they are not equal.
                }
            }

            for (int i = this->size; i < other.size; i++) 
            {
                if (other.coeffPtr[i] != 0) // making sure that rhs is not equal to 0
                {
                    return false; // return false if one of the values is equal to 0 in rhs.
                }
            }
        }
        else // This is for if lhs is larger then rhs.
        {
            for (int i = 0; i < other.size; i++) 
            {
                if (this->coeffPtr[i] != other.coeffPtr[i]) // Making sure they are not equal.
                {
                    return false; // return false if they are not equal.
                }
            }

            for (int i = other.size; i < this->size; i++) 
            {
                if (this->coeffPtr[i] != 0) // making sure that the lhs is not equal to 0
                {
                    return false; // return false if one of the values is equal to 0 in lhs.
                }
            }
        }
    }
    else // Now if the sizes of both the poly objects are equal
    {
        for (int i = 0; i < this->size; i++) 
        {
            if (this->coeffPtr[i] != other.coeffPtr[i]) // checking if the values in the lhs and rhs are equal
            {
                return false; // return false if they are not equal.
            }
        }
    }
    return true; // after going through all the cases return true.
} // end of equality overload

// ------------------------------------Operator != Overload-------------------------------------------  
// Description: Checks if two polynomial objects do not have the same polynomials.
// Returns true if the polynomial objects are different and false otherwise.
// ---------------------------------------------------------------------------------------------------  
bool Poly::operator!=(const Poly& other) const
{
    return !(*this == other); // returning the opposite of the == operator.
} // end of non-equality overload



