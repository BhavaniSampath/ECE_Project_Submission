/*
How to compile
**************

gcc -I /home/bhavani/My_Workspace/tools/cudd-3.0.0 -I /home/bhavani/My_Workspace/tools/cudd-3.0.0/cudd 
-I /home/bhavani/My_Workspace/tools/cudd-3.0.0/util -o sample sample.c -L /home/bhavani/My_Workspace/tools/cudd-3.0.0/cudd/.libs/ 
-lcudd -lutil -lm

*/
#include <stdio.h>
#include "cudd.h"
#include "util.h"

int main(int argc,char *argv[]){
    DdManager *gbm;
    char filename[30];
    gbm=Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
    DdNode *bdd=Cudd_bddNewVar(gbm);
    Cudd_Ref(bdd);
    printf("Nodes : %ld \n",Cudd_ReadNodeCount(gbm));
    Cudd_PrintDebug(gbm,bdd,2,4);
    Cudd_Quit(gbm);
    return 0;
}