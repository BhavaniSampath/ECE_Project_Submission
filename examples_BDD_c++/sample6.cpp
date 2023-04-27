#include "cuddObj.hh"
#include "cudd.h"


int main() {
    // Create a new CUDD manager object
    Cudd mgr;

    // Create some BDD nodes
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD bdd = x & y;

    // Create a vector to hold the BDD nodes
    std::vector<BDD> nodes;
    //nodes.push_back(x);
    //nodes.push_back(y);
    nodes.push_back(bdd);
    FILE *fp = fopen("bdd.dot", "w");

    // Call the DumpDot function to output the BDDs to a file
    mgr.DumpDot(nodes, nullptr, nullptr, fp);

    return 0;
}