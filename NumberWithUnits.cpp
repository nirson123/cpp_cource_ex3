//
// Created by nir son on 18/04/2021.
//

#include "NumberWithUnits.hpp"
#include <string>
#include<iostream>
#include <fstream>

using namespace std;

ariel::NumberWithUnits::NumberWithUnits(double number, string unit) {

}

ariel::NumberWithUnits::NumberWithUnits(const ariel::NumberWithUnits &other) {

}

ariel::NumberWithUnits::~NumberWithUnits() {

}

void ariel::NumberWithUnits::read_units(ifstream& ifs) {

    string unit, dest_unit;
    double conversion_rate;
    string junk1;
    double junk2;

    while(ifs){
        ifs >> junk2 >> unit >> junk1 >> conversion_rate >> dest_unit;
        add_unit(unit, dest_unit, conversion_rate);
    }
}

void ariel::NumberWithUnits::add_unit(string unit, string dest_unit, double conversion_rate){

    units_map[unit][dest_unit] = conversion_rate;
    units_map[dest_unit][unit] = 1.0 / conversion_rate;

    for (const auto& [key, value] : units_map[dest_unit]){
        add_unit(unit, key, conversion_rate*value);
    }
}



ariel::NumberWithUnits ariel::NumberWithUnits::operator+(const ariel::NumberWithUnits &other) const {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &other) {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator+() const {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &other) const {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &other) {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator-() const {
    return ariel::NumberWithUnits(0, "");
}



bool ariel::NumberWithUnits::operator>(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator>=(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator<(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator<=(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator==(const ariel::NumberWithUnits &other) const {
    return false;
}

bool ariel::NumberWithUnits::operator!=(const ariel::NumberWithUnits &other) const {
    return false;
}



ariel::NumberWithUnits& ariel::NumberWithUnits::operator++() {
    return *this;
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator--() {
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator++(int dummy) {
    return ariel::NumberWithUnits(0, "");
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator--(int dummy) {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator*(double num) const {
    return ariel::NumberWithUnits(0, "");
}

ariel::NumberWithUnits ariel::operator*(double num, const ariel::NumberWithUnits &n_w_u) {
    return ariel::NumberWithUnits(0, "");
}

std::istream& ariel::operator>>(std::istream &is, ariel::NumberWithUnits &n_w_u) {
    return is;
}

std::ostream& ariel::operator<<(std::ostream &os, const ariel::NumberWithUnits &n_w_u) {
    return os;
}
