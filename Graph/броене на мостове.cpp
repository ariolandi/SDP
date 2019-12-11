/**
Следствие от определението за мост в граф:
ако едно ребро не е мост, то то участва в цикъл.
*/


#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int n, m, time;
vector<vector<int> >graph;
vector<bool>used;
vector<int>in, from;

void DFS(int v, int parent){                                     //DFS алгоритъм с връх V и родител на връх V
    used[v] = true;                                              //маркираме върха като обходен
    in[v] = from[v] = time;                                      //задаваме време на вход (и временно - стойност на from (в който се пази номера на цикъла на принадлежност))
    time++;
    for(int i=0; i<graph[v].size(); i++){                        //обхождаме всички съседи на върха
        int x = graph[v][i];
        if(x == parent)continue;                                //ако родителят и наследикът съвпадат, продължаваме със следващата операция
        if(used[x]){                                            //ако наследникът е обходен, то актуализираме номера на цикъла, към който принадлежи
            from[v] = min(in[v], from[x]);
        }
        else {                                                 //в противен случай, продължаваме с DFS от върха
            DFS(x, v);
            from[v] = min(from[v], from[x]);                   //отново минимизираме
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
