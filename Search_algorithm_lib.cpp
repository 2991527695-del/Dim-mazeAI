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
#include <sstream>
#include <cstdlib>


void Maze_AI::Maze_pathfinding(){//寻找路线(BFS(洪水))
std::queue<int> Pathfinding_data;
int//初始化偏移量(上下左右) 
X_Offset[4]={-1,0,0,+1},
Y_Offset[4]={0,-1,+1,0},
Find_route = 0,History_records_vect,
History_records_child[Ymax][Xmax]={Empty_data_Enum};
Pathfinding_data.push(Starting_point);//导入起点
while(!Pathfinding_data.empty()){
int cut = Pathfinding_data.front();
int seaY = cut/Xmax;
int seaX = cut-seaY*Xmax;
int XA_off,YA_off;
Pathfinding_data.pop();
    for(int i = 0;i<4;i++){
        if(Find_route){break;}
        XA_off=seaX+X_Offset[i],YA_off=seaY+Y_Offset[i];
        if(XA_off<Xmax && XA_off>=0 && YA_off<Ymax && YA_off>=0 && (maze_map[YA_off][XA_off]==1 || maze_map[YA_off][XA_off]<0)){
            History_records_child[YA_off][XA_off]=(YA_off+(-Y_Offset[i]))*Xmax+(XA_off+(-X_Offset[i]));//记录路径回溯信息
            if(maze_map[YA_off][XA_off]==Maze_Destination){Find_route=1;break;}//如果找到了             
            maze_map[YA_off][XA_off]=Maze_aipath_Enum; 
            Pathfinding_data.push(YA_off*Xmax+XA_off);
            std::stringstream Current_content;
            Current_content << "Search the maze-->[" << XA_off << "," << YA_off << "," << Pathfinding_data.size() <<"]";
            Map_loading(Current_content.str());
        }
    }
    }
History_records_vect=Destination;
while(1){
int seay = History_records_vect/Xmax;
int seax = History_records_vect-seay*Xmax;
if(Starting_point==seay*Xmax+seax){break;}
maze_map[seay][seax]=Maze_Shortest_route;
std::stringstream Current_content_1;
Current_content_1 << "Shortest path...[" << seax << "," << seay << "]";
Map_loading(Current_content_1.str());
if(History_records_child[seay][seax]==Empty_data_Enum && Destination!=seay*Xmax+seax && Starting_point!=seay*Xmax+seax)
{exits("Maze_data_not_found");}    
History_records_vect=History_records_child[seay][seax];
    }
}

