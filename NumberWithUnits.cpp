//
// Created by nir son on 18/04/2021.
//

#include "NumberWithUnits.hpp"
#include <string>
#include<iostream>

using namespace std;

ariel::NumberWithUnits::NumberWithUnits(double number, string unit) {

}

ariel::NumberWithUnits::NumberWithUnits(const ariel::NumberWithUnits &other) {

}

ariel::NumberWithUnits::~NumberWithUnits() {

}

void ariel::NumberWithUnits::read_units(ifstream& ifs) {

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
