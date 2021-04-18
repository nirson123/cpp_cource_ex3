//
// Created by nir son on 18/04/2021.
//

#include <string>
#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <fstream>
#include <sstream>

using namespace ariel;

TEST_CASE("read units"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // valid units
    CHECK_NOTHROW(NumberWithUnits(5, "cm"));
    CHECK_NOTHROW(NumberWithUnits(5, "m"));
    CHECK_NOTHROW(NumberWithUnits(5, "km"));
    CHECK_NOTHROW(NumberWithUnits(5, "g"));
    CHECK_NOTHROW(NumberWithUnits(5, "kg"));
    CHECK_NOTHROW(NumberWithUnits(5, "ton"));
    CHECK_NOTHROW(NumberWithUnits(5, "hour"));
    CHECK_NOTHROW(NumberWithUnits(5, "sec"));
    CHECK_NOTHROW(NumberWithUnits(5, "USD"));
    CHECK_NOTHROW(NumberWithUnits(5, "ILS"));

    // not valid units
    CHECK_THROWS(NumberWithUnits(5, "dollar"));
    CHECK_THROWS(NumberWithUnits(5, "ils"));
    CHECK_THROWS(NumberWithUnits(5, ""));
    CHECK_THROWS(NumberWithUnits(5, "CM"));

    // over ride units file
    std::ifstream units_file_2{"units_2.txt"};
    CHECK_NOTHROW(NumberWithUnits::read_units(units_file_2));

    CHECK_NOTHROW(NumberWithUnits(5, "b"));
    CHECK_NOTHROW(NumberWithUnits(5, "km"));

    CHECK_THROWS(NumberWithUnits(5, "USD"));
}

TEST_CASE("addition"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // same type
    NumberWithUnits two_sec{2, "sec"};
    NumberWithUnits seven_sec{7, "sec"};
    CHECK(two_sec + seven_sec == NumberWithUnits(9, "sec"));

    // same dim
    NumberWithUnits four_kg{4, "kg"};
    NumberWithUnits grams{1000, "g"};
    CHECK(four_kg + grams == NumberWithUnits(5, "km"));
    CHECK(grams + four_kg == NumberWithUnits(5000, "g"));

    // different dim
    NumberWithUnits one_dollar{1, "USD"};
    NumberWithUnits fourty_min{40, "min"};
    CHECK_THROWS(one_dollar + fourty_min);
}

TEST_CASE("add_equal"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // same type
    NumberWithUnits two_sec{2, "sec"};
    NumberWithUnits seven_sec{7, "sec"};
    two_sec += seven_sec;
    CHECK(two_sec == NumberWithUnits(9, "sec"));

    // same dim
    NumberWithUnits four_kg{4, "kg"};
    NumberWithUnits grams{1000, "g"};
    four_kg += grams;
    CHECK(four_kg == NumberWithUnits(5, "km"));
    grams += four_kg;
    CHECK(grams == NumberWithUnits(6000, "g"));

    // different dim
    NumberWithUnits one_dollar{1, "USD"};
    NumberWithUnits fourty_min{40, "min"};
    CHECK_THROWS(one_dollar += fourty_min);
}

TEST_CASE("Unary plus"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits five_shekels{5, "ILS"};
    NumberWithUnits plus_five_shekels = +five_shekels;
    CHECK(five_shekels == plus_five_shekels);
    CHECK(&five_shekels != &plus_five_shekels); //check not some object

    NumberWithUnits minus_eight_cm{-8, "cm"};
    NumberWithUnits plus_minus_eight_cm = +minus_eight_cm;
    CHECK(minus_eight_cm == plus_minus_eight_cm);
    CHECK(&minus_eight_cm != &plus_minus_eight_cm); //check not some object
}

TEST_CASE("minus"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // same type
    NumberWithUnits two_sec{2, "sec"};
    NumberWithUnits seven_sec{7, "sec"};
    CHECK(two_sec - seven_sec == NumberWithUnits(-5, "sec"));

    // same dim
    NumberWithUnits four_kg{4, "kg"};
    NumberWithUnits grams{1000, "g"};
    CHECK(four_kg - grams == NumberWithUnits(3, "km"));
    CHECK(grams - four_kg == NumberWithUnits(-3000, "g"));

    // different dim
    NumberWithUnits one_dollar{1, "USD"};
    NumberWithUnits fourty_min{40, "min"};
    CHECK_THROWS(one_dollar - fourty_min);
}

