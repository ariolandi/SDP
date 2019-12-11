#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;
vector<int>component;

void BFS(int v, int cnt){                            //BFS ��������� � ������� ���� V
    queue<int> q;                                    //������ �� ������� �� ����������� �� ���������

    used[v] = true;                                  //����������� ����� �� ��������
    q.push(v);                                       //� �� �������� � ��������

    while(!q.empty()){                               //������ �������� �� � ������
        v = q.front();                               //��������� �������� ����
        q.pop();
        cout<<v<<" ";

        for(int i=0; i<graph[v].size(); i++){       //����������� ����� �� �������� �� ���� � ���� �������
            if(!used[graph[v][i]]){                 //��� �� �, �� �� ����������� ���� ����� � �������� � ��������
                used[graph[v][i]] = true;
                q.push(graph[v][i]);
            }
        }
        component[v] = cnt;                         //����������� ��� ��� ���������� ���������� �����
    }
}

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    used.resize(n+1);
    component.resize(n+1);

    int v, u;
    for(int i=0; i<m; i++){
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    int cnt = 0;
    for(int i=1; i<+n; i++){                         //��� ������� ��������� ����, �� �� ���� ������� ���� ����������
        if(!used[i]){
            cnt++;
            BFS(i, cnt);
            cout<<endl;
        }
    }


    return 0;
}

