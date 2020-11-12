#include <iostream>
#include <fstream>
#include "json.hpp"
#include "Session.h"

using json = nlohmann::json;
using namespace std;

int main(int argc, char **argv) {

// REAL MAIN

    if (argc != 2) {
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }

    cout << "guysa"<< endl;

    Session sess(argv[1]);
    sess.simulate();
//    Graph &g1=sess.getGraph();
//    g1.print();
    return 0;
}
