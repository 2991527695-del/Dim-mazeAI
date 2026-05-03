#include "Maze_ai_lx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <algorithm>  // shuffle
#include <random>
#include <functional>
#include <unordered_map>
#include <chrono>

Maze_AI::Maze_AI(){
Xmax = 10;
Ymax = 10;
Load_algorithm_library();//加载算法库
Startrunning_Time_Timer();//时间初始化
}

Maze_AI::~Maze_AI(){
    /*如果需要清理资源，在这里写*/
}
void Maze_AI::Load_algorithm_library(){//初始化算法库

Algorithm_Library_Create.push_back({"DFS_1","Blind Digging Maze_DFS(V1.1)",std::bind(&Maze_AI::Maze_Factory, this)});
Algorithm_Library_Search.push_back({"DFS1","Flood Fill_DFS(1.1)",std::bind(&Maze_AI::Maze_pathfinding, this)});
Algorithm_Library_Search.push_back({"DFS2","Bigger Flood Fill_DFS2(V1.2)",std::bind(&Maze_AI::Maze_Path_2BFS, this)});
Algorithm_Library_Search.push_back({"Algorithm_A","A* Algorithm(V1.3)",std::bind(&Maze_AI::Search_Algorithm_Algorithm_A, this)});
}

void Maze_AI::Startrunning_Time_Timer(){

auto Start_Time_void = std::chrono::duration_cast<std::chrono::seconds>(
std::chrono::system_clock::now().time_since_epoch()
);
Start_Time = Start_Time_void.count();

}

void Maze_AI::maae_data_initialization(){
    int XnewValue=0,YnewValue=0,Pathfinding=0,Generation=0;
    std::cout << "[Dim|C++]Maze_Simulation_v2.4" << std::endl;
    
    for(int i = 0 ;i<Algorithm_Library_Create.size();i++){
        std::cout <<Algorithm_Library_Create[i].Name << "[" << i << "]" << std::endl;
        std::cout << "\033[2m"<<Algorithm_Library_Create[i].Introduction << "\033[0m" << std::endl;
    }    
    std::cout << "- - - - - - - - - -"<< std::endl;

    for(int i = 0 ;i<Algorithm_Library_Search.size();i++){
        std::cout <<Algorithm_Library_Search[i].Name << "[" << i << "]" << std::endl;
        std::cout << "\033[2m"<<Algorithm_Library_Search[i].Introduction << "\033[0m" << std::endl;
    }
    std::cout << ">_[mapX]_[mapY]_[Generation_Pathfinding]"<<std::endl;
    std::cout << "Please_enter.-->";
    std::cin >> XnewValue >> YnewValue >> Generation >> Pathfinding;
    if(XnewValue>0&&YnewValue>0){
        Xmax=XnewValue;Ymax=YnewValue;
    }else{
        exits("Exceeded the limit or input is incorrect(X|Y)");
        }
   maze_map.assign(Ymax, std::vector<int>(Xmax,Maze_walls_Enum));  //初始值0
   Algorithm_selection(Generation,Pathfinding);
}

void Maze_AI::Display_Destination_Starting_point(){
int YStarting_point = Starting_point/Xmax;//加载起点(Y)
int YDestination = Destination/Xmax;//加载终点(Y)
maze_map[YStarting_point][Starting_point-(YStarting_point*Xmax)]=Maze_Starting_point;
maze_map[YDestination][Destination-(YDestination*Xmax)]=Maze_Destination;
}

void Maze_AI::Map_loading(std::string mapdata){//迷宫渲染

auto Start_Time_Current = std::chrono::duration_cast<std::chrono::seconds>(
std::chrono::system_clock::now().time_since_epoch());
int Time_Current = Start_Time_Current.count();
int Time_Duration = Time_Current - Start_Time;

std::cout << "\033[?25l";
std::cout << "\033[" << Ymax << "A";
for(int i = 0;i<Ymax;i++){
    std::cout << std::flush;
    for(int j = 0;j<Xmax;j++){
        Render_cout(i,j);
        }std::cout << std::endl;
    }
    std::cout<< "\33[2K\r" << "Current.\033[4m"<< mapdata << "\033[0m\033[2m[" <<Time_Duration<<"/S]"<<"\033[0m\033[1A\r";
}



void Maze_AI::Render_cout(int y,int x){
switch(maze_map[y][x]){
    case Maze_empty_Enum:
    std::cout << ".";break;
    case Maze_walls_Enum:
    std::cout << "#";break;
    case Maze_Destination:
    std::cout << "E";break;
    case Maze_Starting_point:
    std::cout << "S";break;
    case Maze_aipath_Enum:
    std::cout << "~";break;
    case Maze_Shortest_route:
    std::cout << "\033[32m\033[1m=\033[0m";break;
    case Maze_Searching_Traces1:
    std::cout << "+";break;
    case Maze_Searching_Traces2:
    std::cout << "-";break;
    }
std::cout << " ";//间隔    
}

void Maze_AI::Parameter_Start_data(int Parameter,char* mapdata[]){//启动模式选择(数据初始化)
if(Parameter==5){

int 
mapx = std::stoi(mapdata[1]),
mapy = std::stoi(mapdata[2]);
if(mapx<0 || mapy<0){exits("Parameter_error! [Name_-x_-y]");}//退出
Xmax = mapx,Ymax =mapy;

int 
sea = std::stoi(mapdata[3]),
cre = std::stoi(mapdata[4]);

maze_map.assign(Ymax, std::vector<int>(Xmax,Maze_walls_Enum));
Algorithm_selection(sea,cre);
}else if(Parameter>=2){
exits("Parameter_error! [Name_-x_-y] or [Name_-sea_-cre]");//退出
}else{
maae_data_initialization();//正常模式启动  
    }
}

void Maze_AI::Algorithm_selection(int Create,int Search){
if(Create<Algorithm_Library_Create.size() && Create>=0){
    Algorithm_Library_Create[Create].Run();
}else{exits("Cannot find the create algorithm library");}

if(Search<Algorithm_Library_Search.size() && Search>=0){
    Algorithm_Library_Search[Search].Run();
}else{exits("Cannot find search algorithm library");}

map_Render_Display();//最后一次刷新地图
}


void Maze_AI::map_Render_Display(){
Display_Destination_Starting_point();//刷新起/终点
Map_loading("Completed!");//最后刷新
}

void Maze_AI::exits(std::string Error_message){
//std::cout << "[!]Program exited with an error. \n";
std::cout << "[i]Error message.-->"<< Error_message;
exit(0);//程序退出
}