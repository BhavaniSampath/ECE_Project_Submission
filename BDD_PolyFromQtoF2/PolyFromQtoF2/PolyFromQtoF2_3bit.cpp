

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
polynomial_t XOR(polynomial_t ptilda,polynomial_t gtilda);
polynomial_t AND_var(polynomial_t poly,tuple<string,int> variable);
bool isTermConstant(term_t term);
polynomial_t convertStringToPoly(string s);
bool isTermEqual(term_t term_p,term_t term_g);
polynomial_t hPlusg(polynomial_t p,polynomial_t g);


extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;
extern map<string, polynomial_t> gmBasis;
monomial_t variable_list;
monomial_t variable2_list;
monomial_t temp_mono;
bool bIsNegative;


int main (int argc, char* argv[]) 
{
    variable_list.push_back(tuple<string, int>("a0",1));
    variable_list.push_back(tuple<string, int>("a1",1));
    variable_list.push_back(tuple<string, int>("a2",1));
    variable_list.push_back(tuple<string, int>("b0",1));
    variable_list.push_back(tuple<string, int>("b1",1));
    variable_list.push_back(tuple<string, int>("b2",1));



    variable2_list.push_back(tuple<string, int>("a0",1));
    variable2_list.push_back(tuple<string, int>("a1",1));
    variable2_list.push_back(tuple<string, int>("a2",1));
    variable2_list.push_back(tuple<string, int>("b0",1));
    variable2_list.push_back(tuple<string, int>("b1",1));
    variable2_list.push_back(tuple<string, int>("b2",1));




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
    }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
    polynomial_t return_poly = polyFromQtoF2(polynomial,counter);
    string f_poly=sPolyAsString (return_poly);
    cout << "Output polynomial is: " << sPolyName << ":" << f_poly << endl;


    // // Test if should get variety
    //cout << "It is a constant? " << isConstant(polynomial) << endl;
    //cout << "What is the variety? " << sPolyAsString(getConstantAsPolynomial(polynomial)) << endl;
    //cout << "Is it a term? " << isTerm(polynomial) << endl; 
    // cout << "What is the variety? " << sPolyAsString(getTermAsPolynomial(polynomial)) << endl;
    // polynomial_t::iterator iter = polynomial.begin();
    // advance(iter, 0);
    // term_t term_temp = *iter;
    // tuple<string,int> tuple_temp=term_temp.monomial[0];

    // // //Test variable division
    // cout<<"entering division"<<endl;
    // tuple<polynomial_t, polynomial_t> divTuple = variableDivision(polynomial, variable_list[0]);
    // string quo = sPolyAsString(get<0>(divTuple));
    // string rem = sPolyAsString(get<1>(divTuple));
    // polynomial_t quotient = get<0>(divTuple);
    // polynomial_t remainder =get<1>(divTuple);
    // polynomial_t rem_copy=remainder;
    // polynomial_t temp_polynomial=hPlusg(quotient,remainder);
    // polynomial_t temp_polynomial=XOR(quotient,remainder);
    // polynomial_t var_mult=AND_var(temp_polynomial,variable_list[0]);
    // polynomial_t ftilda=XOR(var_mult,rem_copy);
    // cout << "Quotient is: " << quo << endl;
    // cout << "Remainder is: " << rem << endl;
    // cout<<"h+g:"<<sPolyAsString(temp_polynomial)<<endl;
    // cout << "OR result is:"<< sPolyAsString(temp_polynomial) << endl;
    // cout << "AND result is: " << sPolyAsString(var_mult) << endl;
    // cout<<"poly_merge:"<<""<<sPolyAsString(ftilda);



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
    cout<<"inside isconstant:";
    return getConstantAsPolynomial(poly); 
   }


   else if(isTerm(poly))
   {
    cout<<"inside isTerm:";
    return getTermAsPolynomial(poly); 
   }


   //Getting the variable and performing division
   tuple<string,int> variable=variable_list[list_counter];
   tuple<polynomial_t, polynomial_t> divTuple = variableDivision(poly, variable);
   
   string temp="0";
   polynomial_t h_poly = get<0>(divTuple);
   polynomial_t g_poly = get<1>(divTuple);
   polynomial_t g_polydash=g_poly;
   vector<string> temp_term = vtGetTerms_File(temp);
   map<string, string> temp_coefficientsAndMonomials = mGetCoefficientsAndMonomials_File(temp_term);
   polynomial_t temp_polynomial = polyMakePolynomial_Types (temp_coefficientsAndMonomials);


   cout << "h_poly"<<""<< sPolyAsString(h_poly) << " " << "g_poly" << sPolyAsString(g_poly) <<""<<endl;
   
   //Calculating P poly
   polynomial_t p_poly= hPlusg(h_poly,g_polydash);
   cout<<"p_poly:"<<sPolyAsString(p_poly)<<endl;
   
   if(p_poly.size()==0)
   {
    p_poly=temp_polynomial;
    }
    if(g_poly.size()==0)
    {
        g_poly=temp_polynomial;
    }
    list_counter = list_counter + 1;
    
    //Recurrsion starts
    cout << "Recurse g:" << endl;
    polynomial_t g_tilda = polyFromQtoF2(g_poly, list_counter);
    cout<<"g_tilda" << sPolyAsString(g_tilda)<<endl;
    cout << "Recurse p:" << endl;
    polynomial_t p_tilda = polyFromQtoF2(p_poly, list_counter);
    cout<<"p_tilda:"<< sPolyAsString(p_tilda) << endl;

    polynomial_t g_tilda_dash=g_tilda;
    //Reforming as F2 polynomial
    polynomial_t f_tilde1=XOR(p_tilda,g_tilda);
    polynomial_t f_tilde2=AND_var(f_tilde1,variable);
    polynomial_t ftilde=XOR(f_tilde2,g_tilda_dash);
    
    return ftilde;
   

}