TEST_CASE("sub_equal"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // same type
    NumberWithUnits two_sec{2, "sec"};
    NumberWithUnits seven_sec{7, "sec"};
    two_sec -= seven_sec;
    CHECK(two_sec == NumberWithUnits(-5, "sec"));

    // same dim
    NumberWithUnits four_kg{4, "kg"};
    NumberWithUnits grams{1000, "g"};
    four_kg -= grams;
    CHECK(four_kg == NumberWithUnits(3, "km"));
    grams -= four_kg;
    CHECK(grams == NumberWithUnits(-2000, "g"));

    // different dim
    NumberWithUnits one_dollar{1, "USD"};
    NumberWithUnits fourty_min{40, "min"};
    CHECK_THROWS(one_dollar -= fourty_min);
}

TEST_CASE("Unary plus"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits five_shekels{5, "ILS"};
    NumberWithUnits minus_five_shekels = -five_shekels;
    CHECK(minus_five_shekels == NumberWithUnits(-5,"ILS"));
    CHECK(&five_shekels != &minus_five_shekels); //check not some object

    NumberWithUnits minus_eight_cm{-8, "cm"};
    NumberWithUnits minus_minus_eight_cm = -minus_eight_cm;
    CHECK(minus_minus_eight_cm == NumberWithUnits(8, "cm"));
    CHECK(&minus_eight_cm != &minus_minus_eight_cm);    //check not some object
}

TEST_CASE("bigger then"){
    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // some type
    NumberWithUnits eleven_meters{11, "m"};
    NumberWithUnits ten_meters{10, "m"};
    CHECK(eleven_meters > ten_meters);
    CHECK(!(ten_meters > eleven_meters));

    // some dim
    NumberWithUnits half_ton{0.5, "ton"};
    NumberWithUnits grams{500001, "g"};
    CHECK(grams > half_ton);
    CHECK(!(half_ton > grams));

    // different dim
    NumberWithUnits one_shekel{1, "ILS"};
    NumberWithUnits six_sec{6, "sec"};
    CHECK_THROWS(bool b= (six_sec > one_shekel));
    CHECK_THROWS(bool b = (one_shekel > six_sec));
}

TEST_CASE("bigger or equals"){
    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    /* not equal*/

    // some type
    NumberWithUnits eleven_meters{11, "m"};
    NumberWithUnits ten_meters{10, "m"};
    CHECK(eleven_meters >= ten_meters);
    CHECK(!(ten_meters >= eleven_meters));

    // some dim
    NumberWithUnits half_ton{0.5, "ton"};
    NumberWithUnits grams{500001, "g"};
    CHECK(grams >= half_ton);
    CHECK(!(half_ton >= grams));

    // different dim
    NumberWithUnits one_shekel{1, "ILS"};
    NumberWithUnits six_sec{6, "sec"};
    CHECK_THROWS(bool b = (six_sec >= one_shekel));
    CHECK_THROWS(bool b = (one_shekel >= six_sec));

    /* equals */

    // some type
    NumberWithUnits eleven_meters_1{11, "m"};
    NumberWithUnits eleven_meters_2{11, "m"};
    CHECK(eleven_meters_1 >= eleven_meters_2);
    CHECK(eleven_meters_2 >= eleven_meters_1);

    // some dim
    NumberWithUnits half_ton_1{0.5, "ton"};
    NumberWithUnits half_ton_in_grams{50000, "g"};
    CHECK(half_ton_in_grams >= half_ton_1);
    CHECK(half_ton_1 >= half_ton_in_grams);

    // different dim, some number
    NumberWithUnits six_shekel_1{6, "ILS"};
    NumberWithUnits six_sec_1{6, "sec"};
    CHECK_THROWS(bool b = (six_sec >= one_shekel));
    CHECK_THROWS(bool b = (one_shekel >= six_sec));
}

