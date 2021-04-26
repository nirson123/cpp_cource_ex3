//
// Created by nir son on 18/04/2021.
//


#ifndef CPP_TASK_3_NUMBERWITHUNITS_HPP
#define CPP_TASK_3_NUMBERWITHUNITS_HPP

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>


namespace ariel {

    class NumberWithUnits {

    private:
        double number;
        std::string unit;

        static std::map<std::string, std::map<std::string, double>> units_map;
        static void add_unit(const std::string& unit, const std::string& dest_unit, double conversion_rate, std::set<std::string>& visited);

        NumberWithUnits convert_unit(const std::string& convert_to) const;

    public:

        NumberWithUnits(double number, const std::string& unit);
        NumberWithUnits(const NumberWithUnits& other);
        ~NumberWithUnits();

        static void read_units(std::ifstream& ifs);

        // arithmetic operators
        NumberWithUnits operator+ (const NumberWithUnits& other) const;
        NumberWithUnits& operator+= (const NumberWithUnits& other);
        NumberWithUnits operator+() const;
        NumberWithUnits operator- (const NumberWithUnits& other) const;
        NumberWithUnits& operator-= (const NumberWithUnits& other);
        NumberWithUnits operator-() const;

        // Comparison operators
        bool operator> (const NumberWithUnits& other) const;
        bool operator>= (const NumberWithUnits& other) const;
        bool operator< (const NumberWithUnits& other) const;
        bool operator<= (const NumberWithUnits& other) const;
        bool operator== (const NumberWithUnits& other) const;
        bool operator!= (const NumberWithUnits& other) const;

        // incrementation operators
        NumberWithUnits& operator++();
        const NumberWithUnits operator++(int dummy);
        NumberWithUnits& operator--();
        const NumberWithUnits operator--(int dummy);

        NumberWithUnits operator*(double num) const;
        friend NumberWithUnits operator*(double num, const NumberWithUnits& n_w_u);

        friend std::istream& operator>> (std::istream& is, NumberWithUnits& n_w_u);
        friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n_w_u);
    };
}
#endif //CPP_TASK_3_NUMBERWITHUNITS_HPP
