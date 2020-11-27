#include <iostream>
#include <utility>
#include <array>
#include <map>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <limits.h>
#include <stdio.h>
#include "multi_agent_planning.h"

//---------------------------------------func---------------------------------------

void A_Graph::gen_boundries(int n_row, int n_col)
{

	for(int i=0;i<n_row;i++)
	{
		x_boundaries.push_back(i);
		y_boundaries.push_back(0);
	}
	for(int i=0;i<=n_col;i++)
	{
		x_boundaries.push_back(10);
		y_boundaries.push_back(i);
	}
	for(int i=0;i<n_row;i++)
	{
		x_boundaries.push_back(i);
		y_boundaries.push_back(10);
	}
	for(int i=0;i<n_col;i++)
	{
		x_boundaries.push_back(0);
		y_boundaries.push_back(i);
	}
}

void A_Graph::get_directions()
{
/*	directions.push_back(vector<int>());*/
	//4 directions: dx,dy,cost=10
	vector<int> temp;
	temp.push_back(1);
	temp.push_back(0);
	temp.push_back(10);
	directions.push_back(temp);
	temp.clear();

	temp.push_back(0);
	temp.push_back(1);
	temp.push_back(10);
	directions.push_back(temp);
	temp.clear();

	temp.push_back(-1);
	temp.push_back(0);
	temp.push_back(10);
	directions.push_back(temp);
	temp.clear();

	temp.push_back(0);
	temp.push_back(-1);
	temp.push_back(10);
	directions.push_back(temp);
	temp.clear();
}

int A_Graph::cal_xy_index(int pos,int min_pos)
{
	// ceil
	return (pos-min_pos)/grid_size;
}

int A_Graph::gen_unique_key(Node_Coord node)
{
	return (node.y - min_y)*rows + node.x - min_x;
}


int A_Graph::calc_weight_distance(Node_Coord n1,Node_Coord n2)
{
	//weighted Manhattan Distance is used
	int weight =10;
	// weight * sqrt(pow((n1.x-ndest.x),2) +pow((n1.y-ndest.y),2)); //<cmath> Euclidean distance
	int d = weight * (abs(n1.x-n2.x) +abs(n1.y-n2.y));
	return d;
}


bool A_Graph::is_legal_node(Node_Coord node)
{
	if (node.x <min_x || node.y< min_y || node.x>(min_x+rows) || node.y>(min_y+cols) )
	{
		return false;
	}
	else 
	{
		return true;
	}
}

void A_Graph::gen_final_path(Node_Coord ndest, map<int,Node_Coord> closedset,vector<int> *res_x,vector<int> *res_y)
{
	//
	res_x->push_back(ndest.x);
	res_y->push_back(ndest.y);
	int p_index = ndest.parent_index; 
	while (p_index !=-1)
	{
		Node_Coord node_n;
		node_n = closedset[p_index];
		res_x->push_back(node_n.x);
		res_y->push_back(node_n.y);
		p_index = node_n.parent_index;
	}
}

void A_Graph::agent_planing(int (*start)[3],int (*des)[3], vector<int> *res_x,vector<int> *res_y)
{	
	nstart.x = cal_xy_index(*start[0],min_x);
	nstart.y = cal_xy_index(*(start[0]+1),min_y);
	nstart.cost = 0;
	nstart.parent_index = -1;

	ndest.x = cal_xy_index(*des[0],min_x);
	ndest.y = cal_xy_index(*(des[0]+1),min_y);
	ndest.cost = 0;
	ndest.parent_index = -1;

	map<int,Node_Coord> open_set;
	map<int,Node_Coord> close_set;
	int key = gen_unique_key(nstart);
	open_set[key] = nstart;

	while (true)
	{
		if (open_set.size() == 0)
		{
			printf("the open set is empty! ");
			break;
		}
		//TODO
		
		int min_cost = INT_MAX;
		int min_node = INT_MAX;
		map<int,Node_Coord>::iterator it= open_set.begin();
		for (;it!=open_set.end();)
		{
			int temp_cost = calc_weight_distance((*it).second,ndest) + (*it).second.cost;
			if (temp_cost < min_cost)
			{
				min_cost = temp_cost;
				min_node = (*it).second.cost;
			}
			else
			{
				it++;
			}
		}
		
		auto iter = find_if(open_set.begin(),open_set.end(),
			[min_node](const map<int,Node_Coord>::value_type item)
		{
			return item.second.cost == min_node;
		});
		int uniq_id = iter->first;

		Node_Coord current;
		current = open_set[uniq_id];

		if (current.x == ndest.x && current.y == ndest.y)
		{
			printf("Dest is reached! ");
			ndest.parent_index = current.parent_index;
			ndest.cost = current.cost;
			break;
		}

		//delete
		open_set.erase(uniq_id);

		close_set[uniq_id] = current;

		for(int i=0;i<directions.size();i++)
		{
			Node_Coord node;
			node.x = current.x + directions[i][0];
			node.y = current.y + directions[i][1];
			node.cost = current.cost + directions[i][2];
			node.parent_index = uniq_id;
			
			//produce new uniq_id
			int node_id = gen_unique_key(node);

			if (!(is_legal_node(node)))
			{
				continue;
			}
			if (close_set.find(node_id) != close_set.end())
			{
				continue;
			}
			if (open_set.find(node_id) == open_set.end())
			{
				open_set[node_id] = node;
			}
			else
			{
				if(open_set[node_id].cost > node.cost)
				{
					open_set[node_id] = node;
				}
			}
		}
	}


	gen_final_path(ndest, close_set, res_x,res_y);
}


void coding_demo()
{
	A_Graph a_star_plan;
	a_star_plan.grid_size = 1;  // grid resolution, unit: m
	a_star_plan.agent_radius = 0.45; //agent radius

	a_star_plan.min_x = 0;
	a_star_plan.min_y = 0;
	a_star_plan.rows = 10;
	a_star_plan.cols= 10;
	//4 connected grid
	a_star_plan.gen_boundries(a_star_plan.rows, a_star_plan.cols);
	a_star_plan.get_directions();

	int agets[2][3] = {2,0,0,0,3,0};
	int dests[2][3] = {2,5,0,6,3,0};


	for (int i =0;i<2;i++)
	{
		vector<int> result_x;
		vector<int> result_y;
		a_star_plan.agent_planing(&(agets[i]),&(dests[i]),&result_x,&result_y);

		//print the result
		auto iterx = result_x.crbegin();
		auto itery = result_y.crbegin();
		for ( ;iterx != result_x.crend(); ++iterx)
		{
			cout<<"("<< (*iterx) <<","<<(*itery)<<") -> ";
			++itery;
		}
		cout<<endl;
	}
	
	getchar();
}