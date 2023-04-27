/*
How to compile
**************

g++ -I /home/bhavani/My_Workspace/tools/cudd-3.0.0 -I /home/bhavani/My_Workspace/tools/cudd-3.0.0/cplusplus 
-I /home/bhavani/My_Workspace/tools/cudd-3.0.0/cudd -I /home/bhavani/My_Workspace/tools/cudd-3.0.0/util -o sample1 sample1.cpp 
-L /home/bhavani/My_Workspace/tools/cudd-3.0.0/cplusplus/.libs -lobj -L /home/bhavani/My_Workspace/tools/cudd-3.0.0/cudd/.libs 
-lcudd -lutil -lm

*/

#include <iostream>
#include "cuddObj.hh"
#include "cudd.h"

int main(int argc,char *argv[]){
    Cudd mgr(0,0);
    char filename[30];
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD z= mgr.bddVar();

    BDD p = x * y;
    BDD g = mgr.bddOne();
    BDD f = ((p ^ g) * z) ^ g;
    Cudd_PrintDebug(mgr.getManager(),f.getNode(),2,4);
    sprintf(filename, "./bdd/graph.dot"); /*Write .dot filename to a string*/
    FILE *outfile; 
    outfile = fopen(filename,"w");
    std::vector<BDD> no;
    no.push_back(f);
    size_t n = no.size();
    DdNode **First = new DdNode *[n];
    for (size_t i = 0; i < n; i ++) {
	    First[i] = no[i].getNode();
    }
    Cudd_DumpDot(mgr.getManager(),n,First,NULL,NULL,outfile);
    return 0;
}