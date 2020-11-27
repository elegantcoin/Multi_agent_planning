#include <stdio.h>
#include "multi_agent_planning.h"
#include "multi_agent_planning_ut.h"

CPPUNIT_TEST_SUITE_REGISTRATION(UTA_Graph);


//prepare data
//Node static_node;
//static_node = {1,1};
//static_node = {2,4};
//static_node = {6,8};


void UTA_Graph::test_()
{
	A_Graph static_graph;
	static_graph.grid_size = 5;
	int ret = static_graph.cal_xy_index(10,0);
	CPPUNIT_ASSERT_EQUAL(21, ret);
	printf("\n test_func begins ...\n");
}

