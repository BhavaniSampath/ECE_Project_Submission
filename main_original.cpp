// HEADER Files
// ------------
#include<iostream>
#include "tc_time.h"
#include "puma.h"
using namespace std;
#include <string.h>

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

	//char 	                benchname[25] 	= "./Benchmark/C7552.blif";
	char 	                benchname[25] 	= "simpleAND.blif";
	//char 	                benchname[25] 	= "mult2.blif";
	char* DUMPFILENAME ="out.txt";
	//char* DUMPFILENAME ="mult2_outm1.txt";
	//char* DUMPFILENAME ="mult2_outm3.txt";
   

	// ---------------
	// Init DD-Manager
	// ---------------
    dd_man* dd_manager = OKFDD_Init( ut_hashsize ,
                                         ct_hashsize ,
                                         rc_cachesize,
                                         ct_searchlen,
                                         var_lim    );


    
    dd_manager->OKFDD_Read_BLIF( benchname,
                                     NULL      ,
                                     NULL,
                                     NULL      ,
                                     NULL
									  ); 


	

	// utnode* root = new utnode;
	// root->label_i = 0;
	// root->lo_p = dd_manager->OKFDD_ZERO;
	// root->hi_p = dd_manager->OKFDD_ONE;

	// utnode* G = new utnode;
	// G->label_i = 1;
	// G->lo_p = dd_manager->OKFDD_ZERO;
	// G->hi_p = dd_manager->OKFDD_ONE;

	// names x(0, 0);
    // x.label_i = 0;
    // strcpy(x.name,"x");

    // names y(0, 1);
    // y.label_i = 1;
    // strcpy(y.name, "y");

    // names z(1, 0);
    // z.label_i = 2;
    // //strcpy(z.name, "z");

	// // Link the nodes to the variables
    // x.root = root;
    // y.root = root;
    // z.root = dd_manager->OKFDD_ZERO;
    
    // z.root = dd_manager->OKFDD_Synthesis(C_AND,x.root,y.root);
	// //dd_manager->OKFDD_PO_Root_Table(z.root->label_i);
	// int var=dd_manager->OKFDD_utnode_ptr(z.root);
	// cout<<"root not exist"<<var<<endl;

	//utnode* result = dd_manager->OKFDD_Forall(F,0);
    // --------------------------
	// Show some OKFDD statistics
	// --------------------------
	cout << "All:  ";   dd_manager->OKFDD_Profile_all(TRUE);

	cout << "Vars: " << dd_manager->OKFDD_P_I 	 << "\n";
	cout << "Outs: " << dd_manager->OKFDD_P_O        << "\n";
	cout << "Size: " << dd_manager->OKFDD_Size_all() << "\n";
	cout<<"root node:"<<dd_manager->OKFDD_PO_Root_Table (3)<<"\n";
	
	utnode* F=dd_manager->OKFDD_PO_Root_Table (3);
	cout<<"F root node:"<<F->label_i<<"\t"<<"left child"<<F->lo_p<<"\t"<<"right child"<<F->hi_p<<endl;
	//dd_manager->OKFDD_Store_Root ( F);




	cout<<"PO node:"<<dd_manager->OKFDD_PO_Table (0)<<"\n";
	cout<<"PI node:"<<dd_manager->OKFDD_PI_Table (0)<<"\n";
	dd_manager-> OKFDD_1_PC(F,DUMPFILENAME);
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
