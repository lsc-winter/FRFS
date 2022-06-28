#ifndef DIJK_H
#define DIJK_H



#pragma once
//#pragma once是一个比较常用的C/C++杂注，
//只要在头文件的最开始加入这条杂注，
//就能够保证头文件只被编译一次。

#include<iostream>
#include<string>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include<vector>
#include<sstream>
#include <ctime>
#include<iomanip>
//#include <bits/stdc++.h>
#include <map>
#include<stdlib.h>

#include<math.h>
using namespace std;

/*
本程序是使用改进的Dijkstra算法实现求解最短路径的问题
采用的邻接矩阵来存储图
*/
//定义节点结构体
struct V {
    int nodeindex;
    int portnum;
    bool WDMtype;
    int T_num;
    double w[64][64];
    double W_t[64][64];
    string T;  //支持信道，字符长度为支持信道数
    V(){
        nodeindex = 0;
        portnum =0;
        WDMtype =0;
        T_num = 2;
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                w[i][j] = 2000;
                W_t[i][j] = 2000;
            }
        }
    }
};

struct E {
    int srcn;
    int srcp;
    int dstn;
    int dstp;
    double weight;
//    string T;  //支持信道，字符长度为支持信道数
    E(){
        srcn = 0;
        srcp = 0;
        dstn = 0;
        dstp = 0;
        weight = 0;
    }
};

struct C{
    double w[64][64];
    int node1;
    int node2;
    C(){
        node1=0;
        node2=0;
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                w[i][j] = 2000;
            }
        }
    }
};

//记录起点到每个端口的最短路径的信息
struct Dist {
    string path[64];
    double value[64];
    bool visit[64];
    int bridge;
    Dist() {
//        visit = false;
//        value = 2000; //0->无穷大
        for (int j = 0; j < 64; j++) {//每个端口一个值可能会被覆盖掉，应该用个栈或向量 //相当于一次走了两步
            value[j] = 2000; //0->无穷大
            visit[j] = 1;

        }
        for (int j = 0; j < 64; j++) {//每个端口一个值可能会被覆盖掉，应该用个栈或向量 //相当于一次走了两步
            path[j] = ""; //0->无穷大
        }
//        path = "";
        bridge =0;
    }
};

//记录起点到每个顶点的最短路径的信息
struct Dis {
    string path;
    double value;
    bool visit;
    int bridge;
    Dis() {
        visit = false;
        value = 2000; //0->无穷大
//        for (int j = 0; j < 64; j++) {
//            value[j] = 2000; //0->无穷大
//        }
        path = "";
        bridge =0;
    }
};

class Graph_DG {
private:
//     double e;
//     double c[64][64];

    int vexnum;   //图的顶点个数
    int edgenum;
    int edge;     //图的边数
    double **arc;   //邻接矩阵
    double **C_ij;
    Dis * dis;   //记录各个顶点最短路径的信息
    Dist * dist;
    V *v;
    E *e;
    C *c;
public:
    //构造函数
    Graph_DG(int vexnum, int edgenum);
    //析构函数
    ~Graph_DG();
    //初始化
    void initialize( double c, int s, double l, string p, string U);
    //创建节点损耗矩阵
    void createnode();
    //计算目的端口到目标节点的连接损失矩阵
    void Y(int begin, int port, int dest, double* loss, int* ecount);
    //创建C_ij
    void createC_ij(int srcn, int srcp, int desn, int desp, int loss);
    //创建E
//    void createE( int edgenum,int srcn, int srcp, int desn, int desp, int loss);
    void createE( );
    //6.10魔改版
    void Dijkstra11(int begin, int ch);
    //6.13
    void LPLS(int begin, int dst, int ch);
    //提取连接port
    int con_port(int end);
    //创建临时矩阵
    void create_W_t();
    //创建临时矩阵
    void print_W_t();
    //锁节点
    void lock(int path, int k);
    //锁节点
    void lock1(int path, int k);
    //解锁
    void unlock(int path);
    //提取路径中元素
    void extract(int path, int k);
    //提取路径中元素
    void extract1(int path, int k);
    //打印最短路径
    void print_path1(int);






    // 判断我们每次输入的的边的信息是否合法
    //顶点从1开始编号
    bool check_edge_value(int start, int end, double weight);
    //创建图
    void createGraph();
    //创建新图
    void createGraph1();
    //创建新图
    void createGraph2();
    //打印邻接矩阵
    void print();
    //打印更新后的邻接矩阵
    void print_new(int begin);
    //求最短路径
    void Dijkstra(int begin);
    //求最短路径
    void Dijkstra1(int begin);
    //求最短路径
    void Dijkstra_new(int begin,int end);
    //打印最短路径
    void print_path(int);
    //随机生成图输入
    void rere(int begin,int end);
    //随机生成图输入
    void reset_G(int begin);
    //随机生成图输入
    double pi(int begin);
    //单侧
    double lp1(int begin,int end);
    //单侧
    double lp2(int begin,int end);
    //LPLF
    double lplf(int begin,int end);
    //打印路径损耗
    void print_loss(int);


};

void randm();

#endif // DIJK_H