/*
 * A Base Case for Recursion
 */
// bool isConstant(polynomial_t poly)
// {
//     if (poly.size() == 1)
//     {
//         polynomial_t::iterator iter = poly.begin();
//         advance(iter, 0);
//         term_t term = *iter;
//         monomial_t monomial = term.monomial;

//         for (tuple<string,int> variable: monomial)
//         {
//             if(get<int>(variable) != 0)
//             {
//                 return false;
//             }
//         }
//         return true;
//     }
//     else
//     {
//         polynomial_t::iterator iter;
//         for(iter=poly.begin();iter != poly.end(); ++iter)
//         {
//             term_t term=*iter;
//             monomial_t monomial = term.monomial;
//             for (tuple<string,int> variable: monomial)
//             {
//             if(get<int>(variable) != 0)
//             {
//                 return false;
//             }
//             }
        
//         }
//     }
    
//     return true;

// }
    

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


bool isTermConstant(term_t term)
{
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
 * Divides polynomial by a variable. Returns a tuple with quotient and remainder.
 */
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable)
{
    polynomial_t quotient;
    polynomial_t remainder;
    polynomial_t::iterator div_iter;
    for(div_iter=poly.begin();div_iter!=poly.end();++div_iter)
    {
        term_t term_div=*div_iter;
        auto result = find(term_div.monomial.begin(), term_div.monomial.end(), variable);
        if(result != term_div.monomial.end())
        {
            get<int>(*result) = 0;
            quotient.push_back(term_div);
        }
        else
        {
            remainder.push_back(term_div);
        }

    }

    return make_tuple(quotient, remainder);
}



