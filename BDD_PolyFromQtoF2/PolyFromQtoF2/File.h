#include <bits/stdc++.h>
#include <string>
using namespace std;

bool bCheckFileExt_File(string s);
bool bCheckIfPoly_File(string s);
bool bCheckIfRing_File(string s);
void vReadFile_File(int argc, char* argv[]);
vector<string> vtGetTerms_File(string s);
map<string, string> mGetCoefficientsAndMonomials_File(vector<string> v);
bool bCoefficientIsNegative_File(string s);
vector<string> vtGetExpression_File(string s);
vector<string> vtGetNumeratorAndDenominator_File(string s);
vector<string> vtGetPartsOfMonomial_File(string s);
int nGetEncodingForOrder_File (string ring);
void vGetPrimaryInputLexOrder_File(string ring);
