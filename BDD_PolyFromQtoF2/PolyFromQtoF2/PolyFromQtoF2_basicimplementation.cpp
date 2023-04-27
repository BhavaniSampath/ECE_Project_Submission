/*
 * Bhavani Sampath
 * University of Utah
 * College of Engineering
 * Electrical and Computer Engineering Department
 * bhavani.sampathkumar@utah.edu
 * sbhavanipriya@gmail.com
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
#include "/home/bhavani/My_Workspace/tools/cudd-3.0.0/cudd/cudd.h"
#include "/home/bhavani/My_Workspace/tools/cudd-3.0.0/cplusplus/cuddObj.hh"
#include<map>
using namespace std;
using namespace std::chrono;


bool isConstant(polynomial_t poly);
bool isTerm(polynomial_t poly);
BDD getConstantAsBDD(Cudd &mgr,polynomial_t poly);
BDD getTermAsBDD(Cudd &mgr,polynomial_t poly,std::map<tuple<string,int>,BDD> &uvarMap);
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable);
BDD polyFromQtoF2(Cudd &mgr,polynomial_t poly,int list_counter,std::map<tuple<string,int>,BDD> &uvarMap);
polynomial_t XOR(polynomial_t ptilda,polynomial_t gtilda);
polynomial_t AND_var(polynomial_t poly,tuple<string,int> variable);
bool isTermConstant(term_t term);
polynomial_t convertStringToPoly(string s);
bool isTermEqual(term_t term_p,term_t term_g);
polynomial_t hPlusg(polynomial_t p,polynomial_t g);
map<string, int>varFreq (polynomial_t poly);
tuple<string, int> Division(polynomial_t poly, tuple<string, int> variable);
//monomial_t map_sort(map<string, int>& M);
monomial_t return_sorted_list(map<string,int> M);


extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;
extern map<string, polynomial_t> gmBasis;
monomial_t sorted_variable_list;
monomial_t variable2_list;
monomial_t temp_mono;
bool bIsNegative;
int counter=0;
std::map<tuple<string,int>,BDD> uvarMap;




int main (int argc, char* argv[]) 
{
    Cudd mgr;
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

    //variable list  in polynomial  
    for (map <string,int> :: iterator itr_map2 = gmPrimaryInputLexRank.begin(); itr_map2!= gmPrimaryInputLexRank.end(); itr_map2++)
    {
        string var;
        var =  itr_map2->first;
        variable2_list.push_back(tuple<string, int>(var,1));
        
        //cout << "Given variable is: " << var << ":" <<"number:"<< numerical << endl;
    }
    for(int i=0;i<variable2_list.size();i++){
        //BDD* varBdd = new BDD(mgr.bddVar());
        BDD varBdd = mgr.bddVar();
        uvarMap[variable2_list[i]] = varBdd;
        

    }


    BDD return_poly = polyFromQtoF2(mgr,polynomial,counter,uvarMap);
    cout<<"Output expression:"<<endl;
    Cudd_PrintMinterm(mgr.getManager(), return_poly.getNode());

/*     polynomial_t::iterator it3;
    BDD addBDD=mgr.bddZero();
    for(it3=polynomial.begin();it3!=polynomial.end(); ++it3)
    {
        term_t term_it = *it3;
        vector<string> st1;
        BDD polytoBDD=mgr.bddOne();

        for(int i=0;i<term_it.monomial.size();i++){
            if(get<int>(term_it.monomial[i])==1)
            {

                polytoBDD =polytoBDD & uvarMap[term_it.monomial[i]];
                
            }
            
        }
        addBDD =addBDD | polytoBDD;
    

    }  */
        

        

    
    //addBDD=uvarMap["a_0"];
    //Cudd_PrintMinterm(mgr.getManager(), addBDD.getNode());
  

 /*    for(auto it = uvarMap.begin(); it != uvarMap.end(); ++it) {
        delete it->second;
    } */






/*
    
    for(int mono_iter=0;mono_iter<variable2_list.size();mono_iter++)
    {
        cout<<"variable:"<<get<string>(variable2_list[mono_iter])<<endl;
        cout<<"presence:"<<get<int>(variable2_list[mono_iter])<<endl;
*/       



    uvarMap.clear();

    return 0;
}

/*Recurrsion Funtion*/


