// HEADER Files
// ------------
#include<iostream>
#include "tc_time.h"
#include "puma.h"
using namespace std;
#include <string.h>
#include <fstream>



/* ========================================================= */
// Main-routine
/* ========================================================= */
int main(int argc, char *argv[])
{
	unsigned char		ut_hashsize	= 4;
	unsigned long		ct_hashsize	= 5003;
	unsigned long int	rc_cachesize	= 1000;
	unsigned char		ct_searchlen	= 3;
	unsigned short int	var_lim		= 20000;


	//char 	                benchname[25] 	= "simple_input.blif";
	//char 	                benchname[25] 	= "simpleAND.blif";


	char* DUMPFILENAME ="out_AND.txt";
	char variable_name1[] = "a0";
	char variable_name2[] = "b0";
	char variable_name3[] = "m0";
   

	// ---------------
	// Init DD-Manager
	// ---------------
    dd_man* dd_manager = OKFDD_Init( ut_hashsize ,
                                         ct_hashsize ,
                                         rc_cachesize,
                                         ct_searchlen,
                                         var_lim    );


    
    // dd_manager->OKFDD_Read_BLIF( benchname,
    //                                  NULL      ,
    //                                  NULL,
    //                                  NULL      ,
    //                                  NULL
	// 								  ); 



	utnode* variable_node1 =dd_manager->OKFDD_Get_Variable(variable_name1,POSITIVE);
	utnode* variable_node2 =dd_manager->OKFDD_Get_Variable(variable_name2,POSITIVE);
	//utnode* F=dd_manager->OKFDD_Get_outVariable(variable_name3);
	utnode* F=dd_manager->OKFDD_Synthesis(C_XOR,variable_node1,variable_node2);
	dd_manager->OKFDD_Store_Root(F);
	cout<<"variable_info:"<<"\t"<<dd_manager->toprime[dd_manager->OKFDD_PI_Table(0)]->root<<"\t"
	<<dd_manager->toprime[dd_manager->OKFDD_PI_Table(1)]->root<<endl;
	cout<<"complete_variable_info:"<<"\t"<<dd_manager->toprime[dd_manager->OKFDD_PI_Table(0)]->name<<"\t"
	<<dd_manager->toprime[dd_manager->OKFDD_PI_Table(1)]->name
	<<endl;

	cout<<"m0_root:"<<dd_manager->OKFDD_Get_Root (dd_manager->toprime[dd_manager->OKFDD_PO_Table(0)]->name)<<endl;


    
    dd_manager->toprime[dd_manager->OKFDD_PO_Table(0)]->root =F;
	//F=dd_manager->OKFDD_Get_Root (dd_manager->toprime[dd_manager->OKFDD_PO_Table(0)]->name);
	
	cout<<"out_variable:"<<dd_manager->toprime[dd_manager->OKFDD_PO_Table(0)]->name<<endl;
	// //dd_manager->OKFDD_PO_Root_Table(z.root->label_i);
	// int var=dd_manager->OKFDD_utnode_ptr(z.root);
	// cout<<"root not exist"<<var<<endl;

	//utnode* result = dd_manager->OKFDD_Forall(F,0);
    // --------------------------
	// Show some OKFDD statistics
	// --------------------------
	//cout << "All:  ";   dd_manager->OKFDD_Profile_all(TRUE);

	cout << "Vars: " << dd_manager->OKFDD_P_I 	 << "\n";
	cout << "Outs: " << dd_manager->OKFDD_P_O        << "\n";
	cout << "Size: " << dd_manager->OKFDD_Size_all() << "\n";
	cout<<"root node:"<<dd_manager->OKFDD_PO_Root_Table (3)<<"\n";
	
	//cout<<"PI1:"<<variable_node<<endl;
	cout<<"F root node:"<<F->label_i<<"\t"<<"left child"<<F->lo_p<<"\t"<<"right child"<<F->hi_p<<endl;
	//dd_manager->OKFDD_Store_Root ( F);




	cout<<"PO node:"<<dd_manager->OKFDD_PO_Table (0)<<"\n";
	cout<<"PI node:"<<dd_manager->OKFDD_PI_Table (0)<<"\n";
	dd_manager-> OKFDD_1_PC_noblif(F,DUMPFILENAME);
	
	
	
	//dd_manager->Trav_Show(F);
	// dd_manager->Trav_Show(variable_node1);
	// dd_manager->Trav_Show(variable_node2);
	//cout<<"profile:"<<dd_manager->OKFDD_Profile_all(TRUE);
	//cout<<"root node:"<<dd_manager->OKFDD_Get_Root ('0')<<"\n";
	//cout<<"Details:" <<dd_manager->OKFDD_Result[2] <<"\n";
	



	

                    
	//dd_manager->OKFDD_Shell();
                  
	// ----------------------------- 
	// Free Decision Diagram Manager
	// ----------------------------- 
	dd_manager->OKFDD_Quit();

        delete dd_manager;
};
/* ========================================================= */
