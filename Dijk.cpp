#include"Dijk.h"

//初始化
//Graph_DG::initialize( double c, int s, double l, string p, string U ){
//    for (int i=0;i< this->vexnum, i++ ){
//        if(c[0][i])
//    }
//}

//构造函数
Graph_DG::Graph_DG(int vexnum, int edgenum) {
    //初始化顶点数和边数
    this->vexnum = vexnum;
//    this->edge = edge;
    this->edgenum = edgenum;
    //为邻接矩阵开辟空间和赋初值
    arc = new double*[this->vexnum];
//    C_ij =new double*[this->edgenum];
    dis = new Dis[this->vexnum];
    dist = new Dist [this->vexnum];
    //初始化v的实例
    v = new V[this->vexnum];
    e = new E[this->edgenum];
    c = new C[this->edgenum];
    //边
//    e = new E[this->vexnum][6];
//    for (int i = 0; i < this->vexnum; i++) {
//        V v[i];
//    }

    for (int i = 0; i < 1; i++) {
        arc[i] = new double[this->vexnum];
        for (int k = 0; k < this->vexnum; k++) {
            //邻接矩阵初始化为无穷大
                arc[i][k] = 2000;
        }
    }
}

//析构函数
Graph_DG::~Graph_DG() {
    delete[] dis;
    for (int i = 0; i < this->vexnum; i++) {
        delete this->arc[i];
    }
    delete arc;
}

// 判断我们每次输入的的边的信息是否合法
//顶点从0开始编号
bool Graph_DG::check_edge_value(int start, int end, double weight) {
    if (start<0 || end<0 || start>vexnum || end>vexnum || weight < 0) {
        return false;
    }
    return true;
}

//void random(){
//    for (int i = 0; i < 100; i++)
//        {
//            cout << rand()%100<< " "<<rand()%100<<" "<<rand()/(double)(RAND_MAX/10)<<endl;
//        }
//}