BDD polyFromQtoF2(Cudd &mgr,polynomial_t poly,int list_counter,std::map<tuple<string,int>,BDD> &uvarMap)
{
    int var_index1;
/*
    Send out g and p to obtain ~g and ~p
    ~f = ((~p^~g)xi)^~g
*/


   if (isConstant(poly))
   {
    cout<<"inside isconstant:";
    return getConstantAsBDD(mgr,poly); 
    cout<<"outside isconstant:";
   }


   else if(isTerm(poly))
   {
    cout<<"inside isTerm:";
    return getTermAsBDD(mgr,poly,uvarMap); 
    cout<<"outside isterm:";
   }


   //Getting the variable and performing division
   tuple<string,int> variable=variable2_list[list_counter];
   tuple<polynomial_t, polynomial_t> divTuple = variableDivision(poly, variable);
   
   string temp="0";
   //cout<<"Getting g and h poly:"<<endl;
   polynomial_t h_poly = get<0>(divTuple);
   polynomial_t g_poly = get<1>(divTuple);

   polynomial_t g_polydash=g_poly;
   vector<string> temp_term = vtGetTerms_File(temp);
   map<string, string> temp_coefficientsAndMonomials = mGetCoefficientsAndMonomials_File(temp_term);
   polynomial_t temp_polynomial = polyMakePolynomial_Types (temp_coefficientsAndMonomials);
   
   cout << "h_poly:"<<""<< sPolyAsString(h_poly) << endl; 
   cout<< "g_poly:" << sPolyAsString(g_poly) <<""<<endl;
   
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
    counter=counter+1;
    
    //Recurrsion starts
    //cout << "Recurse g:" << endl;
    BDD g_tilda = polyFromQtoF2(mgr,g_poly, list_counter,uvarMap);
    cout<<"Intermediate expression1:"<<endl;
    Cudd_PrintMinterm(mgr.getManager(), g_tilda.getNode());

    BDD p_tilda = polyFromQtoF2(mgr,p_poly, list_counter,uvarMap);
    cout<<"Intermediate expression2:"<<endl;
    Cudd_PrintMinterm(mgr.getManager(), p_tilda.getNode());
    

    //BDD g_tilda_dash=g_tilda;
    //Reforming as F2 polynomial
    // polynomial_t f_tilde1=XOR(p_tilda,g_tilda);
    // polynomial_t f_tilde2=AND_var(f_tilde1,variable);
    // polynomial_t ftilde=XOR(f_tilde2,g_tilda_dash);
    //cout<<"ftilde:"<< sPolyAsString(ftilde) << endl;
    BDD ftilda=((p_tilda ^ g_tilda) & (uvarMap[variable]))^g_tilda;
    //cout<<"Final expression expression with :"<<temp_variable<<endl;
    //Cudd_PrintMinterm(mgr.getManager(), ftilda.getNode());


    
    return ftilda;
   

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


BDD getConstantAsBDD(Cudd &mgr,polynomial_t poly)
{
    polynomial_t::iterator iter = poly.begin();
    advance(iter, 0);
    term_t term = *iter;
    BDD cons_BDD;

    if (term.coefficient.numerator != 0)
    {
        cons_BDD=mgr.bddOne();
    }
    else
    {
        cons_BDD=mgr.bddZero();
    }
    
    cout<<"Constatnt BDD";
    Cudd_PrintMinterm(mgr.getManager(),cons_BDD.getNode());
    return cons_BDD;

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
BDD getTermAsBDD(Cudd &mgr,polynomial_t poly,std::map<tuple<string,int>,BDD> &uvarMap)
{
    polynomial_t::iterator iter = poly.begin();
    term_t term_temp=*iter;
    BDD tilda=mgr.bddOne();
    for(int i=0;i<term_temp.monomial.size();i++){
        //cout<<"monomial:"<<get<string>(term_temp.monomial[i])<<endl;
        for(int i=0;i<term_temp.monomial.size();i++){
            if(get<int>(term_temp.monomial[i])==1)
            {

                tilda =tilda & uvarMap[term_temp.monomial[i]];
                
            }
            
        }

    }

    Cudd_PrintMinterm(mgr.getManager(),tilda.getNode());
    return tilda;
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

    for(int list_num=0;list_num<variable2_list.size();list_num++)
    {
        auto result1 = find(monomial_p.begin(), monomial_p.end(), variable2_list[list_num]);
        //cout<<"list_var:"<<get<string>(variable2_list[list_num])<<endl;
        //cout<<"p_var:"<<get<int>(*result1)<<endl;
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
            //cout<<"p_count:"<<count1<<endl<<"g_count:"<<count2<<endl;
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


            //cout<<"positive"<<endl;
            i_num=((i_num*term_h.coefficient.denominator)+(term_h.coefficient.numerator*i_denom));
            i_denom=(term_h.coefficient.denominator*i_denom);
            //cout<<"constant value:"<<i_num<<""<<i_denom<<endl;
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
            //cout<<"constant value:"<<i_num<<endl;
            term_g.coefficient.numerator=0;
            *iter1=term_g;
        }

    }
    //cout<<"my constant:"<<i_num<<""<<i_denom<<endl;
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
                        //cout<<"terms are equal";
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

//Division by one variable
tuple<string, int> Division(polynomial_t poly, tuple<string, int> variablelist)
{       int count=0;
        polynomial_t :: iterator ip;
        string  var_temp=get<0>(variablelist);
        for(ip=poly.begin(); ip!=poly.end();ip++)
        {
            term_t term=*ip;
            monomial_t m=term.monomial;
        for (int i = 0; i < m.size(); i++) 
            {
             string v=get<0>(m[i]);
             int vf=get<1>(m[i]);
             if(v==var_temp && vf!=0)
             {
              count=count+1;
              //cout<<"count"<<count;
             }
    
            }
        }
       tuple<string, int> newvariablelist=make_tuple(var_temp,count);
       return newvariablelist;
}


//  Determining frequency of all variables in the polynomial
map<string, int> varFreq(polynomial_t poly) 
{
    map<string,int>initialvarlist;
    map<string,int>newvarlist;
    map <string,int> :: iterator itr;

for (itr = gmPrimaryInputLexRank.begin(); itr!= gmPrimaryInputLexRank.end(); itr++)
{
   initialvarlist.insert({(*itr).first,0});
}

for (itr = initialvarlist.begin(); itr!= initialvarlist.end(); itr++)
{
   
  tuple<string,int> myvar=make_tuple((*itr).first,(*itr).second);
  tuple<string, int>div = Division(poly, myvar);
    string v = get<0>(div);
    int vf = get<1>(div);
    newvarlist.insert({ v, vf });

}
        

 return newvarlist;

          
}

// Comparator function to sort pairs
// according to second value
bool cmp(pair<string, int>& a,
         pair<string, int>& b)
{
    return a.second < b.second;
}

// Function to sort the map according
// to value in a (key-value) pairs
// void sort(map<string, int>& M)
// {
//     string temp_store;
//     // Declare vector of pairs
//     vector<pair<string, int> > A;
//     monomial_t new_variable_list;
  
//     // Copy key-value pair from Map
//     // to vector of pairs
//     for (auto& it : M) 
//     {
//         A.push_back(it);
//     }
  
//     // Sort using comparator function
//     sort(A.begin(), A.end(), cmp);
  
//     // Print the sorted value
//     for (auto& it : A) 
//     {
//         cout << it.first << ' '<< it.second << endl;

//     }
//     return 0
// }


// void sort(map<string, int>& M)
// {

//     // Declare a multimap
//     multimap<int, string> MM;
  
//     // Insert every (key-value) pairs from
//     // map M to multimap MM as (value-key)
//     // pairs
//     for (auto& it : M) {
//         MM.insert({ it.second, it.first });
//     }
  
//     // // Print the multimap
//     // for (auto& it : MM) 
//     // {
//     //     temp_store=it.second;
//     //     //cout<<temp_store<<endl;
//     //     //tuple<string,int>temp_tuple=make_tuple(temp_store,1);
//     //     new_variable_list.push_back(tuple<string, int>(temp_store,1));
//     // }
//     // for(auto& it1:new_variable_list)
//     // {
//     //     cout<<get<string>(it1)<<endl;
//     // }


// }

monomial_t return_sorted_list(map<string,int> M)
{
    string temp_store;
    //vector<tuple<string,int>>new_variable_list;
    monomial_t new_variable_list;
    multimap<int, string> MM;
    for (auto& it : M) {
        MM.insert({ it.second, it.first });
    }
    // Print the multimap
    for (auto& it : MM) 
    {
        temp_store=it.second;
        //cout<<temp_store<<endl;
        //tuple<string,int>temp_tuple=make_tuple(temp_store,1);
        new_variable_list.push_back(tuple<string, int>(temp_store,1));
    }

    return new_variable_list;

}
