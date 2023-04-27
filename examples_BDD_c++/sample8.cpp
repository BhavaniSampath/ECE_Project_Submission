#include "cuddObj.hh"
#include "cudd.h"
#include <string>
#include<iostream>
#include <map>


int main() {
    // Create a new CUDD manager object
    Cudd mgr;

    std::map<std::string, int> varMap;

    // Define an array of variable names
    std::string varNames[3] = {"x", "y", "z"};
    BDD tmp;
    BDD expr=mgr.bddOne();

    // // Create some BDD nodes
    // BDD x = mgr.bddVar();
    // BDD y = mgr.bddVar();
    // BDD bdd = x & y;

    // Create BDD variables and associate names with them
    for (int i = 0; i < 3; i++) {
        BDD var = mgr.bddVar();
        varMap[varNames[i]] = var.NodeReadIndex();
        tmp=mgr.bddVar(varMap[varNames[i]]);
        expr=tmp * expr;
        
    }
    

    //BDD expr = mgr.bddVar(varMap[varNames[0]])| mgr.bddVar(varMap[varNames[1]]) * mgr.bddVar(varMap[varNames[2]]);
    //BDD expr = mgr.bddVar(varMap[varNames[0]]) *(~ mgr.bddVar(varMap[varNames[1]]))|mgr.bddVar(varMap[varNames[2]]);
    //BDD expr = mgr.bddVar(varMap["x"]) & mgr.bddVar(varMap["y"]) | mgr.bddVar(varMap["z"]);
    // Create a vector to hold the BDD nodes
    std::vector<BDD> nodes;
    //nodes.push_back(x);
    //nodes.push_back(y);
    nodes.push_back(expr);
    //nodes.push_back(tmp);
    FILE *fp = fopen("expr2.dot", "w");

    // Call the DumpDot function to output the BDDs to a file
    mgr.DumpDot(nodes, nullptr, nullptr, fp);

    return 0;
}