/*
 * Bailey Martin
 * University of Utah
 * College of Engineering
 * Electrical and Computer Engineering Department
 * Bailey.Martin@utah.edu
 * Ms.BaileyL.Martin@gmail.com
 */

//when changing the circuit change the number of variable from line 50-67
//change the loop variable in line 385


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
#include<map>
using namespace std;
using namespace std::chrono;
#include "tc_time.h"
#include "puma.h"
#include <string.h>




bool isConstant(polynomial_t poly);
bool isTerm(polynomial_t poly);
utnode* getConstantAsFDD(dd_man* dd_manager,polynomial_t poly);
utnode* getTermAsFDD(dd_man* dd_manager,polynomial_t poly,std::map<tuple<string,int>,utnode*> nodevarMap);
tuple<polynomial_t, polynomial_t> variableDivision(polynomial_t poly, tuple<string, int> variable);
utnode* polyFromQtoF2(dd_man* dd_manager,polynomial_t poly,int list_counter,std::map<tuple<string,int>,utnode*> nodevarMap);
polynomial_t convertStringToPoly(string s);
polynomial_t hPlusg(polynomial_t p,polynomial_t g);
map<string, int>varFreq (polynomial_t poly);
tuple<string, int> Division(polynomial_t poly, tuple<string, int> variable);
monomial_t return_sorted_list(map<string,int> M);



extern map<string, int>  gmPrimaryInputLexRank;
extern int gnEncoding;
extern map<string, polynomial_t> gmBasis;
monomial_t sorted_variable_list;
monomial_t variable2_list;
monomial_t temp_mono;
bool bIsNegative;
std::map<tuple<string,int>,utnode*> nodevarMap;
std::vector<char*> char_pointers;
int counter1=0;




int main (int argc, char* argv[]) 
{
    
    unsigned char		ut_hashsize	= 4;
	unsigned long		ct_hashsize	= 5003;
	unsigned long int	rc_cachesize	= 1000;
	unsigned char		ct_searchlen	= 3;
	unsigned short int	var_lim		= 20000;

    cout<<"Finished reading DD manager variable"<<endl;

    


    // ---------------
	// Init DD-Manager
	// ---------------
    dd_man* dd_manager = OKFDD_Init( ut_hashsize ,
                                         ct_hashsize ,
                                         rc_cachesize,
                                         ct_searchlen,
                                         var_lim    );

    cout<<"Finished Initializing dd manager"<<endl;


    
    vReadFile_File(argc, argv);
    char* DUMPFILENAME ="Test1_fdd.txt";
    string sPolyName;
    polynomial_t polynomial;

    cout<<"Finished reading the input files"<<endl;

    

    //variable list  in polynomial  
    for (map <string,int> :: iterator itr_map2 = gmPrimaryInputLexRank.begin(); itr_map2!= gmPrimaryInputLexRank.end(); itr_map2++)
    {
        string var;
        var =  itr_map2->first;
        variable2_list.push_back(tuple<string, int>(var,1));
        
        cout << "Given variable is: " << var << endl;
    }

    //char pointer to variable string
    for(int i=0;i<variable2_list.size();i++){

           cout<<"creating pointer for"<<i<<"variable"<<endl;
           //string temp_str=get<0>(variable2_list[i]);
           //cout<<static_cast<void*>(&temp_str[0])<<endl;
           char_pointers.push_back(&(get<0>(variable2_list[i]))[0]);
           //cout<<"creating pointer for"<<i<<"variable"<<endl;
    }

    for(auto i:char_pointers){
        cout<<i<<"\t";
    }
    cout<<endl;

    //utnode node pointer and variable Map
    for(int i=0;i<variable2_list.size();i++){

        nodevarMap[variable2_list[i]] = dd_manager->OKFDD_Get_Variable(char_pointers[i],POSITIVE);
        

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
        utnode* return_poly = polyFromQtoF2(dd_manager,polynomial,counter,nodevarMap);
        dd_manager->OKFDD_Store_Root(return_poly);
        dd_manager->OKFDD_PI_DTL_Table[dd_manager->OKFDD_PO_Table(0)] = D_posD;
        for(int i=0;i<5000;i++)
    	{
	    	if (dd_manager->OKFDD_Result[i]==0)
		    {
			    dd_manager->OKFDD_Result[i]=dd_manager->OKFDD_PO_Table(0);
			    cout<<i<<":"<<dd_manager->OKFDD_Result[i]<<endl;
			    break;

		    }   
	    }
        cout<<"label in result table:"<<dd_manager->OKFDD_Result[4]<<"\t"<<"DTL_type:"<<(int)dd_manager->OKFDD_PI_DTL_Table[dd_manager->OKFDD_PO_Table(0)]<<"\n";
        cout << "Vars: " << dd_manager->OKFDD_P_I 	 << "\n";
	    cout << "Outs: " << dd_manager->OKFDD_P_O        << "\n";
	    cout << "Size: " << dd_manager->OKFDD_Size_all() << "\n";
        cout<<"Finished recurssion"<<endl;
        cout<<"Output expression to a file:"<<endl;
        dd_manager-> OKFDD_1_PC_noblif(return_poly,DUMPFILENAME);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
        //cout << "Output polynomial is: " << sPolyName << ":" << f_poly << endl;
        cout<<"Number of Terms:"<<polynomial.size()<<endl;
        //cout<<"Number of Terms:"<<return_poly.size()<<endl;
        cout<<"depth:"<<counter1<<endl;


        


  
    }

    nodevarMap.clear();
    dd_manager->OKFDD_Quit();

    delete dd_manager;



 

    return 0;
}

