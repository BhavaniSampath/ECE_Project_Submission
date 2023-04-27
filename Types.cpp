#include "Types.h"
#include "File.h"
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;

/* ------------------------------------------------------------------------------
 * Creates a coefficient_t object.
 * 
 *  @param bool: If coefficient is negative.
 *  @param int: numerator
 *  @param int: denominator
 *  @return coefficient_t: Generated coefficient_t
 * ------------------------------------------------------------------------------
 */
coefficient_t coeffMakeCoefficient_Types (bool bIsNegative, int numerator, int denominator)
{
    coefficient_t coefficient;
    coefficient.sign = bIsNegative;
    coefficient.numerator = numerator;
    coefficient.denominator = denominator;
    return coefficient;
}

/* ------------------------------------------------------------------------------
 * Creates a monomial_t object.
 * 
 *  @param vector<string>: parts of monomial -- variables and degrees
 *  @return monomial_t: Generated monomial_t
 * ------------------------------------------------------------------------------
 */
monomial_t monomMakeMonomial_Types (vector<string> partsOfMonomial)
{
    
    monomial_t monomial;
    
    for(const auto &pair : gmPrimaryInputLexRank)
    {
        monomial.push_back(make_tuple(pair.first, 0));
    }

    for(int i = 0; i < partsOfMonomial.size(); i+= 2)
    {
        auto matchLocation = find(monomial.begin(), monomial.end(), make_tuple(partsOfMonomial[i], 0));
        monomial.erase(matchLocation);
        monomial.push_back(make_tuple(partsOfMonomial[i], stoi(partsOfMonomial[i+1])));
        
    }

    sort(monomial.begin(), monomial.end(), monomLexicoCompare_Types);

    return monomial;
}

/* ------------------------------------------------------------------------------
 * Sort monomial_t lexicographically.
 * 
 *  @return bool
 * ------------------------------------------------------------------------------
 */
bool monomLexicoCompare_Types (const tuple<string, int> &monomBegin, const tuple<string, int> &monomEnd)
{
    int valueBegin = gmPrimaryInputLexRank.find(get<string>(monomBegin)) -> second;
    int valueEnd = gmPrimaryInputLexRank.find(get<string>(monomEnd)) -> second;

    return valueBegin < valueEnd;
}

/* ------------------------------------------------------------------------------
 * Get degree of monomial_t object.
 * 
 *  @param monomial_t
 *  @return int: Degree of monomial_t
 * ------------------------------------------------------------------------------
 */
int nDegreeOfMonomial_Types(monomial_t monomial)
{
    int nDegreeOfMonomial = 0;
    for(tuple<string, int> tuple : monomial)
    {
        nDegreeOfMonomial += get<int>(tuple);
    }

    return nDegreeOfMonomial;
}

/* ------------------------------------------------------------------------------
 * Get weighted degree of monomial_t object.
 * 
 *  @param monomial_t
 *  @return int: Weighted degree of monomial_t
 * ------------------------------------------------------------------------------
 */
int nWeightedDegreeOfMonomial_Types(monomial_t monomial)
{
    int nWeightedDegreeOfMonomial = 0;
    for(long unsigned int i = 0; i < monomial.size(); i++)
    {
        tuple<string, int> tuple = monomial.at(i);   
        nWeightedDegreeOfMonomial += (monomial.size() - i) * get<int>(tuple);
    }

    return nWeightedDegreeOfMonomial;
}

/* ------------------------------------------------------------------------------
 * Creates a term_t object.
 * 
 *  @param coefficient_t: coefficient_t for term_t
 *  @param monomial_t: monomial_t for term_t
 *  @return term_t: Generated term_t
 * ------------------------------------------------------------------------------
 */
term_t termMakeTerm_Types (coefficient_t coefficient, monomial_t monomial)
{
    term_t term;
    term.coefficient = coefficient;
    term.monomial = monomial;
    return term;
}