void Maze_AI::Maze_Path_2BFS(){//Bidirectional BFS
std::queue<int> Two_way_DBSdata1;//起点数据
std::queue<int> Two_way_DBSdata2;//终点数据
int X_Offset[4]={-1,0,0,+1};//X偏移量
int Y_Offset[4]={0,-1,+1,0};//Y偏移量
int History_records_child_A[Ymax][Xmax];//历史数据点
int History_records_child_B[Ymax][Xmax];//历史数据点
for(int i=0;i<Ymax;i++){
    for(int j=0;j<Xmax;j++){
        History_records_child_A[i][j]=Empty_data_Enum;
        History_records_child_B[i][j]=Empty_data_Enum;
    }
}
int Find_route1=0;
int XA_of_a,YA_of_a,XA_of_b,YA_of_b;
int seayx_a,seayx_b;
Two_way_DBSdata1.push(Starting_point);
Two_way_DBSdata2.push(Destination);//导入终点
while(!(Two_way_DBSdata1.empty()&&Two_way_DBSdata2.empty())){

    
    if(!Two_way_DBSdata1.empty()){
    int seaY1 = Two_way_DBSdata1.front()/Xmax;
    int seaX1 = Two_way_DBSdata1.front()-seaY1*Xmax;
    Two_way_DBSdata1.pop();
    for(int i = 0;i<4;i++){
        XA_of_a = seaX1 + X_Offset[i],YA_of_a = seaY1 + Y_Offset[i];
        if(XA_of_a<Xmax && XA_of_a>=0 && YA_of_a<Ymax && YA_of_a>=0 && maze_map[YA_of_a][XA_of_a]==Maze_Searching_Traces2)
        {
            Find_route1=1;
            seayx_b = YA_of_a*Xmax+XA_of_a;
            seayx_a = (YA_of_a-Y_Offset[i])*Xmax+(XA_of_a-X_Offset[i]);
            break;
        }
        if(XA_of_a<Xmax && XA_of_a>=0 && YA_of_a<Ymax && YA_of_a>=0 && (maze_map[YA_of_a][XA_of_a]==1 || maze_map[YA_of_a][XA_of_a]<0)){
            History_records_child_A[YA_of_a][XA_of_a]=(YA_of_a+(-Y_Offset[i]))*Xmax+(XA_of_a+(-X_Offset[i]));//记录历史记录
            maze_map[YA_of_a][XA_of_a]=Maze_Searching_Traces1;
            Two_way_DBSdata1.push(YA_of_a*Xmax+XA_of_a);
            //std::stringstream Current_content1;
            //Current_content1 << "Searching(A)...[" << XA_of_a << "," << YA_of_a << "," << Two_way_DBSdata1.size() << "]";
            //Map_loading(Current_content1.str());
            }
        }}if(Find_route1){break;}
    if(!Two_way_DBSdata2.empty()){
    int seaY2 = Two_way_DBSdata2.front()/Xmax;
    int seaX2 = Two_way_DBSdata2.front()-seaY2*Xmax;
    Two_way_DBSdata2.pop();
    for(int i = 0;i<4;i++){
        XA_of_b = seaX2 + X_Offset[i],YA_of_b = seaY2 + Y_Offset[i];
        if(XA_of_b<Xmax && XA_of_b>=0 && YA_of_b<Ymax && YA_of_b>=0 && maze_map[YA_of_b][XA_of_b]==Maze_Searching_Traces1)
        {
            Find_route1=1;
            seayx_a = YA_of_b*Xmax+XA_of_b;
            seayx_b = (YA_of_b-Y_Offset[i])*Xmax+(XA_of_b-X_Offset[i]);
            break;
        }
        if(XA_of_b<Xmax && XA_of_b>=0 && YA_of_b<Ymax && YA_of_b>=0 && (maze_map[YA_of_b][XA_of_b]==1 || maze_map[YA_of_b][XA_of_b]<0)){
            History_records_child_B[YA_of_b][XA_of_b]=(YA_of_b-Y_Offset[i])*Xmax+(XA_of_b-X_Offset[i]);//记录历史记录
            maze_map[YA_of_b][XA_of_b]=Maze_Searching_Traces2;
            Two_way_DBSdata2.push(YA_of_b*Xmax+XA_of_b);
            //std::stringstream Current_content2;
            //Current_content2 << "Searching(B)...[" << XA_of_b << "," << YA_of_b << "," << Two_way_DBSdata2.size() << "]";
            //Map_loading(Current_content2.str());
            }
        std::stringstream Current_content;
        Current_content << "Searching[A." << XA_of_a << "," << YA_of_a << "," << Two_way_DBSdata1.size() << "]"<<"[B." << XA_of_b << "," << YA_of_b << "," << Two_way_DBSdata2.size() << "]";
        Map_loading(Current_content.str());
        }}if(Find_route1){break;}
    }


while(Starting_point!=seayx_a || Destination!=seayx_b){
int seay1=0,seax1=0,seay2=0,seax2=0;
if(Starting_point!=seayx_a){
seay1 = seayx_a/Xmax;
seax1 = seayx_a - seay1*Xmax;
maze_map[seay1][seax1]=Maze_Shortest_route;
seayx_a = History_records_child_A[seay1][seax1];
}
if(Destination!=seayx_b){
seay2 = seayx_b/Xmax;
seax2 = seayx_b - seay2*Xmax;
maze_map[seay2][seax2]=Maze_Shortest_route;
seayx_b = History_records_child_B[seay2][seax2];
}
std::stringstream Current_content_Path;
Current_content_Path << "Shortest path[" << seax1 << "," << seay1 << "][" << seax2 << "," << seay2 << "]";
Map_loading(Current_content_Path.str());
    }
}

