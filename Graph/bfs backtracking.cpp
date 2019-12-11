#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;
vector<int>parent;

void printPathTo(int v){                            //������� �� ���������� �� ���� �� �������� ���� �� ���� V
    if(parent[v] == v){                             //��� ����� ���� � ������� ��� �� ���� ��, �� ��� � ��������
        cout<<v<<" ";
        return;
    }
    printPathTo(parent[v]);                         //���������� ���������� ���������������� � ������ - ����� ����
    cout<<v<<" ";
}

void BFS(int v){                                     //BFS ��������� � ������� ���� V
    queue<int> q;                                    //������ �� ������� �� ����������� �� ���������

    used[v] = true;                                  //����������� ����� �� ��������
    q.push(v);                                       //� �� �������� � ��������
    parent[v] = v;                                   //��������� ���� � ������� ��� �� ���� ��

    while(!q.empty()){                               //������ �������� �� � ������
        v = q.front();                               //��������� �������� ����
        q.pop();
        cout<<v<<" ";

        for(int i=0; i<graph[v].size(); i++){       //����������� ����� �� �������� �� ���� � ���� �������
            if(!used[graph[v][i]]){                 //��� �� �, �� �� ����������� ���� ����� � �������� � �������� � ����������� �������������� ��
                used[graph[v][i]] = true;
                q.push(graph[v][i]);
                parent[graph[v][i]] = v;
            }
        }

        cout<<"to "<<v<<": ";
        printPathTo(v);
        cout<<endl;
    }
}

int main()
{
    cin>>n>>m;
    graph.resize(n+1);
    used.resize(n+1);
    parent.resize(n+1);

    int v, u;
    for(int i=0; i<m; i++){
        cin>>v>>u;
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    cin>>v;
    BFS(v);


    return 0;
}
