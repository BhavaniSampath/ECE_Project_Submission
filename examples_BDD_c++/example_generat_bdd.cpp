#include "cuddObj.hh"
#include "cudd.h"
#include <string>
#include<iostream>
#include <map>


int main() {
    // Create a new CUDD manager object
    Cudd mgr;

    //std::map<std::string, int> varMap;

    // Define an array of variable names


    // // Create some BDD nodes
    // BDD x = mgr.bddVar();
    // BDD y = mgr.bddVar();
    // BDD bdd = x & y;

    // Create BDD variables and associate names with them
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    BDD z= mgr.bddVar();
    BDD u= mgr.bddVar();
    

    //BDD expr = mgr.bddVar(varMap[varNames[0]])| mgr.bddVar(varMap[varNames[1]]) * mgr.bddVar(varMap[varNames[2]]);
    //BDD expr = mgr.bddVar(x) *(~ mgr.bddVar(y))|mgr.bddVar(varMap[varNames[2]]);
    BDD expr = ~(x)*y*z|x*(~y)*z*u|x*y*z;
    //BDD expr = mgr.bddVar(varMap["x"]) & mgr.bddVar(varMap["y"]) | mgr.bddVar(varMap["z"]);
    // Create a vector to hold the BDD nodes
    std::vector<BDD> nodes;
    // nodes.push_back(x);
    // nodes.push_back(y);
    // nodes.push_back(z);
    // nodes.push_back(u);
    nodes.push_back(expr);
    //nodes.push_back(tmp);
    FILE *fp = fopen("print_bdd_node.dot", "w");

    // Call the DumpDot function to output the BDDs to a file
    mgr.DumpDot(nodes, nullptr, nullptr, fp);

    return 0;
}