//check terms are equal
bool isTermEqual(term_t eq_term_p,term_t eq_term_g,monomial_t variable2_list)
{
    int count1=0,count2=0;
    monomial_t monomial_p=eq_term_p.monomial;
    monomial_t monomial_g=eq_term_g.monomial;

    //cout<<"monomials are of same size:"<<endl;
    // for(int list_num=0;list_num<4;list_num++)
    // {
    //     cout<<"list_var:"<<get<string>(variable2_list[list_num])<<endl;
    // }

    for(int list_num=0;list_num<6;list_num++)
    {
        auto result1 = find(monomial_p.begin(), monomial_p.end(), variable2_list[list_num]);
        cout<<"list_var:"<<get<string>(variable2_list[list_num])<<endl;
        cout<<"p_var:"<<get<int>(*result1)<<endl;
        if(result1 != monomial_p.end())
        {
            count1++;

            auto result2 = find(monomial_g.begin(), monomial_g.end(), variable2_list[list_num]);
            if(result2 != monomial_g.end())
            {
                count2++;
                //cout<<"g_var:"<<get<string>(*result2)<<endl;
                //cout<<"g_var:"<<get<int>(*result2)<<endl;
            }
            cout<<"p_count:"<<count1<<endl<<"g_count:"<<count2<<endl;
            if(count1!=count2)
            {
                return false;
            }
            count1=0;
            count2=0;

        }
        else
        {

            auto result2 = find(monomial_g.begin(), monomial_g.end(), variable2_list[list_num]);
            if(result2 != monomial_g.end())
            {
                return false;
            }    

        }
    }
    return true;

 
}




//create a ppolynomial if given a string
polynomial_t convertStringToPoly(string s)
{
    vector<string> temp_term = vtGetTerms_File(s);
    map<string, string> temp_coefficientsAndMonomials = mGetCoefficientsAndMonomials_File(temp_term);
    polynomial_t temp_poly = polyMakePolynomial_Types (temp_coefficientsAndMonomials);
    return temp_poly;

}

//Add two polynomial

polynomial_t hPlusg(polynomial_t p,polynomial_t g)
{
    int i_num=0,i_denom=1;
    polynomial_t addedpoly;
    polynomial_t::iterator iter,iter1;
    for (iter=p.begin();iter!=p.end();++iter)
    {
        term_t term_h=*iter;
        if(isTermConstant(term_h))
        {


            cout<<"positive"<<endl;
            i_num=((i_num*term_h.coefficient.denominator)+(term_h.coefficient.numerator*i_denom));
            i_denom=(term_h.coefficient.denominator*i_denom);
            cout<<"constant value:"<<i_num<<""<<i_denom<<endl;
            term_h.coefficient.numerator=0;
            *iter=term_h;
        }

    }
    for (iter1=g.begin();iter1!=g.end();++iter1)
    {
        term_t term_g=*iter1;
        if(isTermConstant(term_g))
        {
            i_num=((i_num*term_g.coefficient.denominator)+(term_g.coefficient.numerator*i_denom));
            i_denom=(term_g.coefficient.denominator*i_denom);
            cout<<"constant value:"<<i_num<<endl;
            term_g.coefficient.numerator=0;
            *iter1=term_g;
        }

    }
    cout<<"my constant:"<<i_num<<""<<i_denom<<endl;
    if(i_num!=0)
    {
        addedpoly=convertStringToPoly("1");
        polynomial_t::iterator con_iter;
        for(con_iter=addedpoly.begin();con_iter!=addedpoly.end();++con_iter)
        {
            term_t con_term=*con_iter;
            con_term.coefficient.numerator=i_num;
            con_term.coefficient.denominator=i_denom;
            *con_iter=con_term;
        }
    }

    polynomial_t::iterator iter2,iter3;
    for(iter2=p.begin();iter2!= p.end(); ++iter2)
    {
        term_t term = *iter2;
        if(term.coefficient.numerator!=0)
        {
            addedpoly.push_back(term);
        }
    }
    for(iter3=g.begin();iter3!= g.end(); ++iter3)
    {
        term_t term2 = *iter3;
        if(term2.coefficient.numerator!=0)
        {
            addedpoly.push_back(term2);
        }
    }
    return addedpoly;
    

}


