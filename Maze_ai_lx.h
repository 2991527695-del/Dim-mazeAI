#ifndef MYCLASS_H
#define MYCLASS_H

#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <unordered_map>

class Maze_AI
{
private://私有
int Xmax,Ymax;
int Destination,Starting_point;//地图数据
int Start_Time;
std::vector<int> Search_data;
std::vector<int> historymap_data;
std::vector<std::vector<int>> maze_map;

struct Algorithm_structure_Create{
std::string Name;//算法名称
std::string Introduction;//算法简介
std::function<void()> Run;//函数指针
};
struct Algorithm_structure_Search{
std::string Name;//算法名称
std::string Introduction;//算法简介
std::function<void()> Run;//函数指针
};

std::vector<Algorithm_structure_Create> Algorithm_Library_Create;//算法库
std::vector<Algorithm_structure_Search> Algorithm_Library_Search;//算法库



enum Mazemapdata{
BFS_Basics_Search=10001,//生成算法(Search)
DFS_Basics_Creation=11001,//寻找算法(Creation)
DFS2Basics_Creation=11002,//2寻找算法(Creation)
Maze_Destination=-1,//终点
Maze_Starting_point=-2,//起点
Empty_data_Enum=-3,
Maze_walls_Enum=0,//墙壁    
Maze_empty_Enum=1,//空
Maze_aipath_Enum=2,//寻找痕迹
Maze_Searching_Traces1=3,//寻找痕迹1
Maze_Searching_Traces2=4,//寻找痕迹2
Maze_Shortest_route=5,//最短路线标记
};
void maae_data_initialization();

void Display_Destination_Starting_point();

void Map_loading(std::string mapdata);
void Render_cout(int y,int x);

void Load_algorithm_library();

void Maze_Factory();//生成迷宫DFS
void Maze_pathfinding();//寻找路线BFS
void Maze_Path_2BFS();//寻找路线双向BFS

void Startrunning_Time_Timer();
void Search_Algorithm_Algorithm_A();

public://公共

void Parameter_Start_data(int Parameter,char* mapdata[]);//启动模式选择

void Algorithm_selection(int Generate,int Search);



void map_Render_Display();//最后一次刷新起点终点

void exits(std::string Error_message);//退出函数



    Maze_AI(/* args */);
    ~Maze_AI();
};


//Maze_AI::Maze_AI(/* args */){}
//Maze_AI::~Maze_AI(){}


#endif