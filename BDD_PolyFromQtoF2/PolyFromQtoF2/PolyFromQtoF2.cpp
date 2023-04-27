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
#include "../../cudd/cudd.h"
#include "../../cplusplus/cuddObj.hh"
#include<map>
using namespace std;
using namespace std::chrono;


bool isConstant(polynomial_t poly);
bool isTerm(polynomial_t poly);
BDD getConstantAsBDD(Cudd &mgr,polynomial_t poly);
BDD getTermAsBDD(Cudd &mgr,polynomial_t poly,std::map<tuple<string,int>,BDD> &uvarMap);
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable);
BDD polyFromQtoF2(Cudd &mgr,polynomial_t poly,int list_counter,std::map<tuple<string,int>,BDD> &uvarMap);
bool isTermConstant(term_t term);
polynomial_t convertStringToPoly(string s);
polynomial_t hPlusg(polynomial_t p,polynomial_t g);
map<string, int>varFreq (polynomial_t poly);
tuple<string, int> Division(polynomial_t poly, tuple<string, int> variable);
monomial_t return_sorted_list(map<string,int> M);
void printBDDInfo(const Cudd& manager, const BDD& bdd,int nvars);



extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;
extern map<string, polynomial_t> gmBasis;
monomial_t sorted_variable_list;
monomial_t variable2_list;
monomial_t temp_mono;
bool bIsNegative;
std::map<tuple<string,int>,BDD> uvarMap;
int counter1=0;




int main (int argc, char* argv[]) 
{
    Cudd mgr;
    vReadFile_File(argc, argv);
    string sPolyName;
    polynomial_t polynomial;

    //mgr.AutodynEnable(CUDD_REORDER_SAME);

    //variable list  in polynomial  
    for (map <string,int> :: iterator itr_map2 = gmPrimaryInputLexRank.begin(); itr_map2!= gmPrimaryInputLexRank.end(); itr_map2++)
    {
        string var;
        var =  itr_map2->first;
        variable2_list.push_back(tuple<string, int>(var,1));
        
        //cout << "Given variable is: " << var << endl;
    }

    //Map between monomial and BDD node
    for(int i=0;i<variable2_list.size();i++){
        //BDD* varBdd = new BDD(mgr.bddVar());
        BDD varBdd = mgr.bddVar();
        uvarMap[variable2_list[i]] = varBdd;
    }

    for(std::map<string, polynomial_t>::iterator iterMap = gmBasis.begin(); iterMap != gmBasis.end(); ++iterMap)
    {
        sPolyName =  iterMap->first;
        polynomial = iterMap->second;
        string sPoly = sPolyAsString (polynomial);
        //cout << "Given polynomial is " << sPolyName << ":" << sPoly << endl;

        //variable frequency  in polynomial
        map<string,int> newFreqlist=varFreq(polynomial);
        monomial_t reverse_sorted_variable_list =return_sorted_list(newFreqlist);
        for(int i=variable2_list.size();i>0;i--)
        {
            
            sorted_variable_list.push_back(reverse_sorted_variable_list[i-1]);
    
        }
        //Timining starts
        auto start = high_resolution_clock::now();
        int counter=0;
        cout<<"recurssion begun"<<endl;
        BDD return_poly = polyFromQtoF2(mgr,polynomial,counter,uvarMap);
        cout<<"Finished recurssion"<<endl;
        cout<<"Output expression:"<<endl;
        Cudd_PrintMinterm(mgr.getManager(), return_poly.getNode());
        printBDDInfo(mgr,return_poly,variable2_list.size());
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
        //cout << "Output polynomial is: " << sPolyName << ":" << f_poly << endl;
        cout<<"Number of Terms:"<<polynomial.size()<<endl;
        //cout<<"Number of Terms:"<<return_poly.size()<<endl;
        cout<<"depth:"<<counter1<<endl;

        


  
    }

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
    
    return getConstantAsBDD(mgr,poly); 
    
   }


   else if(isTerm(poly))
   {
    
    return getTermAsBDD(mgr,poly,uvarMap); 
    
   }


   //Getting the variable and performing division
   tuple<string,int> variable=sorted_variable_list[list_counter];
   tuple<polynomial_t, polynomial_t> divTuple = variableDivision(poly, variable);
   
   string temp="0";
   //cout<<"Getting g and h poly:"<<endl;
   polynomial_t h_poly = get<0>(divTuple);
   polynomial_t g_poly = get<1>(divTuple);

   polynomial_t g_polydash=g_poly;
   vector<string> temp_term = vtGetTerms_File(temp);
   map<string, string> temp_coefficientsAndMonomials = mGetCoefficientsAndMonomials_File(temp_term);
   polynomial_t temp_polynomial = polyMakePolynomial_Types (temp_coefficientsAndMonomials);
   
   //cout << "h_poly:"<<""<< sPolyAsString(h_poly) << endl; 
   //cout<< "g_poly:" << sPolyAsString(g_poly) <<""<<endl;
   
   //Calculating P poly
   polynomial_t p_poly= hPlusg(h_poly,g_polydash);
   //cout<<"p_poly:"<<sPolyAsString(p_poly)<<endl;
   
   if(p_poly.size()==0)
   {
    p_poly=temp_polynomial;
    }
    if(g_poly.size()==0)
    {
        g_poly=temp_polynomial;
    }


    list_counter = list_counter + 1;
    counter1=counter1+1;
    
    //Recurrsion starts
    //cout << "Recurse g:" << endl;
    BDD g_tilda = polyFromQtoF2(mgr,g_poly, list_counter,uvarMap);
    //cout<<"Intermediate expression1:"<<endl;
    //Cudd_PrintMinterm(mgr.getManager(), g_tilda.getNode());

    BDD p_tilda = polyFromQtoF2(mgr,p_poly, list_counter,uvarMap);
    //cout<<"Intermediate expression2:"<<endl;
    //Cudd_PrintMinterm(mgr.getManager(), p_tilda.getNode());

    BDD ftilda=((p_tilda ^ g_tilda) & (uvarMap[variable]))^g_tilda;
    
    



    
    return ftilda;
   

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
 * If poly = 0 return zero BDD as zero.
 * Else return return one BDD.
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
    

    //Cudd_PrintMinterm(mgr.getManager(),cons_BDD.getNode());
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

    //Cudd_PrintMinterm(mgr.getManager(),tilda.getNode());
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


void printBDDInfo(const Cudd& manager, const BDD& bdd,int nvars) {
  std::cout << "Number of nodes in BDD: " << Cudd_DagSize(bdd.getNode()) << std::endl;
  std::cout << "Number of minterms in BDD: " << Cudd_CountMinterm(manager.getManager(),bdd.getNode(),nvars) << std::endl;
}
