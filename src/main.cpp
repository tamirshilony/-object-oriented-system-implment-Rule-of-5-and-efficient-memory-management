#include <iostream>
#include <fstream>
#include "../include/json.hpp"
#include "../include/Session.h"


using namespace std;
using json = nlohmann::json ;


int main(int argc, char** argv){
//    if(argc != 2){
//        cout << "usage cTrace <config_path>" << endl;
//        return 0;
//    }
//    Session sess(argv[1]);
    Session sess("/home/spl211/stud/SPL/Ass1/config3.json");
    sess.simulate();
    return 0;
}