TEST_CASE("less then"){
    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // some type
    NumberWithUnits eleven_meters{11, "m"};
    NumberWithUnits ten_meters{10, "m"};
    CHECK(!(eleven_meters < ten_meters));
    CHECK(ten_meters < eleven_meters);

    // some dim
    NumberWithUnits half_ton{0.5, "ton"};
    NumberWithUnits grams{500001, "g"};
    CHECK(!(grams < half_ton));
    CHECK(half_ton < grams);

    // different dim
    NumberWithUnits one_shekel{1, "ILS"};
    NumberWithUnits six_sec{6, "sec"};
    CHECK_THROWS(bool b = (six_sec < one_shekel));
    CHECK_THROWS(bool b = (one_shekel < six_sec));
}

TEST_CASE("less or equals"){
    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    /* not equal*/

    // some type
    NumberWithUnits eleven_meters{11, "m"};
    NumberWithUnits ten_meters{10, "m"};
    CHECK(!(eleven_meters <= ten_meters));
    CHECK(ten_meters <= eleven_meters);

    // some dim
    NumberWithUnits half_ton{0.5, "ton"};
    NumberWithUnits grams{500001, "g"};
    CHECK(!(grams <= half_ton));
    CHECK(half_ton <= grams);

    // different dim
    NumberWithUnits one_shekel{1, "ILS"};
    NumberWithUnits six_sec{6, "sec"};
    CHECK_THROWS(bool b = (six_sec <= one_shekel));
    CHECK_THROWS(bool b = (one_shekel <= six_sec));

    /* equals */

    // some type
    NumberWithUnits eleven_meters_1{11, "m"};
    NumberWithUnits eleven_meters_2{11, "m"};
    CHECK(eleven_meters_1 <= eleven_meters_2);
    CHECK(eleven_meters_2 <= eleven_meters_1);

    // some dim
    NumberWithUnits half_ton_1{0.5, "ton"};
    NumberWithUnits half_ton_in_grams{50000, "g"};
    CHECK(half_ton_in_grams <= half_ton_1);
    CHECK(half_ton_1 <= half_ton_in_grams);

    // different dim, some number
    NumberWithUnits six_shekel_1{6, "ILS"};
    NumberWithUnits six_sec_1{6, "sec"};
    CHECK_THROWS(bool b = (six_sec <= one_shekel));
    CHECK_THROWS(bool b = (one_shekel <= six_sec));
}

TEST_CASE("equal equal"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // same object
    NumberWithUnits sevn_min{7,"min"};
    CHECK(sevn_min == sevn_min);

    NumberWithUnits two_hours{2,"hour"};
    NumberWithUnits min_120{120, "min"};
    NumberWithUnits sec_7200{7200, "sec"};
    // direct conversion
    CHECK(two_hours == min_120);
    CHECK(min_120 == two_hours);
    CHECK(min_120 == sec_7200);
    CHECK(sec_7200 == min_120);
    // un-direct conversion
    CHECK(two_hours == sec_7200);
    CHECK(sec_7200 == two_hours);

    // different dims
    NumberWithUnits one_ton{1,"ton"};
    CHECK_THROWS(bool b = (one_ton == sec_7200));
    CHECK_THROWS(bool b = (sec_7200 == one_ton));
}

TEST_CASE("not equal"){

    // check "real" comparison, not address
    NumberWithUnits one_meter_1{1,"meter"};
    NumberWithUnits one_meter_2{1,"meter"};
    CHECK_FALSE(one_meter_1 != one_meter_2);

    // some dim
    NumberWithUnits four_ton{4,"ton"};
    NumberWithUnits kg_4000{4000,"kg"};
    NumberWithUnits g_4000000{4000,"g"};
    // direct
    CHECK_FALSE(four_ton != kg_4000);
    CHECK_FALSE(kg_4000 != g_4000000);
    // un-direct
    CHECK_FALSE(four_ton != g_4000000);

    // minor different
    NumberWithUnits g_4000001{4000001,"g"};
    CHECK(g_4000001 != four_ton);
    CHECK(four_ton != g_4000001);
}

TEST_CASE("prefix plus plus"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits cm_50{50,"cm"};
    CHECK(++cm_50 == NumberWithUnits{51,"cm"});
    CHECK(cm_50 == NumberWithUnits{51,"cm"});

    NumberWithUnits two_and_half_meter{2.5,"m"};
    CHECK(++(two_and_half_meter + cm_50) == NumberWithUnits{4,"m"});
    CHECK(++(cm_50 + two_and_half_meter) == NumberWithUnits{3.01,"m"});
}