//XOR two polynomial
polynomial_t XOR(polynomial_t ptilda,polynomial_t gtilda)
{
    int j=0,count=0;
    polynomial_t polyXOR;
    polynomial_t::iterator xorIter1,xorIter2;
    for(xorIter1=ptilda.begin();xorIter1!=ptilda.end(); ++xorIter1)
    {
        term_t term_xor = *xorIter1;
        if(isTermConstant(term_xor))
        {
            j+=(term_xor.coefficient.numerator);
            term_xor.coefficient.numerator=0;
            *xorIter1=term_xor;
        }
        
    }
    for(xorIter2=gtilda.begin();xorIter2!=gtilda.end(); ++xorIter2)
    {
        term_t term_xor2 = *xorIter2;
        if(isTermConstant(term_xor2))
        {
            j+=(term_xor2.coefficient.numerator);
            term_xor2.coefficient.numerator=0;
            *xorIter2=term_xor2;
        }
        
    }
    //cout<<"constant value:"<<j<<endl;
    if(j%2!=0)
    {
        string one="1";
        polyXOR=convertStringToPoly(one);

    }
    
    //cout<<"after removing constant:"<<sPolyAsString(gtilda)<<endl;
    //cout<<"after removing constant:"<<sPolyAsString(ptilda)<<endl;

    polynomial_t::iterator xorIter3,xorIter4;
    for(xorIter3=ptilda.begin();xorIter3!=ptilda.end(); ++xorIter3)
    {
        term_t term_xor3 = *xorIter3;
        count=0;
        if(term_xor3.coefficient.numerator!=0)
        {
           for(xorIter4=gtilda.begin();xorIter4!=gtilda.end(); ++xorIter4)
           {
                term_t term_xor4= *xorIter4;
                if(term_xor4.coefficient.numerator!=0)
                {
                    if(isTermEqual(term_xor3,term_xor4,variable2_list))
                    {
                        cout<<"terms are equal";
                        term_xor3.coefficient.numerator=0;
                        term_xor4.coefficient.numerator=0;
                        *xorIter3=term_xor3;
                        *xorIter4=term_xor4;
                        break;
                    }
                    count++;

                }
                else
                {
                    count++;
                }
                //cout<<"count size:"<<count<<endl;;
                //cout<<"poly size:"<<gtilda.size()<<endl;;
                if(count==gtilda.size())
                {
                    polyXOR.push_back(term_xor3);
                }
                //cout<<"polyxor:"<<sPolyAsString(polyXOR)<<endl;;
           } 
        }
    }
    polynomial_t::iterator xorIter5;
    for(xorIter5=gtilda.begin();xorIter5!=gtilda.end(); ++xorIter5)
    {
        term_t term_xor5 = *xorIter5;
        if(term_xor5.coefficient.numerator!=0)
        {
            polyXOR.push_back(term_xor5);
        }

    }
    return polyXOR;


}
// polynomial_t AND_var(polynomial_t poly,tuple<string,int> variable)
// {
//     polynomial_t ftilde_2;
//     polynomial_t::iterator iter;
//     for(iter=poly.begin();iter != poly.end(); ++iter)
//     {
//        term_t term = *iter; 
//        term.monomial.push_back(variable);
//        ftilde_2.push_back(term);

//     }

//     return ftilde_2;
// }



polynomial_t AND_var(polynomial_t poly,tuple<string,int> variable)
{
    int count=0;
    polynomial_t ftilde_2;
    polynomial_t::iterator iter2;
    for(iter2=poly.begin();iter2!=poly.end();++iter2)
    {
        term_t term_temp=*iter2;
        //cout<<"monomial size"<<term_temp.monomial.size()<<endl;
        for(int i=0;i<term_temp.monomial.size();i++)
        {
            //cout<<"monomial:"<<get<string>(term_temp.monomial[i])<<endl;
            if(get<string>(term_temp.monomial[i])==get<string>(variable))
            {
                //cout<<"found my variable";
                get<int>(term_temp.monomial[i])=1;
                //cout<<"value:"<<get<int>(var);
            }
            else
            {
                count++;
            }

        }
        if(count==term_temp.monomial.size())
        {
            term_temp.monomial.push_back(variable);
        }
        ftilde_2.push_back(term_temp);

    }
    
    return ftilde_2;         

}

