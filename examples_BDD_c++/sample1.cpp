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

int main(int argc,char *argv[]){
    Cudd mgr(0,0);
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD f = y + !x;
    BDD g = x * y;
    std::cout << "f is" << (f <= g ? "" : " not")
             << " less than or equal to g\n";

    return 0;
}