//
// Created by nir son on 18/04/2021.
//

#include "NumberWithUnits.hpp"
#include <string>
#include<iostream>
#include <fstream>
#include <exception>
#include <set>

using namespace std;

// initiate the map
std::map<std::string, std::map<std::string, double>> ariel::NumberWithUnits::units_map;

// constructor
ariel::NumberWithUnits::NumberWithUnits(double number, const string& unit) {

    if (units_map.count(unit) == 0){    // check valid unit
        throw invalid_argument{"unit doesn't exist"};
    }

        this->unit = unit;
        this->number = number;
}

// copy constructor
ariel::NumberWithUnits::NumberWithUnits(const ariel::NumberWithUnits &other) {
    this->number = other.number;
    this->unit = other.unit;
}

// destructor
ariel::NumberWithUnits::~NumberWithUnits() = default;


/**
 * return a new number with units that equal to this, but in the given unit
 * @param convert_to
 * @return
 */
ariel::NumberWithUnits ariel::NumberWithUnits::convert_unit(const string& convert_to) const{

    if(this->unit == convert_to){   // if same unit - copy
        return ariel::NumberWithUnits{*this};
    }
    if(units_map[this->unit].count(convert_to) != 0){   // if not same unit but can be converted - convert
        return ariel::NumberWithUnits{this->number * units_map[this->unit][convert_to] ,convert_to};
    }

    // if can't be converted, throw exception
    throw invalid_argument{"can't convert between " + this->unit + " and " +convert_to};
}

/**
 * set the units map
 * @param ifs
 */
void ariel::NumberWithUnits::read_units(ifstream& ifs) {

    string unit, dest_unit, junk1;
    double conversion_rate = 0 , junk2 = 0;

    set<string> visited;

    // read each line and add to the map
    while(ifs >> junk2 >> unit >> junk1 >> conversion_rate >> dest_unit){
        visited.clear();
        add_unit(unit, dest_unit, conversion_rate, visited);
    }

}

/**
 * add a new unit / conversion to the map
 * @param unit
 * @param dest_unit
 * @param conversion_rate
 * @param visited
 */
void ariel::NumberWithUnits::add_unit(const string& unit, const string& dest_unit, double conversion_rate, set<string>& visited){

    // add conversion
    units_map[unit][dest_unit] = conversion_rate;
    units_map[dest_unit][unit] = 1.0 / conversion_rate;

    visited.insert(dest_unit);
    visited.insert(unit);

    // recursively add the unit to all the "connected" units
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

    // convert
    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return ariel::NumberWithUnits{this->number + other_converted.number, this->unit};
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator+=(const ariel::NumberWithUnits &other) {

    // convert
    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    this->number += other_converted.number; // increment

    return *this;
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator+() const {
    return ariel::NumberWithUnits{*this};   // unary plus does nothing - just copy
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator-(const ariel::NumberWithUnits &other) const {

    // convert
    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return ariel::NumberWithUnits{this->number - other_converted.number, this->unit};
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator-=(const ariel::NumberWithUnits &other) {

    // convert
    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    this->number -= other_converted.number; // decrement

    return *this;
}

ariel::NumberWithUnits ariel::NumberWithUnits::operator-() const {
    return ariel::NumberWithUnits{-this->number, this->unit};
}

bool ariel::NumberWithUnits::operator>(const ariel::NumberWithUnits &other) const {

    // convert
    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return this->number > other_converted.number; // check if bigger
}

bool ariel::NumberWithUnits::operator>=(const ariel::NumberWithUnits &other) const {
    return (*this > other) || (*this == other);
}

bool ariel::NumberWithUnits::operator<(const ariel::NumberWithUnits &other) const {
    return !(*this >= other);
}

bool ariel::NumberWithUnits::operator<=(const ariel::NumberWithUnits &other) const {
    return !(*this > other);
}

bool ariel::NumberWithUnits::operator==(const ariel::NumberWithUnits &other) const {

    static const double EPS = 0.000001; // "tolerance" for different

    // convert
    ariel::NumberWithUnits other_converted = other.convert_unit(this->unit);

    return abs(this->number - other_converted.number) < EPS;    // check if close enough
}

bool ariel::NumberWithUnits::operator!=(const ariel::NumberWithUnits &other) const {
    return !(*this == other);
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator++() {
    this->number ++;    // increment
    return *this;
}

ariel::NumberWithUnits& ariel::NumberWithUnits::operator--() {
    this->number --;  // decrement
    return *this;
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator++(int dummy) {
    ariel::NumberWithUnits copy{*this}; // save a copy
    this->number ++;    // increment
    return copy;    // return the copy (before increment)
}

const ariel::NumberWithUnits ariel::NumberWithUnits::operator--(int dummy) {
    ariel::NumberWithUnits copy{*this}; // save a copy
    this->number --;    // decrement
    return copy;    // return the copy (before decrement)
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

    // read number and '['
    if(!(is >> num) ||
    !(is >> temp) || temp != '['){
        // if wrong format or problem with stream, clear input and throw exception
        is.clear();
        is.seekg(start_position);
        throw runtime_error{"wrong input format"};
    }

    // read the unit and ']'
    while(temp != ']'){
        if(!(is >> temp)){
            // if wrong format or problem with stream, clear input and throw exception
            is.clear();
            is.seekg(start_position);
            throw runtime_error{"wrong input format"};
        }
        if(temp != ' ' && temp != ']'){unit += temp;}
    }

    // if the unit is not valid, clear input and throw exception
    if(NumberWithUnits::units_map.count(unit) == 0){
        is.clear();
        is.seekg(start_position);
        throw runtime_error{"wrong input format"};
    }

    // set the input values
    n_w_u.number = num;
    n_w_u.unit = unit;
    return is;
}



std::ostream& ariel::operator<<(ostream &os, const ariel::NumberWithUnits &n_w_u) {
    os << n_w_u.number << "[" << n_w_u.unit << "]"; // print in format
    return os;
}