TEST_CASE("postfix plus plus"){
    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits cm_50{50,"cm"};
    CHECK(cm_50++ == NumberWithUnits{50,"cm"});
    CHECK(cm_50 == NumberWithUnits{51,"cm"});

    NumberWithUnits two_and_half_meter{2.5,"m"};
    NumberWithUnits m_3 = two_and_half_meter + cm_50;
    CHECK(m_3++ == NumberWithUnits{3,"m"});
    CHECK(m_3 == NumberWithUnits{4,"m"});
    NumberWithUnits m_3_2 = cm_50 + two_and_half_meter;
    CHECK(m_3_2++ == NumberWithUnits{3,"m"});
    CHECK(m_3_2 == NumberWithUnits{3.01,"m"});
}

TEST_CASE("prefix minus minus"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits cm_50{50,"cm"};
    CHECK(--cm_50 == NumberWithUnits{49,"cm"});
    CHECK(cm_50 == NumberWithUnits{49,"cm"});

    NumberWithUnits two_and_half_meter{2.5,"m"};
    CHECK(--(two_and_half_meter + cm_50) == NumberWithUnits{2,"m"});
    CHECK(--(cm_50 + two_and_half_meter) == NumberWithUnits{2.99,"m"});
}

TEST_CASE("postfix minus minus"){
    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits cm_50{50,"cm"};
    CHECK(cm_50-- == NumberWithUnits{50,"cm"});
    CHECK(cm_50 == NumberWithUnits{49,"cm"});

    NumberWithUnits two_and_half_meter{2.5,"m"};
    NumberWithUnits m_3 = two_and_half_meter + cm_50;
    CHECK(m_3-- == NumberWithUnits{3,"m"});
    CHECK(m_3 == NumberWithUnits{2,"m"});
    NumberWithUnits m_3_2 = cm_50 + two_and_half_meter;
    CHECK(m_3_2-- == NumberWithUnits{3,"m"});
    CHECK(m_3_2 == NumberWithUnits{2.99,"m"});
}

TEST_CASE("multiplication"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits nine_dollar{9,"USD"};

    CHECK(nine_dollar*3 == NumberWithUnits{27,"USD"});
    CHECK(5*nine_dollar == NumberWithUnits{45,"USD"});

    CHECK(0*nine_dollar == NumberWithUnits{0,"USD"});
    CHECK(nine_dollar*0 == NumberWithUnits{0,"USD"});

    CHECK(-1*nine_dollar == -nine_dollar);
    CHECK(nine_dollar*-1 == -nine_dollar);
}

TEST_CASE("input"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // valid input
    NumberWithUnits num{0,"g"};
    std::stringstream sis{"200[km]"};
    sis >> num;
    CHECK(num == NumberWithUnits{200,"km"});

    // not-valid input
    std::stringstream sis_2{"a12[g]"};
    CHECK_THROWS(sis_2 >> num);
    CHECK(num == NumberWithUnits{200,"km"});

    // empty input
    std::stringstream sis_3{""};
    CHECK_THROWS(sis_3 >> num);
    CHECK(num == NumberWithUnits{200,"km"});

    // with spaces
    std::stringstream sis_4{"13 [ILS]"};
    sis_4 >> num;
    CHECK(num == NumberWithUnits{13, "ILS"});
}

TEST_CASE("output"){

    std::ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    NumberWithUnits min_27{27,"min"};
    std::stringstream sos;
    sos << min_27;
    CHECK(sos.str() == std::string("27[min]"));
    sos.clear();

    NumberWithUnits minus_one_ton{-1,"ton"};
    sos << minus_one_ton;
    CHECK(sos.str() == std::string("-1[ton]"));
    sos.clear();

    NumberWithUnits two_min{2,"min"};
    NumberWithUnits sec_30{30, "sec"};

    sos << (two_min - sec_30);
    CHECK(sos.str() == std::string("1.5[min]"));
    sos.clear();

    sos << (sec_30 - two_min);
    CHECK(sos.str() == std::string("-90[sec]"));
}
