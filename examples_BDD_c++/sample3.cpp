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
    BDD new_var,tmp;
    BDD tilde=mgr.bddOne();
    //BDD x = mgr.bddVar();
    //BDD y = mgr.bddVar();
    BDD z= mgr.bddVar();
    for (int i = 2; i >= 0; i--) {
    new_var = mgr.bddVar(i); /*Create a new BDD variable*/
    tmp = tilde * new_var; /*Perform AND Boolean operation*/
    tilde = tmp;
    }
    BDD g=mgr.bddOne();
    BDD f = ((tilde ^ g) * z) ^ g;
    Cudd_PrintDebug(mgr.getManager(),f.getNode(),2,4);

}