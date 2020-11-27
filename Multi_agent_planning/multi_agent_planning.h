#pragma once
#include <vector>
#include <map>

using namespace std;

struct Node_Coord
{
	int x;
	int y;
	float degree;
	int cost;
	int parent_index;
};

struct A_Graph
{
 public:
	int grid_size;  // grid resolution, unit: m
	double agent_radius; //agent radius
	int min_x;
	int min_y;
	int rows;
	int cols;

	vector<vector<int>> directions;
	vector<int> x_boundaries;
	vector<int> y_boundaries;
	Node_Coord nstart;
	Node_Coord ndest;


	void gen_boundries(int n_row, int n_col);

	// build 4 directions
	void get_directions();

	int cal_xy_index(int pos,int min_pos);

	int gen_unique_key(Node_Coord node);

	int calc_weight_distance(Node_Coord n1,Node_Coord n2);

	bool is_legal_node(Node_Coord node);

	void gen_final_path(Node_Coord ndest, map<int,Node_Coord> closedset,vector<int> *res_x,vector<int> *res_y);

	void agent_planing(int (*start)[3],int (*des)[3], vector<int> *res_x,vector<int> *res_y);

};