/*Recurrsion Funtion*/

utnode* polyFromQtoF2(dd_man* dd_manager,polynomial_t poly,int list_counter,std::map<tuple<string,int>,utnode*> nodevarMap)
{
    int var_index1;
/*
    Send out g and p to obtain ~g and ~p
    ~f = ((~p^~g)xi)^~g
*/


   if (isConstant(poly))
   {
    
    return getConstantAsFDD(dd_manager,poly); 
    
   }


   else if(isTerm(poly))
   {
    
    return getTermAsFDD(dd_manager,poly,nodevarMap); 
    
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
    utnode* g_tilda = polyFromQtoF2(dd_manager,g_poly, list_counter,nodevarMap);
    //cout<<"Intermediate expression1:"<<endl;
    //Cudd_PrintMinterm(mgr.getManager(), g_tilda.getNode());

    utnode* p_tilda = polyFromQtoF2(dd_manager,p_poly, list_counter,nodevarMap);
    //cout<<"Intermediate expression2:"<<endl;
    //Cudd_PrintMinterm(mgr.getManager(), p_tilda.getNode());

    //utnode* ftilda=((p_tilda ^ g_tilda) & (uvarMap[variable]))^g_tilda;
    utnode* ftilda1=dd_manager->OKFDD_Synthesis(C_XOR,g_tilda,p_tilda);
    //dd_manager->OKFDD_Store_Root(ftilda1);
    utnode* ftilda2=dd_manager->OKFDD_Synthesis(C_AND,ftilda1,nodevarMap[variable]);
    //dd_manager->OKFDD_Store_Root(ftilda2);
    utnode* ftilda=dd_manager->OKFDD_Synthesis(C_XOR,ftilda2,g_tilda);
    //dd_manager->OKFDD_Store_Root(ftilda);
    



    
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


utnode* getConstantAsFDD(dd_man* dd_manager,polynomial_t poly)
{
    polynomial_t::iterator iter = poly.begin();
    advance(iter, 0);
    term_t term = *iter;
    utnode* cons_BDD;

    if (term.coefficient.numerator != 0)
    {
        cons_BDD=dd_manager->OKFDD_ONE;
    }
    else
    {
        cons_BDD=dd_manager->OKFDD_ZERO;
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
utnode* getTermAsFDD(dd_man* dd_manager,polynomial_t poly,std::map<tuple<string,int>,utnode*> nodevarMap)
{
    polynomial_t::iterator iter = poly.begin();
    term_t term_temp=*iter;
    //BDD tilda=mgr.bddOne();
    utnode* tilda=dd_manager->OKFDD_ONE;
    for(int i=0;i<term_temp.monomial.size();i++){
        //cout<<"monomial:"<<get<string>(term_temp.monomial[i])<<endl;
        for(int i=0;i<term_temp.monomial.size();i++){
            if(get<int>(term_temp.monomial[i])==1)
            {

                tilda =dd_manager->OKFDD_Synthesis(C_AND,tilda,nodevarMap[term_temp.monomial[i]]);
                
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



