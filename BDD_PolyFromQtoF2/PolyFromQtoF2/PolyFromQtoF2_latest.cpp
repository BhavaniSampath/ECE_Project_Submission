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
#include <typeinfo>
using namespace std;

bool isConstant(polynomial_t poly);
bool isTerm(polynomial_t poly);
polynomial_t getConstantAsPolynomial(polynomial_t poly);
polynomial_t getTermAsPolynomial(polynomial_t poly);
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable);
polynomial_t polyFromQtoF2(polynomial_t poly,int list_counter);
polynomial_t hPlusg(polynomial_t h,polynomial_t g);
polynomial_t AND_var(polynomial_t poly,tuple<string,int> variable);

extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;
extern map<string, polynomial_t> gmBasis;
monomial_t variable_list;
monomial_t temp_mono;
bool bIsNegative;


int main (int argc, char* argv[]) 
{
    variable_list.push_back(tuple<string, int>("a_0",1));
    variable_list.push_back(tuple<string, int>("a_1",1));
    variable_list.push_back(tuple<string, int>("b_0",1));
    variable_list.push_back(tuple<string, int>("b_1",1));
    temp_mono.push_back(tuple<string, int>("0",0));
    
/*  
    for(auto& tuple:variable_list){
        cout<<"variable:"<<get<0>(tuple)<<endl;
    }
*/
    int counter=0;
    vReadFile_File(argc, argv);
    string sPolyName;
    polynomial_t polynomial;

    for(std::map<string, polynomial_t>::iterator iterMap = gmBasis.begin(); iterMap != gmBasis.end(); ++iterMap)
    {
        sPolyName =  iterMap->first;
        polynomial = iterMap->second;
        string sPoly = sPolyAsString (polynomial);
        cout << "Given polynomial is " << sPolyName << ":" << sPoly << endl;

        // // Test variable division
        // tuple<polynomial_t, polynomial_t> divTuple = variableDivision(polynomial, variable_list[1]);
        // string quo = sPolyAsString(get<0>(divTuple));
        // string rem = sPolyAsString(get<1>(divTuple));
        // polynomial_t quotient = get<0>(divTuple);
        // polynomial_t remainder =get<1>(divTuple);
        // polynomial_t temp_polynomial=hPlusg(quotient,remainder);
        // polynomial_t var_mult=AND_var(temp_polynomial,variable_list[0]);
        // polynomial_t ftilde=hPlusg(var_mult,remainder);
        // cout << "Quotient is: " << quo << endl;
        // cout << "Remainder is: " << rem << endl;
        // //cout<<"poly_merge:"<<""<<sPolyAsString(ftilde);
    }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    polynomial_t return_poly = polyFromQtoF2(polynomial,counter);
    string f_poly=sPolyAsString (return_poly);
    cout << "Output polynomial is: " << sPolyName << ":" << f_poly << endl;


    // // Test if should get variety
    //cout << "It is a constant? " << isConstant(polynomial) << endl;
    //cout << "What is the variety? " << sPolyAsString(getConstantAsPolynomial(polynomial)) << endl;
    //cout << "Is it a term? " << isTerm(polynomial) << endl; 
    // cout << "What is the variety? " << sPolyAsString(getTermAsPolynomial(polynomial)) << endl;






    return 0;
}

/*Recurrsion Funtion*/


polynomial_t polyFromQtoF2(polynomial_t poly,int list_counter)
{
/*
    Send out g and p to obtain ~g and ~p
    ~f = ((~p^~g)xi)^~g
*/
   if (isConstant(poly))
   {
    return getConstantAsPolynomial(poly); 
   }
   else if(isTerm(poly))
   {
    return getTermAsPolynomial(poly); 
   }
   monomial_t::size_type sz = variable_list.size();
   tuple<string,int> variable=variable_list[list_counter];
   tuple<polynomial_t, polynomial_t> divTuple = variableDivision(poly, variable);
   string temp="0";
   polynomial_t h_poly = get<0>(divTuple);
   polynomial_t g_poly = get<1>(divTuple);
   vector<string> temp_term = vtGetTerms_File(temp);
   map<string, string> temp_coefficientsAndMonomials = mGetCoefficientsAndMonomials_File(temp_term);
   polynomial_t temp_polynomial = polyMakePolynomial_Types (temp_coefficientsAndMonomials);
   //cout<<temp_polynomial.size()<<endl;
   //cout << "h_poly" <<h_poly.size()<<""<< sPolyAsString(h_poly) << " " << "g_poly" << sPolyAsString(g_poly) <<""<< g_poly.size() <<endl;
   polynomial_t p= hPlusg(h_poly,g_poly);
   if(p.size()==0)
   {
        p=temp_polynomial;
   }
    if(g_poly.size()==0)
    {
        g_poly=temp_polynomial;
    }
    list_counter = list_counter + 1;
    //cout << "Recurse g:" << endl;
    polynomial_t g_tilda = polyFromQtoF2(g_poly, list_counter);
    //cout << "Recurse p:" << endl;
    polynomial_t p_tilda = polyFromQtoF2(p, list_counter);
    //cout<<"F2 ppoly:"<< sPolyAsString(p_tilda) << "F2 gpoly" << sPolyAsString(g_tilda) << endl;
    polynomial_t f_tilde1=hPlusg(p_tilda,g_tilda);
    polynomial_t f_tilde2=AND_var(f_tilde1,variable);
    polynomial_t ftilde=hPlusg(f_tilde2,g_tilda);
    return ftilde;
   

}


/*
 * A Base Case for Recursion
 */
bool isConstant(polynomial_t poly)
{
    if (poly.size() == 1)
    {
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
    polynomial_t::iterator iter;
    for(iter=poly.begin();iter != poly.end(); ++iter)
    {
        term_t term=*iter;
        monomial_t monomial = term.monomial;
        for (tuple<string,int> variable: monomial)
        {
            if(get<int>(variable) != 0)
            {
                return false;
            }
        }
        
    }
    return true;

}
    

    


/*
bool isConstant(polynomial_t poly)
{

    if (!isTerm(poly))
    {
        cout<<"its not a term";
        return false;
    }

    else if(poly.size()==1)
    {
        
        return true;
    }

    return false;
}
*/
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

polynomial_t hPlusg(polynomial_t h,polynomial_t g){
    polynomial_t p;
    p=h;
    polynomial_t::iterator iter;
    for(iter=g.begin();iter != g.end(); ++iter)
    {
        term_t term = *iter;
        if(term.coefficient.numerator!=0)
        {
            p.push_back(term);
        }
        
    }

    return p;


}

polynomial_t AND_var(polynomial_t poly,tuple<string,int> variable)
{
    polynomial_t ftilde_2;
    polynomial_t::iterator iter;
    for(iter=poly.begin();iter != poly.end(); ++iter)
    {
       term_t term = *iter; 
       term.monomial.push_back(variable);
       ftilde_2.push_back(term);

    }

    return ftilde_2;
}
