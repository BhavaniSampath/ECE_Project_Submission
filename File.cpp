#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <fstream>
#include "File.h"
#include "Types.h"
#include <iostream>
#include <regex>
#include <stdio.h>
#include <sstream>
#include <string>
using namespace std;

map<string, int>  gmPrimaryInputLexRank;
int gnEncoding;
map<string, polynomial_t> gmBasis;

/* ------------------------------------------------------------------------------
 * Checks that file has extension ".sing"
 * 
 *  @param string: Name of file.
 *  @return bool: True if file has extension ".sing," otherwise false.
 * ------------------------------------------------------------------------------
 */
bool bCheckFileExt_File(string s)
{
    if(s.substr(s.find_last_of(".") + 1) == "sing")
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

/* ------------------------------------------------------------------------------
 * Checks if string is a polynomial.
 * 
 *  @param string: Line from file.
 *  @return bool: True if line is a polynomial, 
 *  if so it calls appropriate functions for polynomial. Otherwise it just
 *  returns false.
 * ------------------------------------------------------------------------------
 */
bool bCheckIfPoly_File(string s)
{
    if(s.find("poly") == 0)
    {
        vector<string> sPolynomialExpression = vtGetExpression_File(s);
        string sPolyName = sPolynomialExpression[0];
        sPolyName = sPolyName.substr(4, sPolyName.length() - 1); 
        vector<string> terms = vtGetTerms_File(sPolynomialExpression[1]);
        map<string, string> coefficientsAndMonomials = mGetCoefficientsAndMonomials_File(terms);
        polynomial_t polynomial = polyMakePolynomial_Types (coefficientsAndMonomials);
        gmBasis.insert(pair<string, polynomial_t> (sPolyName, polynomial));
        return 1;
    }
       
    return 0;
}

/* ------------------------------------------------------------------------------
 * Checks if string is a ring.
 * 
 *  @param string: Line from file.
 *  @return bool: True if line is a ring, 
 *  if so it calls appropriate functions for ring. Otherwise it just
 *  returns false.
 * ------------------------------------------------------------------------------
 */
bool bCheckIfRing_File(string s)
{
    if(s.find("ring") == 0)
    {
        vector<string> sRingExpression = vtGetExpression_File(s);
        gnEncoding = nGetEncodingForOrder_File(sRingExpression[1]);
        vGetPrimaryInputLexOrder_File(sRingExpression[1]); 
        return 1;
    }
    return 0;
}  

/* ------------------------------------------------------------------------------
 * Reads ".sing" file
 * 
 *  @param int: Number of command-line arguments.
 *  @param char*: Char* array of command-line arguments.
 *                Second being ".sing" filename.
 *  @return void
 * ------------------------------------------------------------------------------
 */
void vReadFile_File(int argc, char* argv[])
{
    string fileName;
    ifstream inFile;
    string s = "";
    string token;
 
    if(argc > 2)
    {
        puts("Error: Too many arguments given.");
        return;
    }

    if(argc < 2)
    {
        puts("Error: Too few arguments given.");
        return;
    }

    if (argv[1] == NULL)
    {
        perror ("Error");
    }
    else
    {
        fileName = argv[1];
    }

    if(!bCheckFileExt_File(fileName))
    {
        puts("Error: Wrong File Extension.");
        return;
    }

    inFile.open(fileName);
    while(getline(inFile, s))
    {
        stringstream ss(s);

        while(getline(ss, s, ';'))
        {
            s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
            if(bCheckIfPoly_File(s) || bCheckIfRing_File(s))
            {
                s += ';';
            }
            s = "";
        }
    }

    return;
}

/* ------------------------------------------------------------------------------
 * Parses string by '=' for either ring or polynomial.
 * 
 *  @param string: String that contains either a ring or polynomial.
 *  @return vector<string>: First element holds ring/polynomial name
 *                          and the second element holds the ring or 
 *                          polynomial the expression.
 * ------------------------------------------------------------------------------
 */
vector<string> vtGetExpression_File(string s)
{
    vector <string> tokens, terms;
    stringstream ss(s);
    string token, poly;
     
    while(getline(ss, token, '='))
    {
        tokens.push_back(token);
    }
        
    return tokens;
}

/* ------------------------------------------------------------------------------
 * Parses string containing polynomial for terms of it.
 * 
 *  @param string: String that contains a polynomial.
 *  @return vector<string>: Contains terms of the polynomial as strings.
 * ------------------------------------------------------------------------------
 */
vector<string> vtGetTerms_File(string s)
{
    vector <string> terms;

    regex re ("([+-]?[^-+]+)"); 

    regex_iterator<string::iterator> iterTerms ( s.begin(), s.end(), re );
    regex_iterator<string::iterator> iterEnd;

    while (iterTerms != iterEnd) 
    {
        string str = iterTerms->str();
        terms.push_back(str);
        ++iterTerms;
    }
   
    return terms;
}

/* ------------------------------------------------------------------------------
 * Parses vector<string> containing terms as strings to create a map
 * of monomials as the key and coefficients as the value.
 * 
 *  @param vector<string>: Strings containing the terms of a polynomial.
 *  @return map<string, string>: Key = Monomial and Value = coefficient
 * ------------------------------------------------------------------------------
 */
map<string, string> mGetCoefficientsAndMonomials_File(vector<string> v)
{
    map<string, string> result;

    for(string s: v)
    {
        regex re ("^[^*]*"); 

        regex_iterator<string::iterator> iterTerms ( s.begin(), s.end(), re );
        regex_iterator<string::iterator> iterEnd;

        while (iterTerms != iterEnd) 
        {
            string str = iterTerms->str();
            s.replace(s.find(str), str.length(), "");
            if(s!="")
            {
                s.erase(0, 1);
            }
            else
            {
                s="1";
            }
            result.insert(pair<string, string> (s, str));
            ++iterTerms;
            
        }

    }
    return result;
}

/* ------------------------------------------------------------------------------
 * Negative check for coefficients.
 * 
 *  @param string: string containing coefficient
 *  @return polynomial_t: 1 = Negative and 0 = Positive
 * ------------------------------------------------------------------------------
 */
bool bCoefficientIsNegative_File(string s)
{
    if(s[0] == '-')
        return 1;
    return 0;
}

/* ------------------------------------------------------------------------------
 * Get numerator and denominator from coefficient string.
 * 
 *  @param string: string containing coefficient
 *  @return polynomial_t: First element is the numerator 
 *                        and second is denominator
 * ------------------------------------------------------------------------------
 */
vector<string> vtGetNumeratorAndDenominator_File(string s)
{
    vector <string> tokens;
    stringstream ss(s);
    string token;
    
    while(getline(ss, token, '/'))
    {
        tokens.push_back(token);
    }
    
    return tokens;
}

/* ------------------------------------------------------------------------------
 * Gets variables and degrees of monomial.
 * 
 *  @param string: string containing monomial
 *  @return vector<string>: Contains variables and degrees of monomial
 * ------------------------------------------------------------------------------
 */
vector<string> vtGetPartsOfMonomial_File(string s)
{
    vector <string> tokens;
    stringstream ss(s);
    string str, str2;
    
    while(getline(ss, str, '*'))
    { 
        stringstream ss2(str);
        while(getline(ss2, str2, '^'))
        {
            tokens.push_back(str2);
        }
    }
    return tokens;
}

/* ------------------------------------------------------------------------------
 * Encoding system to pick term ordering.
 * 
 *  @param string: string containing ring from file
 *  @return int: Encoding for ordering
 * ------------------------------------------------------------------------------
 */
int nGetEncodingForOrder_File (string ring)
{
    if(ring.substr(ring.find_last_of("),") + 1) == "Dp")
    {
        return 0;
    }
    if(ring.substr(ring.find_last_of("),") + 1) == "dp")
    {
        return 1;
    }
    if(ring.substr(ring.find_last_of("),") + 1) == "lp")
    {
        return 2;
    }

    return -1;
}

/* ------------------------------------------------------------------------------
 * Sets mPrimaryInputLexRank for lexographical rank of primary inputs.
 * Key = Primary input as a string and Value = rank
 * 
 *  @param string: string containing ring from file
 *  @return void
 * ------------------------------------------------------------------------------
 */
void vGetPrimaryInputLexOrder_File(string ring)
{
    regex re ("[^,]+"); 

    regex_iterator<string::iterator> iterTerms ( ring.begin(), ring.end(), re );
    regex_iterator<string::iterator> iterEnd;

    bool startParathesisFound = false;
    bool endParathesisFound = false;

    int position = 0;
    while (iterTerms != iterEnd) 
    {
        string str = iterTerms->str();
        if (str[0] == '(') startParathesisFound = true; // Don't reset to false

        if(startParathesisFound && !endParathesisFound)
        {
            if (str[0] == '(') 
                str.erase(0, 1);

            if (str[str.length() - 1] == ')')
            {
                endParathesisFound = true; // Don't reset to false
                str.erase( str.length()-1);
            } 
            
            gmPrimaryInputLexRank.insert(pair<string, int> (str, position));
            position++;
        }

        ++iterTerms;
    }

    return;
}