void Graph_DG::createnode(){
//    cout<<"输入节点i的端口损耗矩阵,支持信道"<<endl;
    int node_index;
    bool WDMtype;
    int T;
    int portnum;
    int input,output;
    double loss;
//    string T;
    int count = 0;
    for (int i=0;i<this->vexnum;i++){
//        cout<<"输入节点"<<i<<"的支持信道"<<endl;

//        char str[72];
//        std::cin.getline(str,72);
//        v[i].T=str;
//        std::cout << str << std::endl;

        string str;
        getline(cin, str);
//        getline(cin,str);
        cout<<str<<endl;


        cout<<"请输入节点"<<i<<"的序号 "<<"分束类型 "<<"支持信道数 "<<"端口数量 "<<endl;
        cin >> node_index>>WDMtype>>T>> portnum ;
        v[i].nodeindex=node_index;
        v[i].WDMtype=WDMtype;
        v[i].T_num=T;
        v[i].portnum=portnum;
//        j<(v[i].portnum*(v[i].portnum-1)/2)
        for (int j=0;j<v[i].portnum;j++){
            for(int k=0;k<v[i].portnum;k++){
                cout<<"输入节点"<<i<<"的端口损耗矩阵"<<endl;
                cin >>  input>>output >> loss;
                 v[i].nodeindex=node_index;
                v[i].w[input-1][output-1]=loss;
                v[i].w[output-1][input-1]=loss;
            }

//            ++count;
        }
    }
    //打印节点端口矩阵
    cout<<"打印节点端口矩阵"<<endl;
    cout<<v[2].portnum<<endl;
    for (int i =0;i<this->vexnum;i++){
        for (int j =0;j<v[i].portnum;j++){
            for (int k =0;k<v[i].portnum;k++){
                cout<<v[i].w[j][k]<< " ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }
//    while (count <=this->vexnum*64*64){
//         }
}

//计算目的端口到目标节点的连接损失矩阵
void Graph_DG::Y(int begin, int port, int dest,double* loss, int* ecount){
//    int begin, int port, int dest；
    int temp1=0;
    int temp2=0;
    int m_i=5;
    int count;
//    int m_j=64;
    double min = 2000;
//    int count=0;
    for (int i = 0; i < v[begin].portnum; i++) {

      for (count =0; count<this->edgenum;count++){
        if(e[count].srcn==begin&&e[count].dstn==dest){
//            for(int j=0;j<m_j;j++){
                //dis[degin-1].value还有点问题，不止一条边
                //不加锁
//                if (e[count].srcp-1==i&&v[begin].w[port-1][i]+e[count].weight<min) {
//                    min = v[begin].w[port-1][i]+e[count].weight;
//                    temp1 = i;
//                    temp2= count;

//                }
//            //不加入锁
//            if (e[count].srcp-1==i&&v[begin].w[port][i]+e[count].weight<min) {//我们定义的边是个有向的!!!!!!!!!!!!!!!!!!!!!!!!!目前实现是再加一组边

//                min = v[begin].w[port][i]+e[count].weight;
//                temp1 = i;
//                temp2= count;
//            }

                //加入锁定机制后
                if (e[count].srcp-1==i&&v[begin].W_t[port][i]+e[count].weight<min) {//我们定义的边是个有向的!!!!!!!!!!!!!!!!!!!!!!!!!目前实现是再加一组边

                    min = v[begin].W_t[port][i]+e[count].weight;
                    temp1 = i;
                    temp2= count;

                }

        }
    }
 }
    *loss=min;
    *ecount=temp2;
//    return min;
}
//Y(begin, port, dest, &minloss)

void Graph_DG::createE() {
    cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
    int startn,startp;
    int endn,endp;
    double weight;
    int count = 0;
//    random();
    while (count != this->edgenum) {
        cin >> startn >> startp >>endn>>endp>> weight;
        //首先判断边的信息是否合法
//        while (!this->check_edge_value(start, end, weight)) {
//            cout << "输入的边的信息不合法，请重新输入" << endl;
//            cin >> start >> end >> weight;
//            break;
//        }
        //对邻接矩阵对应上的点赋值
        e[count].srcn = startn;
        e[count].srcp = startp;
        e[count].dstn = endn;
        e[count].dstp = endp;
        e[count].weight = weight;
        //无向图添加上这行代码
//        arc[desn ][desp ] = weight;
//        C_ij[e[count].srcp][e[count].dstp] = weight;
//        //无向图添加上这行代码
//        C_ij[e[count].dstp][e[count].srcp] = weight;
        ++count;
    }
    cout << "输出边" << endl;
    for (int i=0;i<this->edgenum;i++){
        cout<<e[i].srcn<<" "<<e[i].dstn<<" "<<e[i].weight<<endl;
    }
}

void Graph_DG::createC_ij(int srcn, int srcp, int desn, int desp, int loss) {
    cout << "请输入每条边的起点和终点（顶点编号从1开始）以及其权重" << endl;
    int startn,startp;
    int endn,endp;
    double weight;
    int count = 0;
//    random();
    while (count != this->edge) {
        cin >> startn >> startp >>endn>>endp>> weight;
        //首先判断边的信息是否合法
//        while (!this->check_edge_value(start, end, weight)) {
//            cout << "输入的边的信息不合法，请重新输入" << endl;
//            cin >> start >> end >> weight;
//            break;
//        }
        //对邻接矩阵对应上的点赋值
        C_ij[e[count].srcp][e[count].dstp] = weight;
        //无向图添加上这行代码
        C_ij[e[count].dstp][e[count].srcp] = weight;
        ++count;
    }
}


void Graph_DG::print() {
    cout << "图的邻接矩阵为：" << endl;
    int count_row = 0; //打印行的标签
    int count_col = 0; //打印列的标签
    //开始打印
    while (count_row != this->vexnum) {
        count_col = 0;
        while (count_col != this->vexnum) {
            if (count_row!=count_col&&arc[count_row][count_col] == 2000)
                cout << "∞" << " ";
            else if (count_row==count_col&&arc[count_row][count_col] == 2000)
                cout << "0" << " ";
            else
            cout << arc[count_row][count_col] << " ";
            ++count_col;
        }
        cout << endl;
        ++count_row;
    }
}

void Graph_DG::print_new(int begin) {
    cout << "更新后的邻接矩阵为：" << endl;
    int count_row = 0; //打印行的标签
    int count_col = 0; //打印列的标签
//    int i = 0;
    //开始打印
    while (count_row != this->vexnum) {
        count_col = 0;
        //不更新整个邻接矩阵
        if (count_row!=begin){
            while (count_col != this->vexnum) {
                if (count_row!=count_col&&arc[count_row][count_col] == 2000)
                    cout << "∞" << " ";
                else if (count_row==count_col&&arc[count_row][count_col] == 2000)
                    cout << "0" << " ";
                else
                cout << arc[count_row][count_col] << " ";
                ++count_col;
            }
                cout << endl;
    }
//        //更新整个邻接矩阵，待完善
//        if (count_row!=begin){
//            while (count_col != this->vexnum) {
////                if (count_row!=count_col&&arc[count_row][count_col] == 2000)
////                    cout << "∞" << " ";
////                else if (count_row==count_col&&arc[count_row][count_col] == 2000)
////                    cout << "0" << " ";
////                else
////                double temp=dis[count_row].value+dis[count_col].value;
//                if (count_row==count_col){
//                    cout<<0<<" ";
//                }
//                else cout << dis[count_row].value+dis[count_col].value << " ";
//                ++count_col;
//            }
//                cout << endl;
//    }
        else{
             while (count_col != this->vexnum) {
                  cout << dis[count_col].value << " ";
                  ++count_col;
                  }
                cout << endl;
        }
//            cout << dis[count_col].value << " ";
//            ++count_col;
        ++count_row;
    }
}


//6.11 多端口dijkstra, 纠缠源到所有节点
void Graph_DG::Dijkstra11(int begin, int ch){
    //首先初始化我们的dis数组
    cout<<"开始运行算法"<<endl;
    int i;
//    int t=2000;
    dist[0].visit[0] = true;
    for (i = 1; i < this->vexnum; i++) {
        //设置当前的路径
//        dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
//        dis[i].path = to_string(begin)+" "+to_string(i+1);
//        dis[i].value = arc[begin-1][i];
        //初始化L，P，U
        for (int n = 0; n <v[i].portnum;n++) {//每个端口一个值可能会被覆盖掉，应该用个栈或向量 //相当于一次走了两步
            dist[i].visit[n] = false;

        }

        for (int j=0;j<this->edgenum;j++){
//            if(e[j].srcn==begin&&e[j].weight<t){
//                t=e[j].weight;
//            }


              for(int k=0;k<v[i].portnum;k++){
                    if(e[j].srcn==begin&&e[j].dstn==i&&e[j].dstp==k){
                        dist[i].value[k]=e[j].weight;

//                  string str;
//                  str=to_string(e[j].weight);
//                  str=str.substr(0,str.size()-5);
//                  dis[i].path = "0 "+to_string(e[j].srcn)+" "+to_string(e[j].srcp)+" "+to_string(e[j].dstn)+" "+to_string(e[j].dstp)+" "+str;
//                        dist[i].path =to_string(e[j].srcn)+" "+to_string(e[j].srcp)+" "+to_string(e[j].dstn)+" "+to_string(e[j].dstp);
                    dist[i].path[k] = "0 1 1 1";
//                        dis[i].path = "0 "+to_string(e[begin].srcn)+" "+to_string(e[begin].srcp)+" "+to_string(e[begin].dstn)+" "+to_string(e[begin].dstp)+" "+to_string(e[begin].weight)+" "+to_string(e[i+1].srcn)+" "+to_string(e[i+1].srcp)+" "+to_string(e[i+1].dstn)+" "+to_string(e[i+1].dstp)+" "+to_string(e[i+1].weight);
                         break;

                }
            else{
//                for(int k=0;k<v[i].portnum;k++){
                dist[i].value[k]=2000;
//                }
//                dist[i].path ="0 1 1 1";
            }
          }
        }
    }
    dist[1].value[0]=e[0].weight;////////草草草草草草草草草草草草
//    create_W_t();
    //设置起点的到起点的路径为0
//    dis[begin].value = 0;
//    dis[begin].visit = true;
    cout<<"初始化完成"<<endl;

    for (int i=1; i<this->vexnum;i++){
        double te=2000;
        int ind=0;
         for(int k=0;k<v[i].portnum;k++){
             if(dist[i].value[k]<2000){
                 te=dist[i].value[k];
                 ind=i;
             }
         }
        cout<<i<<"的损耗值为 "<<te<<endl;
        cout<<i<<"的路径为 "<<dist[i].path<<endl;
    }

    int count = 0;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    int temp1=0,temp2=0;
    while (count != 30) {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
//        int temp=0;
//        double min =2000;

         double min =2000;
        for (i = 1; i < this->vexnum; i++) {

            for(int k=0;k<v[i].portnum;k++){
            if (!dist[i].visit[k] && dist[i].value[k]<min) {

                min = dist[i].value[k];
                temp1 = i;
                temp2 = k;

            }
            }
            cout<<temp1<<"的min为"<<"端口"<<temp2<<min<<endl;
        }

//        cout<<"第"<<count<<"轮"<<min<<endl;
//        cout<<"第"<<count<<"轮"<<min<<endl;

        cout<<"当前最小index为"<<temp1<<"的端口"<<temp2<<endl;
        cout<<endl;
        cout<<endl;

        //cout << temp + 1 << "  "<<min << endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dist[temp1].visit[temp2] = true;
        ++count;
        int port=0;

        for (i = 0; i < this->vexnum; i++) {
//            for(int k=0;k<v[temp1].portnum;k++){

//                port=con_port(temp);//找到连接端口
                double l=0;
                 int   ecount=0;
    //             create_W_t();
                Y(temp1, temp2, i,&l,&ecount);
                /****************调试信息**************************
                cout<<l<<" "<<ecount<<endl;
                cout<<e[ecount].srcn<<e[ecount].srcp<<e[ecount].dstn<<e[ecount].dstp<<e[ecount].weight<<endl;
                cout<<temp1<<" 连接port: "<<k<<e[ecount].srcp<<"  端口到节点"<<i<<"的端口"<<e[ecount].dstp<<"的最小loss： "<<l<<endl;
                cout<<dist[temp1].value[k]<<"草"<<l<<endl;
//                   ******************************************/

                //&&!dist[i].visit  可能会跑到已经探索过得节点，但端口未探索过
            if (fabs(ch-33.5)<v[temp1].T_num/2&&!dist[i].visit[e[ecount].dstp-1]&& (dist[temp1].value[temp2] + l< dist[i].value[e[ecount].dstp-1]) ){//6.15凌晨把2000改成dist[i].value[e[ecount].dstp-1]，每个端口的值不小于以前的就不更新，成了！（明天白天加个锁）
                //如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
                dist[i].value[e[ecount].dstp-1] =dist[temp1].value[temp2] + l;
//                dist[i].value[e[ecount].dstp]
                cout<<i<<"的端口"<<e[ecount].dstp<<"的路径损为<<<<<<<<<<<<<<<<<<<<<<<<<<"<<dist[i].value[e[ecount].dstp-1] <<endl;
//                dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
                int bridge=ecount   ;
                string str1;
                str1=to_string(e[bridge].weight);
                str1=str1.substr(0,str1.size()-5);
//                dis[i].path = dis[temp].path + " " + to_string(e[bridge].srcn)+" "+to_string(e[bridge].srcp)+" "+to_string(e[bridge].dstn)+" "+to_string(e[bridge].dstp)+" "+str1;
                dist[i].path[e[ecount].dstp-1] = dist[temp1].path[temp2] + " " + to_string(e[bridge].srcn)+" "+to_string(e[bridge].srcp)+" "+to_string(e[bridge].dstn)+" "+to_string(e[bridge].dstp);
            }
//            }


        }
    }

}

//LPLS,纠缠源到目标节点s
void Graph_DG::LPLS(int begin, int dst, int ch){
    //首先初始化我们的dis数组
    cout<<"开始运行算法"<<endl;
    int i;
//    int t=2000;
    //初始化
    dis[0].visit = false;
    for (i = 1; i < this->vexnum; i++) {
        //设置当前的路径
//        dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
//        dis[i].path = to_string(begin)+" "+to_string(i+1);
//        dis[i].value = arc[begin-1][i];
        //初始化L，P，U
        dis[i].visit = false;
        for (int j=0;j<this->edgenum;j++){
//            if(e[j].srcn==begin&&e[j].weight<t){
//                t=e[j].weight;
//            }

            if(e[j].srcn==begin&&e[j].dstn==i){
                  dis[i].value=e[j].weight;
//                  string str;
//                  str=to_string(e[j].weight);
//                  str=str.substr(0,str.size()-5);
//                  dis[i].path = "0 "+to_string(e[j].srcn)+" "+to_string(e[j].srcp)+" "+to_string(e[j].dstn)+" "+to_string(e[j].dstp)+" "+str;
                  dis[i].path = "0 1 1 1 "+to_string(e[j].srcn)+" "+to_string(e[j].srcp)+" "+to_string(e[j].dstn)+" "+to_string(e[j].dstp);
//                  dis[i].path = "0 "+to_string(e[begin].srcn)+" "+to_string(e[begin].srcp)+" "+to_string(e[begin].dstn)+" "+to_string(e[begin].dstp)+" "+to_string(e[begin].weight)+" "+to_string(e[i+1].srcn)+" "+to_string(e[i+1].srcp)+" "+to_string(e[i+1].dstn)+" "+to_string(e[i+1].dstp)+" "+to_string(e[i+1].weight);
                  break;
            }
            else{
                dis[i].value=2000;
                dis[i].path = "0 1 1 1 ";
            }
        }
    }

//    create_W_t();
    //设置起点的到起点的路径为0
//    dis[begin].value = 0;
//    dis[begin].visit = true;
    cout<<"初始化完成"<<endl;
    for (int i=0; i<this->vexnum;i++){
        cout<<i<<"的损耗值为 "<<dis[i].value<<endl;
        cout<<i<<"的路径为 "<<dis[i].path<<endl;
    }

    int count = 2;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    while (count != this->vexnum) {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;
        int min = 2000;
        for (i = 1; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        if(dis[dst].visit){
            cout<<"已遍历dst"<<endl;
            cout<<"纠缠源到"<<dst<<"的损耗为："<<dis[dst].value<<endl;
            cout<<"纠缠源到"<<dst<<"的路径为："<<dis[dst].path<<endl;
            break;
        }
        cout<<"当前最小index为"<<temp<<endl;
        //cout << temp + 1 << "  "<<min << endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;
        int port=0;

        for (i = 0; i < this->vexnum; i++) {
            //注意这里的条件arc[temp][i]!=2000必须加，不然会出现溢出，从而造成程序异常
//            for(int k=0;k<=this->edgenum;k++){
//                if (e[k].dstn==temp){
//                    port=con_port(temp);//找到连接端口
//                }
//            }
            port=con_port(temp);//找到连接端口
            double l=0;
             int   ecount=0;
//             create_W_t();
            Y(temp, port, i,&l,&ecount);
            cout<<l<<" "<<ecount<<endl;
            cout<<"连接port: "<<port<<"  端口到节点"<<i<<"的最小loss： "<<l<<endl;
            if (fabs(ch-33.5)<v[temp].T_num/2&&!dis[i].visit && (dis[temp].value + l< dis[i].value) ){
                //如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
                dis[i].value = dis[temp].value + l;
//                dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
                int bridge=ecount   ;
                string str1;
                str1=to_string(e[bridge].weight);
                str1=str1.substr(0,str1.size()-5);
//                dis[i].path = dis[temp].path + " " + to_string(e[bridge].srcn)+" "+to_string(e[bridge].srcp)+" "+to_string(e[bridge].dstn)+" "+to_string(e[bridge].dstp)+" "+str1;
                dis[i].path = dis[temp].path + " " + to_string(e[bridge].srcn)+" "+to_string(e[bridge].srcp)+" "+to_string(e[bridge].dstn)+" "+to_string(e[bridge].dstp);
            }
        }
    }

}

void Graph_DG::Dijkstra(int begin){
    //首先初始化我们的dis数组
    int i;
    for (i = 0; i < this->vexnum; i++) {
        //设置当前的路径
//        dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        dis[i].path = to_string(begin)+" "+to_string(i+1);
        dis[i].value = arc[begin-1][i];
    }
    //设置起点的到起点的路径为0
    dis[begin-1 ].value = 0;
    dis[begin-1 ].visit = true;

    int count = 1;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    while (count != this->vexnum) {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;
        int min = 2000;
        for (i = 0; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        //cout << temp + 1 << "  "<<min << endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;
        for (i = 0; i < this->vexnum; i++) {
            //注意这里的条件arc[temp][i]!=2000必须加，不然会出现溢出，从而造成程序异常
            if (!dis[i].visit && arc[temp][i]!=2000 && (dis[temp].value + arc[temp][i])+0.4 < dis[i].value) {
                //如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度
                dis[i].value = dis[temp].value + arc[temp][i];
//                dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
                dis[i].path = dis[temp].path + " " + to_string(i+1);
            }
        }
    }

}

void Graph_DG::Dijkstra1(int begin){
    //首先初始化我们的dis数组
    int i;
    for (i = 0; i < this->vexnum; i++) {
        //设置当前的路径
//        dis[i].path = "v" + to_string(begin) + "-->v" + to_string(i + 1);
        dis[i].path = to_string(begin)+" "+to_string(i+1);
        dis[i].value = arc[begin-1][i];
        dis[i].visit = false;
    }
    //设置起点的到起点的路径为0
    dis[begin-1 ].value = 0;
    dis[begin-1 ].visit = true;

    int count = 1;
    //计算剩余的顶点的最短路径（剩余this->vexnum-1个顶点）
    while (count != this->vexnum) {
        //temp用于保存当前dis数组中最小的那个下标
        //min记录的当前的最小值
        int temp=0;
        int min = 2000;
        for (i = 0; i < this->vexnum; i++) {
            if (!dis[i].visit && dis[i].value<min) {
                min = dis[i].value;
                temp = i;
            }
        }
        //cout << temp + 1 << "  "<<min << endl;
        //把temp对应的顶点加入到已经找到的最短路径的集合中
        dis[temp].visit = true;
        ++count;
        for (i = 0; i < this->vexnum; i++) {
            //注意这里的条件arc[temp][i]!=2000必须加，不然会出现溢出，从而造成程序异常
            if (!dis[i].visit && arc[temp][i]!=2000 && (dis[temp].value + arc[temp][i])+0.4 < dis[i].value) {
                //如果新得到的边可以影响其他为访问的顶点，那就就更新它的最短路径和长度

                dis[i].value = dis[temp].value + arc[temp][i];
//                dis[i].path = dis[temp].path + "-->v" + to_string(i + 1);
                dis[i].path = dis[temp].path + " " + to_string(i+1);
            }
        }
    }

}

void Graph_DG::Dijkstra_new(int begin,int end){
    string str,str1,path1;
    str = "v" + to_string(begin);
    str1="v" + to_string(end);
    cout << "从"<<str<<"到"<<str1<<"的最短路径为：" << endl;
    if (dis[begin].value!=2000&& dis[end].value!=2000){
//         cout << dis[begin-1].path << "-->v" << dis[end-1].path << endl;
        //调用reverse函数进行反转
         path1=dis[begin].path;
//         cout << path1 << endl;
//         path1.substr(0, path1.length() - 2);
         path1.erase(path1.begin());
//         cout << path1 << endl;
         reverse(path1.begin(), path1.end());
//         cout << path1 << endl;
//         cout << dis[end-1].path << endl;
         cout<< path1 << dis[end].path << " 总损耗为："<<dis[begin].value+dis[end].value<<" dB"<<endl;
    }
    else {
         cout << "是无最短路径的" << endl;
        }
}

void deal(vector<string>&res, string& str, char delim = ' ')
{
    stringstream ss;
    //sstringstream可以完成对字符串的切分，还能完成字符串和数字之间的转换
    ss << str;
    string tmp;
    while (ss >> tmp)
    {
        res.push_back(tmp);
    }
}

void Graph_DG::create_W_t(){
    //创建临时矩阵  6.13
    cout<<"创建临时矩阵 "<<endl;
//        double W_t[10][10]={};
//        W_t = new double*[v[temp1].portnum];
    for (int i=0;i<this->vexnum;i++){
        for (int m=0; m<v[i].portnum;m++){
            for (int n=0; n<v[i].portnum;n++){
                v[i].W_t[m][n]=v[i].w[m][n];
            }
        }
    }

}

void Graph_DG::print_W_t(){
    //创建临时矩阵  6.13
    cout<<"打印临时矩阵!!!! "<<endl;
//        double W_t[10][10]={};
//        W_t = new double*[v[temp1].portnum];
    for (int i =2;i<3;i++){
        for (int j =0;j<v[i].portnum;j++){
            for (int k =0;k<v[i].portnum;k++){
                cout<<v[i].W_t[j][k]<< " ";
            }
            cout<<endl;
        }
    }

}

void Graph_DG::extract(int path, int k){
    string str;
    str = dist[path].path[k];
    vector<string> res;
//    for (int i = 0; i < str.size(); i++)
//    {
//        if (!isalnum(str[i]))//判断其是否为字母或数字
//        {
////            str[i] = ' ';
//        }
//    }
    cout<<str<<endl;
    deal(res, str);
    cout<<str<<endl;
    for (int i = 2; i <=res.size() - 3; i+=2)
    {
//        temp1=res[i]-1;
//        temp2=res[i+1]-1;
        int temp1 = stoi(res[i],0,10);
        int temp2 = stoi(res[i+1],0,10);

        cout<<temp1<<" "<<temp2<<endl;

//        arc[temp1-1][temp2-1]=2000;
//        arc[temp2-1][temp1-1]=2000;
////        arc[1][2]=2000;
    }
}

void Graph_DG::extract1(int path, int k){
    cout<<"619测试！！！！！！！！！！！！"<<endl;
    string str;
    str = dist[path].path[k];
    vector<string> res;
//    for (int i = 0; i < str.size(); i++)
//    {
//        if (!isalnum(str[i]))//判断其是否为字母或数字
//        {
////            str[i] = ' ';
//        }
//    }
    cout<<str<<endl;
    deal(res, str);
    cout<<str<<endl;
    for (int i = 2; i <=res.size() - 3; i+=4)
    {
//        temp1=res[i]-1;
//        temp2=res[i+1]-1;
        int temp1 = stoi(res[i],0,10);
        int temp2 = stoi(res[i+1],0,10);
        int temp3 = stoi(res[i+2],0,10);
        int temp4 = stoi(res[i+3],0,10);

        cout<<temp1<<" "<<temp2<<" "<<temp3<<" "<<temp4<<endl;

//        arc[temp1-1][temp2-1]=2000;
//        arc[temp2-1][temp1-1]=2000;
////        arc[1][2]=2000;
    }
}

//6.16 判定当节点为wss时，不锁矩阵
void Graph_DG::lock(int path,int k){////锁哪些端口很重要，wss不能锁死
    string str;
    str = dist[path].path[k];
    vector<string> res;
//    for (int i = 0; i < str.size(); i++)
//    {
//        if (!isalnum(str[i]))//判断其是否为字母或数字
//        {
////            str[i] = ' ';
//        }
//    }
    cout<<str<<endl;
    deal(res, str);
    cout<<str<<endl;
    int round=0;

    for (int i = 2; i <=res.size() - 3; i+=2)
//    for (int i = 3; i <=res.size() - 1; i+=2)
    {
//        temp1=res[i]-1;
//        temp2=res[i+1]-1;

        int temp1 = stoi(res[i],0,10);
        int temp2 = stoi(res[i+1],0,10);
        cout<<temp1<<" "<<temp2<<endl;
//        for (int j=0;j<v[temp1].portnum;j++){
//            v[temp1].w[temp2][j]=-v[temp1].w[temp2][j];
//        }
        //和前一个相同，改变列,缺一个条件
        if (round%2==1&&v[temp1].WDMtype==0){
            for (int j=0;j<v[temp1].portnum;j++){
                v[temp1].w[j][temp2-1]=-v[temp1].w[j][temp2-1];
                v[temp1].w[temp2-1][j]=-v[temp1].w[temp2-1][j];
            }
            round++;
        }
        else if (round%2==0&&v[temp1].WDMtype==0){
            for (int k=0;k<v[temp1].portnum;k++){
                v[temp1].w[temp2-1][k]=-v[temp1].w[temp2-1][k];
                v[temp1].w[k][temp2-1]=-v[temp1].w[k][temp2-1];

            }
            round++;
        }

        cout<<"打印节点端口矩阵 "<<endl;
//        cout<<v[2].portnum<<endl;
        for (int i =2;i<3;i++){
            for (int j =0;j<v[temp1].portnum;j++){
                for (int k =0;k<v[temp1].portnum;k++){
                    cout<<v[temp1].w[j][k]<< " ";
                }
                cout<<endl;
            }
        }

        //创建临时矩阵  6.13
        cout<<"负值设为无穷 "<<endl;
//        double W_t[10][10]={};
//        W_t = new double*[v[temp1].portnum];
        for (int m=0; m<v[temp1].portnum;m++){
            for (int n=0; n<v[temp1].portnum;n++){
                v[temp1].W_t[m][n]=v[temp1].w[m][n]; //不在这里创建了
                if(v[temp1].W_t[m][n]<0){
                    v[temp1].W_t[m][n]=2000;
                }

            }
        }
        //打印临时节点端口矩阵
        cout<<"打印节点"<<temp1<<"的临时节点端口矩阵 "<<endl;
//        cout<<v[2].portnum<<endl;
//        for (int i =2;i<3;i++){
            for (int j =0;j<v[temp1].portnum;j++){
                for (int k =0;k<v[temp1].portnum;k++){
                    cout<<v[temp1].W_t[j][k]<< " ";
                }
                cout<<endl;
            }
        }
//    }
    print_W_t();
}


void Graph_DG::lock1(int path,int k){////锁哪些端口很重要，wss不能锁死
    string str;
    str = dist[path].path[k];
    vector<string> res;
//    for (int i = 0; i < str.size(); i++)
//    {
//        if (!isalnum(str[i]))//判断其是否为字母或数字
//        {
////            str[i] = ' ';
//        }
//    }
    cout<<str<<endl;
    deal(res, str);
    cout<<str<<endl;
//    int round=0;

    for (int i = 2; i <=res.size() - 3; i+=4)
    {
//        temp1=res[i]-1;
//        temp2=res[i+1]-1;
        int temp1 = stoi(res[i],0,10);
        int temp2 = stoi(res[i+1],0,10);
        int temp3 = stoi(res[i+2],0,10);
        int temp4 = stoi(res[i+3],0,10);

        cout<<temp1<<" "<<temp2<<" "<<temp3<<" "<<temp4<<endl;
//        for (int j=0;j<v[temp1].portnum;j++){
//            v[temp1].w[temp2][j]=-v[temp1].w[temp2][j];
//        }
        //和前一个相同，改变列,缺一个条件
        if (v[temp1].WDMtype==0){
            for (int j=0;j<v[temp1].portnum;j++){
                v[temp1].w[temp2-1][temp2-1]=temp4;
                v[temp1].w[temp4-1][temp4-1]=temp2;
            }
//            round++;
        }
//        else if (round%2==0&&v[temp1].WDMtype==0){
//            for (int k=0;k<v[temp1].portnum;k++){
//                v[temp1].w[temp2-1][k]=-v[temp1].w[temp2-1][k];
//                v[temp1].w[k][temp2-1]=-v[temp1].w[k][temp2-1];

//            }
//            round++;
//        }

        cout<<"打印节点端口矩阵 "<<endl;
//        cout<<v[2].portnum<<endl;
        for (int i =2;i<3;i++){
            for (int j =0;j<v[temp1].portnum;j++){
                for (int k =0;k<v[temp1].portnum;k++){
                    cout<<v[temp1].w[j][k]<< " ";
                }
                cout<<endl;
            }
        }

        //创建临时矩阵  6.13
        cout<<"负值设为无穷 "<<endl;
//        double W_t[10][10]={};
//        W_t = new double*[v[temp1].portnum];

        for (int m=0; m<v[temp1].portnum;m++){
            int x=0;
            double t=0;
            if(v[temp1].w[m][m]<2000){
                x=v[temp1].w[m][m];//锁的端口
                t=v[temp1].w[m][x-1];//该端口的值
                cout<<x<<" "<<t<<endl;
             for (int n=0; n<v[temp1].portnum;n++){
                      v[temp1].W_t[m][n]=2000;
                      }
              v[temp1].W_t[m][x-1]=t;



            }
            else{
                for (int n=0; n<v[temp1].portnum;n++){
                    v[temp1].W_t[m][n]=v[temp1].w[m][n];
            }

        }

//        for (int m=0; m<v[temp1].portnum;m++){
//            for (int n=0; n<v[temp1].portnum;n++){
//                    v[temp1].W_t[temp2][n]=2000;
//                    v[temp1].W_t[temp2][x]=t;

//            }
//        }
        //打印临时节点端口矩阵
        cout<<"打印节点"<<temp1<<"的临时节点端口矩阵 "<<endl;
//        cout<<v[2].portnum<<endl;
//        for (int i =2;i<3;i++){
            for (int j =0;j<v[temp1].portnum;j++){
                for (int k =0;k<v[temp1].portnum;k++){
                    cout<<v[temp1].W_t[j][k]<< " ";
                }
                cout<<endl;
            }
        }
//    }
    print_W_t();
}

}
void Graph_DG::unlock(int path){
    cout<<"解锁，释放资源"<<endl;
    string str;
    str = dis[path].path;
    vector<string> res;
//    for (int i = 0; i < str.size(); i++)
//    {
//        if (!isalnum(str[i]))//判断其是否为字母或数字
//        {
////            str[i] = ' ';
//        }
//    }
    cout<<str<<endl;
    deal(res, str);
    cout<<str<<endl;
    int round=0;


    for (int i = 1; i <=res.size() - 1; i+=2)
    {
//        temp1=res[i]-1;
//        temp2=res[i+1]-1;

        int temp1 = stoi(res[i],0,10);
        //恢复值
        for (int m=0; m<v[temp1].portnum;m++){
            for (int n=0; n<v[temp1].portnum;n++){
//                v[temp1].w[m][n]=v[temp1].w[m][n];
                if(m==n){
                    v[temp1].w[m][n]=2000;
                }

            }
        }

        //打印临时节点端口矩阵
        cout<<"打印节点端口矩阵 "<<endl;
//        cout<<v[2].portnum<<endl;
        for (int i =2;i<3;i++){
            for (int j =0;j<v[temp1].portnum;j++){
                for (int k =0;k<v[temp1].portnum;k++){
                    cout<<v[temp1].w[j][k]<< " ";
                }
                cout<<endl;
            }
        }
    }


}

int Graph_DG::con_port(int end) {
        string str;
//        cout<<"原字符串"<<dis[begin].path<<endl;
        str=dis[end].path;
        cout<<"原字符串为"<<dist[end].path<<endl;
        vector<string> res;
        for (int i = 0; i < str.size(); i++)
        {
            if (!isalnum(str[i]))//判断其是否为字母或数字
            {
                str[i] = ' ';
            }
        }
        deal(res, str);
//        if (dist[end].value!=2000){
//        cout << "从"<<begin<<"到"<<end<<"的最短路径总损耗为：" <<dis[begin-1].value+dis[end-1].value<<" dB"<< endl;
//        cout << res[res.size() - 1];
        string s=res[res.size() - 1];
        cout<<s<<endl;
        int a;
        a = atoi(s.c_str());
        cout<<a<<endl;
        return a;
}


void Graph_DG::rere(int begin,int end) {
        string str;
//        cout<<"原字符串"<<dis[begin].path<<endl;
        str=dis[begin-1].path;
        vector<string> res;
        for (int i = 0; i < str.size(); i++)
        {
            if (!isalnum(str[i]))//判断其是否为字母或数字
            {
                str[i] = ' ';
            }
        }
        deal(res, str);
        if (dis[begin-1].value!=2000&& dis[end-1].value!=2000){
        cout << "从"<<begin<<"到"<<end<<"的最短路径总损耗为：" <<dis[begin-1].value+dis[end-1].value<<" dB"<< endl;
        cout << res[res.size() - 1];
        for (int i = res.size() - 2; i >= 1; i--)
        {
            cout << " " << res[i];
        }

        cout<<" " <<dis[end-1].path<<endl;
        }
        else {
             cout <<"从"<<begin<<"到"<<end<< "是无最短路径的" << endl;
            }
//        cout << " 总损耗为："<<dis[begin].value+dis[end].value<<" dB"<< endl;
}

double Graph_DG::pi(int begin) {
    string str;
    str = "v" + to_string(begin);
    cout << "以"<<str<<"为终点的最短路径为：" << endl;
        if(dis[begin-1].value!=2000)
        cout << dis[begin-1].path << "  总损耗为" << dis[begin-1].value<< " dB"  << endl;
        else {
            cout << dis[begin-1].path << "是无最短路径的" << endl;
        }
    return dis[begin-1].value;
}

double Graph_DG::lp1(int begin,int end){
    double loss1=0,loss2=0;
    loss1=pi(begin);
    reset_G(begin);
    loss2=pi(end);
    return loss1+loss2;
}

double Graph_DG::lp2(int begin,int end){
    double loss1=0,loss2=0;
    loss1=pi(end);
    reset_G(end);
    loss2=pi(begin);
    return loss1+loss2;
}



void Graph_DG::reset_G(int begin){
//    cout<<dis[begin-1].path<<endl;

    string str;
//        cout<<"原字符串"<<dis[begin].path<<endl;
    str=dis[begin-1].path;
    vector<string> res;
    for (int i = 0; i < str.size(); i++)
    {
        if (!isalnum(str[i]))//判断其是否为字母或数字
        {
            str[i] = ' ';
        }
    }
    deal(res, str);
//    for (int i = 0; i <=res.size() - 1; i++)
//    {
//        cout << res[i]<<endl;
//    }

//    for (int i = 0; i <=res.size() - 2; i++)
//    {
//        cout << res[i]<<" "<<res[i+1]<<endl;
//    }

//    int temp1,temp2=0;
    for (int i = 0; i <=res.size() - 2; i++)
    {
//        temp1=res[i]-1;
//        temp2=res[i+1]-1;
        int temp1 = stoi(res[i],0,10);
        int temp2 = stoi(res[i+1],0,10);

//        cout<<temp1<<" "<<temp2<<endl;

        arc[temp1-1][temp2-1]=2000;
        arc[temp2-1][temp1-1]=2000;
//        arc[1][2]=2000;
    }
//    if (dis[begin].value!=2000){
//    cout << res[res.size() - 1];
//    for (int i = res.size() - 2; i >= 1; i--)
//    {
//        cout << " " << res[i];
//    }
//    }
}

void Graph_DG::print_path1(int begin) {
    string str;
    str = "v" + to_string(begin);
    cout << "以"<<str<<"为起点的图的最短路径为：" << endl;
    for (int i = 1; i != this->vexnum; i++) {
        double te=2000;
        int t;
        for(int k=0;k<v[i].portnum;k++){
            if(dist[i].value[k]<te){
                te=dist[i].value[k];
                t=k;
            }
        }
        if(te<2000){
            cout<<i <<"的路径为"<< dist[i].path[t] << "  总损耗为" << te<< " dB"  << endl;
        }

        else {
            cout<<endl;
            cout <<i <<"的路径为  "<< dist[i].path[t] << "是无最短路径的" << "  总损耗为" << te<< " dB" <<endl;

        }
    }
}

void Graph_DG::print_path(int begin) {
    string str;
    str = "v" + to_string(begin);
    cout << "以"<<str<<"为起点的图的最短路径为：" << endl;
    for (int i = 0; i != this->vexnum; i++) {
        if(dis[i].value!=2000)
        cout<<i <<"的路径为"<< dis[i].path << "  总损耗为" << dis[i].value<< " dB"  << endl;
        else {
            cout<<endl;
            cout <<i <<"的路径为  "<< dis[i].path << "是无最短路径的" << endl;

        }
    }
}

void Graph_DG::print_loss(int begin) {
//    string str;
//    str = "v" + to_string(begin);
//    cout << "以"<<str<<"为起点的图的最短路径为：" << endl;
    for (int i = 0; i != this->vexnum; i++) {
        if(dis[i].value!=2000)
        cout << dis[i].value<< " ";
        else {
            cout << "∞" << " ";
        }
    }
}


