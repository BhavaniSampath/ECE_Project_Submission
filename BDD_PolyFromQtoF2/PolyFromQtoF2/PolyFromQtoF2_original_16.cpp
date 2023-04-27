/*
 * Bailey Martin
 * University of Utah
 * College of Engineering
 * Electrical and Computer Engineering Department
 * Bailey.Martin@utah.edu
 * Ms.BaileyL.Martin@gmail.com
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include "File.h"
#include "Types.h"
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <sstream>
#include <string>
using namespace std;

bool isConstant(polynomial_t poly);
bool isTerm(polynomial_t poly);
polynomial_t getConstantAsPolynomial(polynomial_t poly);
polynomial_t getTermAsPolynomial(polynomial_t poly);
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable);

extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;
extern map<string, polynomial_t> gmBasis;

int main (int argc, char* argv[]) 
{
    vReadFile_File(argc, argv);
    string sPolyName;
    polynomial_t polynomial;

    for(std::map<string, polynomial_t>::iterator iterMap = gmBasis.begin(); iterMap != gmBasis.end(); ++iterMap)
    {
        sPolyName =  iterMap->first;
        polynomial = iterMap->second;
        string sPoly = sPolyAsString (polynomial);
        cout << "Given polynomial is " << sPolyName << ":" << sPoly << endl;
    }

    // // Test if should get variety
    // cout << "It is a constant? " << isConstant(polynomial) << endl;
    // cout << "What is the variety? " << sPolyAsString(getConstantAsPolynomial(polynomial)) << endl;
    // cout << "Is it a term? " << isTerm(polynomial) << endl; 
    // cout << "What is the variety? " << sPolyAsString(getTermAsPolynomial(polynomial)) << endl;

    // // Test variable division
    // tuple<polynomial_t, polynomial_t> divTuple = variableDivision(polynomial, make_tuple("a_1", 1));
    // string quotient = sPolyAsString(get<0>(divTuple));
    // string remainder = sPolyAsString(get<1>(divTuple));
    // cout << "Quotient is: " << quotient << endl;
    // cout << "Remainder is: " << remainder << endl;

    return 0;
}

/*
 * A Base Case for Recursion
 */
bool isConstant(polynomial_t poly)
{
    if (!isTerm(poly))
    {
        return false;
    }

    polynomial_t::iterator iter = poly.begin();
    advance(iter, 0);
    term_t term = *iter;
    monomial_t monomial = term.monomial;

    for (tuple<string,int> variable: monomial)
    {
        if(get<int>(variable) != 0)
        {
            return false;
        }
    }

    return true;
}

/*
 * Get variety of Constant.
 * If poly = 0 return numerator as zero.
 * Else return numerator and denominator as one.
 */
polynomial_t getConstantAsPolynomial(polynomial_t poly)
{
    polynomial_t::iterator iter = poly.begin();
    advance(iter, 0);
    term_t term = *iter;
    polynomial_t polynomial;

    if (term.coefficient.numerator != 0)
    {
        term.coefficient.numerator = 1;
        term.coefficient.denominator = 1;
    }
    polynomial.push_back(term);
    return polynomial;

}

/*
 * A Base Case for Recursion
 */
bool isTerm(polynomial_t poly)
{
    if (poly.size() != 1)
    {
        return false;
    }
    return true;
}

/*
 * Return other base case in F_2
 */
polynomial_t getTermAsPolynomial(polynomial_t poly)
{
    polynomial_t::iterator iter = poly.begin();
    advance(iter, 0);
    term_t term = *iter;
    term.coefficient.numerator = 1;
    term.coefficient.denominator = 1;
    polynomial_t polynomial;
    polynomial.push_back(term);
    return polynomial;
}

/*
 * Divides polynomial by a variable. Returns a tuple with quotient and remainder.
 */
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable)
{
    polynomial_t quotient;
    polynomial_t remainder;
    for(term_t term:poly)
    {
        auto result = find(term.monomial.begin(), term.monomial.end(), variable);
        if(result != term.monomial.end())
        {
            get<int>(*result) = 0;
            quotient.push_back(term);
        }
        else
        {
            remainder.push_back(term);
        }

    }

    return make_tuple(quotient, remainder);
}