void Maze_AI::Search_Algorithm_Algorithm_A(){
struct Recor_G{
int newH;//估测价值
int newG;//实际已走
int newF;//总价值(后期请使用Value_F+Guidewire_H获取)
int Dir_Suo_X;//X位置索引
int Dir_Suo_Y;//Y位置索引
};
struct Historystruct{
int History_Y;//历史记录Y位置
int History_X;//历史记录X位置
};
std::vector<Recor_G> Record_List;//记录价值
Historystruct History_List[Ymax][Xmax];//历史记录
int distance[Ymax][Xmax];//距离记录(离终点的距离)
for(int i = 0;i<Ymax;i++){
    for(int j = 0;j<Xmax;j++){
        distance[i][j] = 99999;
    }
}

int OffsetX[4] = {-1,0,0,1};//偏移量X
int OffsetY[4] = {0,-1,1,0};//偏移量Y

int seaY = Starting_point/Xmax;
int seaX = Starting_point-seaY*Xmax;
distance[seaY][seaX] = 0;//起点距离为0

int seaY1 = Destination/Xmax;
int seaX1 = Destination-seaY1*Xmax;

int poor_road = abs(seaX1 - seaX) + abs(seaY1 - seaY);
int Found_you = 0;

Record_List.push_back({poor_road, 0, 0, seaX, seaY});//导入起点
while(Record_List.size()){
int TemMax = Record_List[0]. newF,Tem=0;
for(int i = 0;i<Record_List.size();i++){
    if(TemMax>Record_List[i].newF){
        TemMax=Record_List[i].newF;
        Tem=i;
        }
    }
std::iter_swap(Record_List.begin() + Tem, Record_List.end() - 1);

int PositionY = Record_List[Record_List.size()-1].Dir_Suo_Y;
int PositionX = Record_List[Record_List.size()-1].Dir_Suo_X;
Record_List.pop_back();

    for(int i = 0;i<4;i++){
        int NewY = PositionY + OffsetY[i];
        int NewX = PositionX + OffsetX[i];
    if(NewX<Xmax && NewX>=0 && NewY<Ymax && NewY>=0 && distance[NewY][NewX]>distance[PositionY][PositionX]+1 && maze_map[NewY][NewX]!=Maze_walls_Enum){
        maze_map[NewY][NewX]=Maze_aipath_Enum;
        History_List[NewY][NewX]={NewY-OffsetY[i],NewX-OffsetX[i]};//记录历史记录
        if(NewY==seaY1 && NewX==seaX1){Found_you = 1; break;}//如果找到了
        distance[NewY][NewX] = distance[PositionY][PositionX]+1;//实际已走距离
        int Guidewire_H = abs(seaX1 - NewX) + abs(seaY1 - NewY);//估测距离
        Record_List.push_back({Guidewire_H, distance[NewY][NewX], Guidewire_H + distance[NewY][NewX], NewX, NewY});
        std::stringstream Current_content;
        Current_content << "Searching...[" << NewX << "," << NewY << "," << Record_List.size() << "|" << distance[NewY][NewX] <<"]";
        Map_loading(Current_content.str());
            }
        }
        if(Found_you){break;}
    }
while(Starting_point!=seaY1*Xmax+seaX1){
int History_Y = History_List[seaY1][seaX1].History_Y;
int History_X = History_List[seaY1][seaX1].History_X;
maze_map[seaY1][seaX1]=Maze_Shortest_route;
seaY1 = History_Y;
seaX1 = History_X;
std::stringstream Current_content;
Current_content << "Shortest path...[" << seaX1 << "," << seaY1 << "]";
Map_loading(Current_content.str());
}

}//[2026050315:19]A*算法实现

