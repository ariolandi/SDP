/**
��������� �� ������������� �� ���� � ����:
��� ���� ����� �� � ����, �� �� ������� � �����.
*/


#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n, m, time;
vector<vector<int> >graph;
vector<bool>used;
vector<int>in, from;

void DFS(int v, int parent){                                     //DFS ��������� � ���� V � ������� �� ���� V
    used[v] = true;                                              //��������� ����� ���� �������
    in[v] = from[v] = time;                                      //�������� ����� �� ���� (� �������� - �������� �� from (� ����� �� ���� ������ �� ������ �� �������������))
    time++;
    for(int i=0; i<graph[v].size(); i++){                        //��������� ������ ������ �� �����
        int x = graph[v][i];
        if(x == parent)continue;                                //��� ��������� � ���������� ��������, ������������ ��� ���������� ��������
        if(used[x]){                                            //��� ����������� � �������, �� ������������� ������ �� ������, ��� ����� ����������
            from[v] = min(in[v], from[x]);
        }
        else {                                                 //� �������� ������, ������������ � DFS �� �����
            DFS(x, v);
            from[v] = min(from[v], from[x]);                   //������ ������������
            if(from[x] > in[v])cout<<x<<" - "<<v<<endl;        //IS_BRIDGE (v, x)
        }
    }
}

int main ()
{
    cin>>n>>m;
    graph.resize(n+1);
    used.resize(n+1);
    in.resize(n+1);
    from.resize(n+1);

    int v, u;
    for(int i=0; i<m; i++){
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    DFS(1, -1);

    for(int i=1; i<=n; i++){
        cout<<i<<" is from "<<from[i]<<endl;
    }

    return 0;
}
