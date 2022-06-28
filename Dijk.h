#ifndef DIJK_H
#define DIJK_H



#pragma once
//#pragma once��һ���Ƚϳ��õ�C/C++��ע��
//ֻҪ��ͷ�ļ����ʼ����������ע��
//���ܹ���֤ͷ�ļ�ֻ������һ�Ρ�

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
��������ʹ��Dijkstra�㷨ʵ��������·��������
���õ��ڽӾ������洢ͼ
*/
//����ڵ�ṹ��
struct V {
    int nodeindex;
    int portnum;
    bool WDMtype;
    int T_num;
    double w[64][64];
    double W_t[64][64];
    string T;  //֧���ŵ����ַ�����Ϊ֧���ŵ���
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
//    string T;  //֧���ŵ����ַ�����Ϊ֧���ŵ���
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

//��¼��㵽ÿ���˿ڵ����·������Ϣ
struct Dist {
    string path[64];
    double value[64];
    bool visit[64];
    int bridge;
    Dist() {
//        visit = false;
//        value = 2000; //0->�����
        for (int j = 0; j < 64; j++) {//ÿ���˿�һ��ֵ���ܻᱻ���ǵ���Ӧ���ø�ջ������ //�൱��һ����������
            value[j] = 2000; //0->�����
            visit[j] = 1;

        }
        for (int j = 0; j < 64; j++) {//ÿ���˿�һ��ֵ���ܻᱻ���ǵ���Ӧ���ø�ջ������ //�൱��һ����������
            path[j] = ""; //0->�����
        }
//        path = "";
        bridge =0;
    }
};

//��¼��㵽ÿ����������·������Ϣ
struct Dis {
    string path;
    double value;
    bool visit;
    int bridge;
    Dis() {
        visit = false;
        value = 2000; //0->�����
//        for (int j = 0; j < 64; j++) {
//            value[j] = 2000; //0->�����
//        }
        path = "";
        bridge =0;
    }
};

class Graph_DG {
private:
//     double e;
//     double c[64][64];

    int vexnum;   //ͼ�Ķ������
    int edgenum;
    int edge;     //ͼ�ı���
    double **arc;   //�ڽӾ���
    double **C_ij;
    Dis * dis;   //��¼�����������·������Ϣ
    Dist * dist;
    V *v;
    E *e;
    C *c;
public:
    //���캯��
    Graph_DG(int vexnum, int edgenum);
    //��������
    ~Graph_DG();
    //��ʼ��
    void initialize( double c, int s, double l, string p, string U);
    //�����ڵ���ľ���
    void createnode();
    //����Ŀ�Ķ˿ڵ�Ŀ��ڵ��������ʧ����
    void Y(int begin, int port, int dest, double* loss, int* ecount);
    //����C_ij
    void createC_ij(int srcn, int srcp, int desn, int desp, int loss);
    //����E
//    void createE( int edgenum,int srcn, int srcp, int desn, int desp, int loss);
    void createE( );
    //6.10ħ�İ�
    void Dijkstra11(int begin, int ch);
    //6.13
    void LPLS(int begin, int dst, int ch);
    //��ȡ����port
    int con_port(int end);
    //������ʱ����
    void create_W_t();
    //������ʱ����
    void print_W_t();
    //���ڵ�
    void lock(int path, int k);
    //���ڵ�
    void lock1(int path, int k);
    //����
    void unlock(int path);
    //��ȡ·����Ԫ��
    void extract(int path, int k);
    //��ȡ·����Ԫ��
    void extract1(int path, int k);
    //��ӡ���·��
    void print_path1(int);






    // �ж�����ÿ������ĵıߵ���Ϣ�Ƿ�Ϸ�
    //�����1��ʼ���
    bool check_edge_value(int start, int end, double weight);
    //����ͼ
    void createGraph();
    //������ͼ
    void createGraph1();
    //������ͼ
    void createGraph2();
    //��ӡ�ڽӾ���
    void print();
    //��ӡ���º���ڽӾ���
    void print_new(int begin);
    //�����·��
    void Dijkstra(int begin);
    //�����·��
    void Dijkstra1(int begin);
    //�����·��
    void Dijkstra_new(int begin,int end);
    //��ӡ���·��
    void print_path(int);
    //�������ͼ����
    void rere(int begin,int end);
    //�������ͼ����
    void reset_G(int begin);
    //�������ͼ����
    double pi(int begin);
    //����
    double lp1(int begin,int end);
    //����
    double lp2(int begin,int end);
    //LPLF
    double lplf(int begin,int end);
    //��ӡ·�����
    void print_loss(int);


};

void randm();

#endif // DIJK_H
