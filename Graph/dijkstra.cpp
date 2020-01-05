/**
��������� �� �������� �� ���-��� ��� � ���� �� ����� ���� �� ������ ��������.
�������� � �����:
* ���������� ���� ��� ����������� �����
* ������������ ���� ��� ����������� �����
��������: O(M log(N))
������������: https://www.cs.usfca.edu/~galles/visualization/Dijkstra.html
*/

#include<iostream>
#include<vector>
#include<queue>
#define INF 99999999999
using namespace std;
int n, m;
vector<vector<pair<int, int> > >graph;
vector<int>d;

void dijkstra(int v){                               //Dijkstra ��������� �� ���� V
    priority_queue<pair<int, int> >q;
    d.assign(n+1, INF);                             //������������ �������������� �� ������ d - ���� ���� ���� �� � ��������, ����� �������� � ���������� 0
    d[v] = 0;
    q.push(make_pair(0, v));                        //� ����������� ������ �������� ���������� ������ (����������, ����)

    while(!q.empty()){
        v = q.top().second;                         //��������� �������� ���� �� ������������� ������ (���� � ���-����� ����������)
        q.pop();

        for(int i=0; i<graph[v].size(); i++){       //��������� �������� �� ������
            int vertex = graph[v][i].first,
                dist = graph[v][i].second;
            if(d[vertex] > d[v]+dist){              //��� ���� ���� ������� ���������� �� ������������ �� ����� ����, �� ������������� ������ d � �������� ����� � ��������
                d[vertex] = d[v]+dist;
                q.push(make_pair(d[vertex], vertex));
            }
        }
    }
}


int main()
{
    cin>>n>>m;
    graph.resize(n+1);

    int v, u, w;
    for(int i=0; i<m; i++){
        cin>>v>>u>>w;
        graph[v].push_back(make_pair(u, w));
        graph[u].push_back(make_pair(v, w));
    }

    cin>>v;
    dijkstra(v);

    for(int i=1; i<=n; i++){
        cout<<(d[i]!=INF?d[i]:-1)<<" ";
    }
    cout<<endl;

    return 0;
}
