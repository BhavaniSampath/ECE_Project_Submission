#include <stdio.h>
#include <stdlib.h>
#include <cudd.h>

int main() {
    DdManager *mgr;
    DdNode *bdd;

    // Initialize the CUDD manager
    mgr = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);

    // Create some BDD variables
    DdNode *var0 = Cudd_bddNewVar(mgr);
    DdNode *var1 = Cudd_bddNewVar(mgr);

    // Create a BDD expression
    DdNode *expr = Cudd_bddAnd(mgr, var0, Cudd_Not(var1));

    // Dump the DOT representation of the BDD to a file
    FILE *outfile = fopen("bdd.dot", "w");
    Cudd_DumpDot(mgr, 1, &expr, NULL, NULL, outfile);
    fclose(outfile);

    // Clean up the manager
    Cudd_Quit(mgr);

    return 0;
}