/* ------------------------------------------------------------------------------
 * Creates a term_t object for polynomial_t.
 * 
 *  @param vector<string>: parts of monomial -- variables and degrees
 *  @param bool: If coefficient is negative.
 *  @param vector<string>: numerator and denominator for coefficient
 *  @return term_t: 
 * ------------------------------------------------------------------------------
 */
term_t termMakeForPolynomials_Types (vector<string> partsOfMonomial,
                                      bool bIsNegative,
                                      vector<string> numeratorAndDenominator)
{
    // Making monomial
    monomial_t monomial = monomMakeMonomial_Types (partsOfMonomial);
    // Making Coefficient
    coefficient_t coefficient = coeffMakeCoefficient_Types (bIsNegative,
                                                                stoi(numeratorAndDenominator[0]),
                                                                stoi(numeratorAndDenominator[1]));

    // Making term
    term_t term = termMakeTerm_Types(coefficient, monomial);

    return term;
}

/* ------------------------------------------------------------------------------
 * Creates a polynomial_t object.
 * 
 *  @param map<string, string>: Terms of the polynomial in a map as 
 *                              Key = Monomial and Value = coefficient
 *  @return polynomial_t: Generated polynomial_t
 * ------------------------------------------------------------------------------
 */
polynomial_t polyMakePolynomial_Types (map<string, string> m)
{
    polynomial_t polynomial;
    for(std::map<string, string>::iterator iterMap = m.begin(); iterMap != m.end(); ++iterMap)
    {
        string sMonomial = iterMap->first; // monomial
        vector<string> partsOfMonomial = vtGetPartsOfMonomial_File(sMonomial);
        if(partsOfMonomial.size()==1)
        {
            string s0="0";
            partsOfMonomial.push_back(s0);
        }
        string sCoefficient = iterMap->second; // value
        vector<string> numeratorAndDenominator = vtGetNumeratorAndDenominator_File(sCoefficient);
        
        if(numeratorAndDenominator.size()==1)
        {
            string s="1";
            numeratorAndDenominator.push_back(s);
        } 
        term_t term = termMakeForPolynomials_Types (partsOfMonomial, 
                                                       bCoefficientIsNegative_File(sCoefficient), 
                                                       numeratorAndDenominator);
        
        polynomial.push_back(term);
    }

    // Order polynomial
    if (gnEncoding == 0) // Dp
    {
        polynomial.sort(polyDegreeLexicoCompare_Types);
    }
    else if(gnEncoding == 1) // dp
    {
        polynomial.sort(polyDegreeRevLexicoCompare_Types);
    }
    else // default is lp
    {
        polynomial.sort(polyLexicoCompare_Types);
    }

    return polynomial;
}

/* ------------------------------------------------------------------------------
 * Sort polynomial_t lexicographically.
 * 
 *  @return bool
 * ------------------------------------------------------------------------------
 */
bool polyLexicoCompare_Types (const term_t &polyBegin, const term_t &polyEnd)
{
    monomial_t monomBegin = polyBegin.monomial;
    monomial_t monomEnd = polyEnd.monomial;

    if(monomBegin.size() != monomEnd.size())
        exit(EXIT_FAILURE);
    else
    {
        if(monomBegin > monomEnd)
        {
            return true;
        }      
    }
    
    return false;
}

/* ------------------------------------------------------------------------------
 * Sort polynomial_t Degree-lexicographically.
 * 
 *  @return bool
 * ------------------------------------------------------------------------------
 */
bool polyDegreeLexicoCompare_Types (const term_t &polyBegin, const term_t &polyEnd)
{
    monomial_t monomBegin = polyBegin.monomial;
    monomial_t monomEnd = polyEnd.monomial;

    if(monomBegin.size() != monomEnd.size())
        exit(EXIT_FAILURE);
    else
    {
        int nDegreeOfMonomBegin = nDegreeOfMonomial_Types(monomBegin);
        int nDegreeOfMonomEnd = nDegreeOfMonomial_Types(monomEnd);

        if (nDegreeOfMonomBegin > nDegreeOfMonomEnd)
        {
            return true;
        }
        if(nDegreeOfMonomBegin < nDegreeOfMonomEnd)
        {
            return false;
        }
        else
        {
            if(monomBegin > monomEnd)
            {
                return true;
            }   
        }
    }
    
    return false;
}

