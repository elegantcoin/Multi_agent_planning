# Multi_agent_planning
C++ Multi agent planning

<p align="center">
    <a href="https://github.com/elegantcoin/coding_demos"><img src="https://img.shields.io/badge/status-updating-brightgreen.svg"></a>
    <a href="https://github.com/topics/cplusplus"><img src="https://img.shields.io/github/languages/top/elegantcoin/coding_demos.svg"></a>
    <a href="https://github.com/elegantcoin/coding_demos"><img src="https://img.shields.io/badge/platform-Windows%7CLinux%7CmacOS-660066.svg"></a>

</p>
<br />

## :fire: 算法思路

主要采用了 `A*` 算法，相比于`Dijkstra`算法，它提供了搜索方向的启发性指引信息，在大多数情况下大大降低了`Dijkstra`算法无效的冗余的扩展搜索。利用代价总函数最小选择下一节点，`f(n) = g(n) + h(n)`。`g(n)`表示从初始结点到任意结点n的代价，`h(n)`表示从结点n到目标点的启发式评估代价。从初始点向目标点移动时，`A*`算法权衡这两者，选择`f(n)`最小的结点n行走，如此往复直到目标点。
# 数据结构

节点 `Node_Coord`,代表`grid`中节点的数据结构，包括x-y坐标，方向，成本`g(n)`，以及父节点（类似链表，没使用指针）。
```c++
Node_Coord
	x;
	y;
	degree;
	cost;
	parent_index;
```
图 `A_Graph`, A*算法的主要数据结构，包括整个`grid`的必要信息（大小，精度,`agent`的半径，坐标范围，可搜索方向（这里只考虑了4个方向，稍微扩展可以到8个方向以及任意方向），出发点和目标点。
```c++
A_Graph
	public:
		grid_size;
		agent_radius;
		min_x;
		min_y;
		rows;
		cols;
		directions;
		x_boundaries;
		y_boundaries;
		nstart;
		ndest;
		gen_boundries(int n_row, int n_col); //构造图，绘制边界，可以扩展出障碍
		get_directions();  //构造搜寻的方向，以及每个方向单位行走成本
		cal_xy_index(int pos,int min_pos); //根据网格的精度，计算坐标
		gen_unique_key(Node_Coord node);  //使用map,生成key
		calc_weight_distance(Node_Coord n1,Node_Coord n2);  //计算h(n)
		is_legal_node(Node_Coord node);  //判断是否运动到grid外面，有障碍物可以判断能否通过障碍物
		gen_final_path(Node_Coord ndest, map<int,Node_Coord> closedset,vector<int> *res_x,vector<int> *res_y); //产生最终结果，使用vector存储路径坐标
		agent_planing(int (*start)[3],int (*des)[3], vector<int> *res_x,vector<int> *res_y); //主要算法函数
```
# 算法主流程：
- 生成边界，明确定义了网格的大小范围，指定网格的精度。
- 生成搜索方向：以向量形式指定`agent`可以运动的方向，包含沿该方向上行走的成本`cost`。
- 指定起始点、终止点，采用多维数组保存每个`agent`的信息。
- 用`map`构造`open_set`、`close_set`，其中的`key`通过专门函数生成，借用`hash`思路。
- 1.进入寻路主循环，把`open_set`初始化为起始节点，其父节点标记为`-1`。如果`open_set`为空就退出、否则遍历` open_set` 计算到目标点和出发点总成本最小的点(由于假定`agent`只能四个方向移动，使用了加权`曼哈顿距离`)，标记点，然后通过` value` 值找到` key`，也就找到搜索下一步要访问的节点。
- 2.把原节点放入`close_set`，代表节点已经被访问，不需要再次搜索，同时把原节点从`open_set`中删除。
- 3.该节点作为新的节点，根据搜寻方向函数继续向各个方向搜索，运用函数计算点是否可行（到边界外或者有障碍物,考虑` agent` 的大小和网格精度的关系）把可行的节点最小的一个加入`open_set`。
- 循环步骤` 1-3`，如果节点访问到了目标节点，退出循环。
- 其后，根据目标节点的` parent_index` 遍历，直到遇到标记` -1` 的起始点，得到完整的路径。
- 最后，将路径通过`vector`迭代器从后往前遍历，输出结果路径。


## :fire: 编译

```linux
mkdir include lib bin
```

*公用库，头文件放到` include` 、静态库放到` lib`，动态库放到` bin`（Linux）或` bin/Debug` （Windows）目录下.*

**Windows**

(以使用Visual Studio 2010为例，前提要安装Cmake,并将其路径添加到path系统环境变量)
```
cd bin
cmake .. -G "Visual Studio 10 Win64"
```

**Linux**
(建议更新到最新，至少保证Cmake在v2.8以上)
```Linux
cd bin
cmake ..
make
```

## :fire: 运行

**Windows**

(用VS打开`Multi_agent_planning\bin` 目录下的  `Multi_agent_planning.sln`)

**Linux**

```Linux
cd bin
./MultiAgentPlanning
```



