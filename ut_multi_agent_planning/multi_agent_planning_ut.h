#pragma once
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

using namespace std;


class UTA_Graph: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UTA_Graph);
	//CPPUNIT_TEST(test_generate_upper_bound_path);
	//CPPUNIT_TEST(test_generate_lower_bound_path);
	//CPPUNIT_TEST(test_delay_to_avoid_another_path);
	//CPPUNIT_TEST(test_print_path_points_to_json_string);
	CPPUNIT_TEST_SUITE_END();
public:
	void test_();
};