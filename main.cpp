#include"Dijk.h"
//������������Ͷ�������ֵ�Ƿ���Ч�������Լ�����Ϊɶ��
//�������ͱ����Ĺ�ϵ�ǣ�((Vexnum*(Vexnum - 1)) / 2) < edge
bool check(int Vexnum, int edge) {
    if (Vexnum < 0 || edge <= 0 || ((Vexnum*(Vexnum - 1)) / 2) < edge)
        return false;
    return true;
}

void random(){
//    srand((int)time(0));
    for (int i = 0; i < 100; i++)
        {
                   cout << rand()%100<< " "<<fixed<<setprecision(1)<<rand()%100<<" "<<rand()/(double)(RAND_MAX/10)<<endl;
        }
}


void random1(){
    srand((int)time(0));
    for (int i = 0; i < 200; i++)
        {
//                   cout << "("<<rand()%100<< ","<<rand()%100<<"),"<<endl;
//                    cout<<rand()%100+1<< " ";
                    cout<<fixed<<setprecision(1)<<rand()/(double)(RAND_MAX/10)<<" ";
        }
}

int main(int argc,char *argv[]) {
//    random1();
    int vexnum; int edgenum;
//    int begin;

    cout << "����ͼ�Ķ�������ͱߵ�������" << endl;
        cin >> vexnum >>edgenum;
//    random();
    cout << "ܳ1111111111" << endl;
    while (!check(vexnum, edgenum)) {
        cout << "�������ֵ���Ϸ�������������" << endl;

        cin >> vexnum >>edgenum;
    }
    Graph_DG graph(vexnum,edgenum);

//    graph.createGraph2();
    graph.createnode();
    graph.createE();
    graph.create_W_t();
//    graph.print();

//    cout << "������㣺" << endl;
//    cin >> begin;
//    graph.Dijkstra(begin);
//    graph.print_path(begin);
//    graph.print_new(begin);

    int ch,dst;
//    cout << "Ŀ��ڵ�ͷ����ŵ���" << endl;
//    cin >> dst>>ch;
//    graph.LPLS(0,dst,ch);

    cin >> ch;
    int k=0;
//     graph.print();
    cout << "�����ŵ���" << endl;
    graph.Dijkstra11(k,ch);
    cout<<"·������������"<<endl;
    graph.print_path1(k);
    cout << "��������·����" << endl;
    int lockpath1;
    cin>>lockpath1;
    graph.extract(lockpath1,0);
    graph.extract1(lockpath1,0);
    graph.lock1(lockpath1,0);
//    graph.create_W_t();
//    graph.unlock(lockpath);
    graph.print_W_t();
    graph.Dijkstra11(k,ch);
    graph.print_path1(k);

    cout << "��������·����" << endl;
    int lockpath2;
    cin>>lockpath2;
    graph.extract1(lockpath2,0);
    graph.lock1(lockpath2,0);
//    graph.create_W_t();
//    graph.unlock(lockpath);
    graph.print_W_t();
    graph.Dijkstra11(k,ch);
    graph.print_path1(k);

    cout << "��������·����" << endl;
    int lockpath3;
    cin>>lockpath3;
    graph.extract1(lockpath3,0);
    graph.lock1(lockpath3,0);
//    graph.create_W_t();
//    graph.unlock(lockpath);
    graph.print_W_t();
    graph.Dijkstra11(k,ch);
    graph.print_path1(k);

    graph.print_path1(k);
    cin>>vexnum;
//    graph.print();
//     graph.print_new(0);

}



