#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
using namespace doctest;

const int MIN_TESTS = 20;


struct ReporterGrader: public ConsoleReporter {
    ReporterGrader(const ContextOptions& input_options)
            : ConsoleReporter(input_options) {}

    void test_run_end(const TestRunStats& run_stats) override {
        ConsoleReporter::test_run_end(run_stats);
        int numAsserts = run_stats.numAsserts >=  MIN_TESTS? run_stats.numAsserts:  MIN_TESTS;
        float grade = (run_stats.numAsserts - run_stats.numAssertsFailed) * 100 / numAsserts;
        // std::cout << "Grade: " << grade << std::endl;
    }
};

REGISTER_REPORTER("grader", /*priority=*/1, ReporterGrader);

#include "NumberWithUnits.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

int main(int argc, char** argv) {
    Context context;
    context.addFilter("reporters", "grader");
    return context.run();

//    std::ifstream units_file{"C:\\Users\\nir son\\CLionProjects\\cpp_task_3\\units.txt"};
//
//    if(!units_file){std::cout << "ddd";}
//
//    double temp1 = 0;
//    char a = '%';
//    //ifs >> temp1;
//    units_file >> a;
//
//    std::cout << a;
//
//    std::ifstream units_file{"C:\\Users\\nir son\\CLionProjects\\cpp_task_3\\units.txt"};
//    ariel::NumberWithUnits::read_units(units_file);
//    ariel::NumberWithUnits n1{1,"km"};
//    ariel::NumberWithUnits n2{100, "m"};
//    std::cout << std::boolalpha;
//
//    std::cout << n1.convert_unit("m");
//
//
//    //std::cout << (n1==n2);
//
//
//
//    //ariel::NumberWithUnits::read_units(ifs);


}
