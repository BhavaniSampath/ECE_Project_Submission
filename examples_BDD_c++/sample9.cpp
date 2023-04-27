#include <iostream>
#include "cuddObj.hh"

using namespace std;

int main() {
    // Create a BDD manager
    Cudd mgr;

    // Define two Boolean variables
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD u =mgr.bddVar();

    // Define a BDD expression (x AND y)
    BDD z = ((x ^ y)*u)^y;
   


    // Dump the BDD to the console
    cout << "BDD expression:" << endl;
    Cudd_PrintMinterm(mgr.getManager(), z.getNode());

    return 0;
}

