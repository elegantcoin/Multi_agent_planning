# Multi_agent_planning
C++ Multi agent planning

<p align="center">
    <a href="https://github.com/elegantcoin/coding_demos"><img src="https://img.shields.io/badge/status-updating-brightgreen.svg"></a>
    <a href="https://github.com/topics/cplusplus"><img src="https://img.shields.io/github/languages/top/elegantcoin/coding_demos.svg"></a>
    <a href="https://github.com/elegantcoin/coding_demos"><img src="https://img.shields.io/badge/platform-Windows%7CLinux%7CmacOS-660066.svg"></a>

</p>
<br />

## :fire: �㷨˼·

��Ҫ������ `A*` �㷨�������`Dijkstra`�㷨�����ṩ�����������������ָ����Ϣ���ڴ��������´�󽵵���`Dijkstra`�㷨��Ч���������չ���������ô����ܺ�����Сѡ����һ�ڵ㣬`f(n) = g(n) + h(n)`��`g(n)`��ʾ�ӳ�ʼ��㵽������n�Ĵ��ۣ�`h(n)`��ʾ�ӽ��n��Ŀ��������ʽ�������ۡ��ӳ�ʼ����Ŀ����ƶ�ʱ��`A*`�㷨Ȩ�������ߣ�ѡ��`f(n)`��С�Ľ��n���ߣ��������ֱ��Ŀ��㡣
# ���ݽṹ

�ڵ� `Node_Coord`,����`grid`�нڵ�����ݽṹ������x-y���꣬���򣬳ɱ�`g(n)`���Լ����ڵ㣨��������ûʹ��ָ�룩��
```c++
Node_Coord
	x;
	y;
	degree;
	cost;
	parent_index;
```
ͼ `A_Graph`, A*�㷨����Ҫ���ݽṹ����������`grid`�ı�Ҫ��Ϣ����С������,`agent`�İ뾶�����귶Χ����������������ֻ������4��������΢��չ���Ե�8�������Լ����ⷽ�򣩣��������Ŀ��㡣
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
		gen_boundries(int n_row, int n_col); //����ͼ�����Ʊ߽磬������չ���ϰ�
		get_directions();  //������Ѱ�ķ����Լ�ÿ������λ���߳ɱ�
		cal_xy_index(int pos,int min_pos); //��������ľ��ȣ���������
		gen_unique_key(Node_Coord node);  //ʹ��map,����key
		calc_weight_distance(Node_Coord n1,Node_Coord n2);  //����h(n)
		is_legal_node(Node_Coord node);  //�ж��Ƿ��˶���grid���棬���ϰ�������ж��ܷ�ͨ���ϰ���
		gen_final_path(Node_Coord ndest, map<int,Node_Coord> closedset,vector<int> *res_x,vector<int> *res_y); //�������ս����ʹ��vector�洢·������
		agent_planing(int (*start)[3],int (*des)[3], vector<int> *res_x,vector<int> *res_y); //��Ҫ�㷨����
```
# �㷨�����̣�
- ���ɱ߽磬��ȷ����������Ĵ�С��Χ��ָ������ľ��ȡ�
- ��������������������ʽָ��`agent`�����˶��ķ��򣬰����ظ÷��������ߵĳɱ�`cost`��
- ָ����ʼ�㡢��ֹ�㣬���ö�ά���鱣��ÿ��`agent`����Ϣ��
- ��`map`����`open_set`��`close_set`�����е�`key`ͨ��ר�ź������ɣ�����`hash`˼·��
- 1.����Ѱ·��ѭ������`open_set`��ʼ��Ϊ��ʼ�ڵ㣬�丸�ڵ���Ϊ`-1`�����`open_set`Ϊ�վ��˳����������` open_set` ���㵽Ŀ���ͳ������ܳɱ���С�ĵ�(���ڼٶ�`agent`ֻ���ĸ������ƶ���ʹ���˼�Ȩ`�����پ���`)����ǵ㣬Ȼ��ͨ��` value` ֵ�ҵ�` key`��Ҳ���ҵ�������һ��Ҫ���ʵĽڵ㡣
- 2.��ԭ�ڵ����`close_set`������ڵ��Ѿ������ʣ�����Ҫ�ٴ�������ͬʱ��ԭ�ڵ��`open_set`��ɾ����
- 3.�ýڵ���Ϊ�µĽڵ㣬������Ѱ����������������������������ú���������Ƿ���У����߽���������ϰ���,����` agent` �Ĵ�С�����񾫶ȵĹ�ϵ���ѿ��еĽڵ���С��һ������`open_set`��
- ѭ������` 1-3`������ڵ���ʵ���Ŀ��ڵ㣬�˳�ѭ����
- ��󣬸���Ŀ��ڵ��` parent_index` ������ֱ���������` -1` ����ʼ�㣬�õ�������·����
- ��󣬽�·��ͨ��`vector`�������Ӻ���ǰ������������·����


## :fire: ����

```linux
mkdir include lib bin
```

*���ÿ⣬ͷ�ļ��ŵ�` include` ����̬��ŵ�` lib`����̬��ŵ�` bin`��Linux����` bin/Debug` ��Windows��Ŀ¼��.*

**Windows**

(��ʹ��Visual Studio 2010Ϊ����ǰ��Ҫ��װCmake,������·����ӵ�pathϵͳ��������)
```
cd bin
cmake .. -G "Visual Studio 10 Win64"
```

**Linux**
(������µ����£����ٱ�֤Cmake��v2.8����)
```Linux
cd bin
cmake ..
make
```

## :fire: ����

**Windows**

(��VS��`Multi_agent_planning\bin` Ŀ¼�µ�  `Multi_agent_planning.sln`)

**Linux**

```Linux
cd bin
./MultiAgentPlanning
```



