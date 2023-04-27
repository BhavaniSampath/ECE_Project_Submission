#include <string>
#include <list>
#include <map>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

typedef struct coefficient_t  
{
    int sign;
    int numerator;
    int denominator; 
} coefficient_t; 

typedef vector<tuple<string, int>> monomial_t;

typedef struct term_t
{
    coefficient_t coefficient;
    monomial_t monomial;
} term_t;

typedef list<term_t> polynomial_t;

coefficient_t coeffMakeCoefficient_Types (bool bIsNegative, int numerator, int denominator);
monomial_t monomMakeMonomial_Types (vector<string> partsOfMonomial);
bool monomLexicoCompare_Types (const tuple<string, int> &monomBegin, const tuple<string, int> &monomEnd);
int nDegreeOfMonomial_Types(monomial_t monomial);
int nWeightedDegreeOfMonomial_Types(monomial_t monomial);
term_t termMakeTerm_Types (coefficient_t coefficient, monomial_t monomial);
term_t termMakeForPolynomials_Types (vector<string> partsOfMonomial,
                                       bool bIsNegative,
                                       vector<string> numeratorAndDenominator);
polynomial_t polyMakePolynomial_Types (map<string, string> m);
bool polyLexicoCompare_Types (const term_t &polyBegin, const term_t &polyEnd);
bool polyDegreeLexicoCompare_Types (const term_t &polyBegin, const term_t &polyEnd);
bool polyDegreeRevLexicoCompare_Types (const term_t &polyBegin, const term_t &polyEnd);
void vPolyIntToDigital_Types (polynomial_t &polynomial);
string sPolyAsString (polynomial_t poly);