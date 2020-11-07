#include <iostream>
#include "Session.h"

using namespace std;

int main(int argc, char **argv) {
    // cout << "guysa";
    std::vector<std::vector<int>> m = {{1, 2, 3}, {4, 5, 6}};

    std::vector<std::vector<int>> a= {{4, 5, 6},{1, 2, 3}};


    Graph g1(m);
    Graph g2(a);
    g1.print();
    g2.print();

//    g1=g2;
//    g1.print();

    Graph g3=g2;
   // g1(g2);
    g3.print();




//    for (int i = 0; i < a.size(); ++i) {
//        for (int j = 0; j < a[i].size(); ++j) {
//            std::cout << a[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    a[0][0]=9;
//    for (int i = 0; i < a.size(); ++i) {
//        for (int j = 0; j < a[i].size(); ++j) {
//            std::cout << a[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    for (int i = 0; i < m.size(); ++i) {
//        for (int j = 0; j < m[i].size(); ++j) {
//            std::cout << m[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    // Graph n(m);
//    Graph *g = new Graph(m);
//    (*g).print();
//    delete g;
//    cout << "guysa-main" << endl;


//    if(argc != 2){
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }
//    Session sess(argv[1]);
//    sess.simulate();
//    return 0;
}
