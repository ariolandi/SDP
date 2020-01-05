#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;
vector<int>component;

void BFS(int v, int cnt){                            //BFS алгоритъм с начален връх V
    queue<int> q;                                    //опашка за следене на поредността на обхождане

    used[v] = true;                                  //отбелязваме върха за обхожден
    q.push(v);                                       //и го добавяме в опашката

    while(!q.empty()){                               //докато опашката не е празна
        v = q.front();                               //извличаме поредния връх
        q.pop();
        cout<<v<<" ";

        for(int i=0; i<graph[v].size(); i++){       //проверяваме всеки от съседите му дали е вече обходен
            if(!used[graph[v][i]]){                 //ако не е, то го отбелязваме като такъв и добавяме в опашката
                used[graph[v][i]] = true;
                q.push(graph[v][i]);
            }
        }
        component[v] = cnt;                         //отбелязваме към коя компонента принадлежи върха
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
    for(int i=1; i<+n; i++){                         //ако намерим необходен връх, то от него започва нова компонента
        if(!used[i]){
            cnt++;
            BFS(i, cnt);
            cout<<endl;
        }
    }


    return 0;
}

