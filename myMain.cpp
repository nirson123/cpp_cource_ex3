//
// Created by nir son on 26/04/2021.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "NumberWithUnits.hpp"

using namespace ariel;
using namespace std;

int main(){

    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);


    NumberWithUnits n1{2,"km"};
    NumberWithUnits n2{300, "m"};

    cout << "arithmetic operations : " << endl;
    cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;
    cout << n2 << " + " << n1 << " = " << n2 + n1 << endl;
    cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;
    cout << "n1 = " << n1 << " n2 = " << n2 << endl;
    cout << n2 << " += " << n1 << " : n2 = "; n2 += n1; cout << n2 << endl;
    cout << n1 << " -= " << n2 << " : n1 = "; n1 -= n2; cout << n1 << endl;
    cout << "-n1 = " << -n1 << endl;

    n1 = NumberWithUnits{3600,"sec"};
    n2 = NumberWithUnits{1, "hour"};

    cout << endl << "Comparison operators" << endl;
    cout << boolalpha;
    cout << n1 << " == " << n2 << " ? " << (n1 == n2) << endl;
    cout << n1 << " != " << n2 << " ? " << (n1 != n2) << endl;
    n1 ++;
    cout << n1 << " > " << n2 << " ? " << (n1 > n2) << endl;
    cout << n1 << " >= " << n2 << " ? " << (n1 >= n2) << endl;
    cout << n1 << " < " << n2 << " ? " << (n1 < n2) << endl;
    cout << n1 << " <= " << n2 << " ? " << (n1 <= n2) << endl;

    n1 = NumberWithUnits{45,"USD"};
    n2 = NumberWithUnits{12, "ILS"};

    cout << endl << "incrementation  / decrementation" << endl;
    cout <<"n1 = " << n1 << endl;
    cout << "n1++ = " << n1++ << endl;
    cout << "n1 = " << n1 << endl;
    cout <<"n2 = " << n2 << endl;
    cout << "n2-- = " << n2-- << endl;
    cout << "n2 = " << n2 << endl;
    cout <<"n1 = " << n1 << endl;
    cout << "++n1 = " << ++n1 << endl;
    cout << "n1 = " << n1 << endl;
    cout <<"n2 = " << n2 << endl;
    cout << "--n2 = " << --n2 << endl;
    cout << "n2 = " << n2 << endl;

    cout << endl << "multiplication operators" << endl;
    cout << n1 << " * " << 2 << " = " << n1*2 << endl;
    cout << 2 << " * " << n2 << " = " << 2*n2 << endl;

    cout << endl << "input operator" << endl;
    istringstream iss{"143[cm]"};
    n1 = NumberWithUnits{0,"m"};
    cout << "istringstream iss{\"143[cm]\"} >> n1" << endl;
    iss >> n1;
    cout << "n1 = " << n1 << endl;


    return 0;
}

