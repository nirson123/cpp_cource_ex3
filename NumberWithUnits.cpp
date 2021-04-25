//
// Created by nir son on 18/04/2021.
//

#include "NumberWithUnits.hpp"
#include <string>
#include<iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <set>

using namespace std;

std::map<std::string, std::map<std::string, double>> ariel::NumberWithUnits::units_map;

ariel::NumberWithUnits::NumberWithUnits(double number, const string& unit) {

    if (units_map.count(unit) == 0){
        throw invalid_argument{"unit doesn't exist"};
    }
        this->unit = unit;
        this->number = number;
}

ariel::NumberWithUnits::NumberWithUnits(const ariel::NumberWithUnits &other) {
    this->number = other.number;
    this->unit = other.unit;
}

ariel::NumberWithUnits::~NumberWithUnits() = default;


ariel::NumberWithUnits ariel::NumberWithUnits::convert_unit(const string& convert_to) const{

    if(this->unit == convert_to){
        return ariel::NumberWithUnits{this->number, this->unit};
    }
    if(units_map[this->unit].count(convert_to) != 0){
        return ariel::NumberWithUnits{this->number * units_map[this->unit][convert_to] ,convert_to};
    }

    throw invalid_argument{"can't convert between " + this->unit + " and " +convert_to};
}

void ariel::NumberWithUnits::read_units(ifstream& ifs) {

    string unit, dest_unit, junk1;
    double conversion_rate = 0 , junk2 = 0;

    set<string> visited;

    while(ifs >> junk2 >> unit >> junk1 >> conversion_rate >> dest_unit){
        visited.clear();
        add_unit(unit, dest_unit, conversion_rate, visited);
    }

}

void ariel::NumberWithUnits::add_unit(const string& unit, const string& dest_unit, double conversion_rate, set<string>& visited){

    units_map[unit][dest_unit] = conversion_rate;
    units_map[dest_unit][unit] = 1.0 / conversion_rate;

    visited.insert(dest_unit);
    visited.insert(unit);

    for (auto [key, value] : units_map[dest_unit]){
        if(visited.find(key) == visited.end()) {
            add_unit(unit, key, conversion_rate * value, visited);
        }
    }

    for (auto [key, value] : units_map[unit]){
        if(visited.find(key) == visited.end()) {
            add_unit(dest_unit, key, (1.0 / conversion_rate) * value, visited);
        }
    }
}



ariel::NumberWithUnits ariel::NumberWithUnits::operator+(const ariel::NumberWithUnits &other) const {

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return ariel::NumberWithUnits{this->number + other_converted.number, this->unit};
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &other) {

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    this->number += other_converted.number;

    return *this;
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator+() const {
    return ariel::NumberWithUnits{this->number, this->unit};
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &other) const {

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return ariel::NumberWithUnits{this->number - other_converted.number, this->unit};
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &other) {

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    this->number -= other_converted.number;

    return *this;
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator-() const {
    return ariel::NumberWithUnits{-this->number, this->unit};
}



bool ariel::NumberWithUnits::operator>(const ariel::NumberWithUnits &other) const {

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return this->number > other_converted.number;
}

bool ariel::NumberWithUnits::operator>=(const ariel::NumberWithUnits &other) const {

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return (this->number > other_converted.number) || (this->number == other_converted.number);
}

bool ariel::NumberWithUnits::operator<(const ariel::NumberWithUnits &other) const {

    return !(*this >= other);

}

bool ariel::NumberWithUnits::operator<=(const ariel::NumberWithUnits &other) const {
    return !(*this > other);
}

bool ariel::NumberWithUnits::operator==(const ariel::NumberWithUnits &other) const {

    static const double EPS = 0.000001;

    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return abs(this->number - other_converted.number) < EPS;
}

bool ariel::NumberWithUnits::operator!=(const ariel::NumberWithUnits &other) const {
    return !(*this == other);
}



ariel::NumberWithUnits& ariel::NumberWithUnits::operator++() {
    this->number ++;
    return *this;
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator--() {
    this->number --;
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator++(int dummy) {
    ariel::NumberWithUnits copy{*this};
    this->number ++;
    return copy;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator--(int dummy) {
    ariel::NumberWithUnits copy{*this};
    this->number --;
    return copy;
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator*(double num) const {
    return ariel::NumberWithUnits{this->number * num , this->unit};
}

ariel::NumberWithUnits ariel::operator*(double num, const ariel::NumberWithUnits &n_w_u) {
    return ariel::NumberWithUnits{n_w_u.number * num , n_w_u.unit};
}

std::istream& ariel::operator>>(istream &is, ariel::NumberWithUnits &n_w_u) {

    double num{0};
    string unit;
    char temp{' '};

    auto start_position = is.tellg();

    if(!(is >> num) ||
    !(is >> temp) || temp != '['){
        is.clear();
        is.seekg(start_position);
        throw runtime_error{"wrong input format"};
    }

    while(temp != ']'){
        if(!(is >> temp)){
            is.clear();
            is.seekg(start_position);
            throw runtime_error{"wrong input format"};
        }
        if(temp != ' ' && temp != ']'){unit += temp;}
    }

    if(NumberWithUnits::units_map.count(unit) == 0){
        is.clear();
        is.seekg(start_position);
        throw runtime_error{"wrong input format"};
    }

        n_w_u.number = num;
        n_w_u.unit = unit;
        return is;
}



std::ostream& ariel::operator<<(ostream &os, const ariel::NumberWithUnits &n_w_u) {
    os << n_w_u.number << "[" << n_w_u.unit << "]";
    return os;
}