/* ------------------------------------------------------------------------------
 * Sort polynomial_t Degree-reverse-lexicographically.
 * 
 *  @return bool
 * ------------------------------------------------------------------------------
 */
bool polyDegreeRevLexicoCompare_Types (const term_t &polyBegin, const term_t &polyEnd)
{
    monomial_t monomBegin = polyBegin.monomial;
    monomial_t monomEnd = polyEnd.monomial;

    if(monomBegin.size() != monomEnd.size())
        exit(EXIT_FAILURE);
    else
    {
        int nDegreeOfMonomBegin = nDegreeOfMonomial_Types(monomBegin);
        int nDegreeOfMonomEnd = nDegreeOfMonomial_Types(monomEnd);

        if (nDegreeOfMonomBegin > nDegreeOfMonomEnd)
        {
            return true;
        }
        if(nDegreeOfMonomBegin < nDegreeOfMonomEnd)
        {
            return false;
        }
        else
        {
            int nWeightedDegreeOfMonomBegin = nWeightedDegreeOfMonomial_Types(monomBegin);
            int nWeightedDegreeOfMonomEnd = nWeightedDegreeOfMonomial_Types(monomEnd);

            if (nWeightedDegreeOfMonomBegin > nWeightedDegreeOfMonomEnd)
            {
                return true;
            }
            if(nWeightedDegreeOfMonomBegin < nWeightedDegreeOfMonomEnd)
            {
                return false;
            }
            else
            {
                if(monomBegin < monomEnd)
                {
                    return true;
                }
            }      
        }
    }
    
    return false;
}

/* ------------------------------------------------------------------------------
 * Reduce polynomial by J0.
 * 
 *  @param polynomial_t: polynomial objecd to be reduced
 *  @return void
 * ------------------------------------------------------------------------------
 */
void vPolyIntToDigital_Types (polynomial_t &polynomial)
{
    for(term_t &term : polynomial)
    {
        monomial_t &monom = term.monomial;
        for(tuple<string, int> &tuple : monom)
        {
            if(get<int>(tuple) >= 1)
            {
                get<int>(tuple) = 1;
            }
            else
            {
                get<int>(tuple) = 0;
            }
        }
    }

    // Order polynomial
    if (gnEncoding == 0) // Dp
    {
        polynomial.sort(polyDegreeLexicoCompare_Types);
    }
    else if(gnEncoding == 1) // dp
    {
        polynomial.sort(polyDegreeRevLexicoCompare_Types);
    }
    else // default is lp
    {
        polynomial.sort(polyLexicoCompare_Types);
    }

    return;
}

/* ------------------------------------------------------------------------------
 * Reduce polynomial by J0.
 * 
 *  @param polynomial_t: polynomial object
 *  @return string: string version of polynomial
 * ------------------------------------------------------------------------------
 */
string sPolyAsString (polynomial_t poly)
{
    string sPoly = "";
    for (term_t term: poly)
    {
        coefficient_t coefficient = term.coefficient;
        monomial_t monomial = term.monomial;

        if(!coefficient.sign && (sPoly != ""))
        {
            sPoly += "+";
        }
        else if(coefficient.sign)
        {
            sPoly += "+";
        }

        sPoly += to_string(coefficient.numerator) + "/" + to_string(coefficient.denominator);

        for(tuple<string, int> variable: monomial)
        {
            if(get<int>(variable) == 0)
            {
                continue;
            }
            else
            {
                sPoly += "*" + get<string>(variable) + "^" + to_string(get<int>(variable));
            }
            
        }
    }

    return sPoly;
}