/**
Алгоритъм на Дийкстра за най-къс път в граф от даден връх до всички останали.
Приложим е върху:
* ориентиран граф без отрицателен цикъл
* неориентиран граф без отрицателни ребра
Сложност: O(M log(N))
Визуализация: https://www.cs.usfca.edu/~galles/visualization/Dijkstra.html
*/

#include<iostream>
#include<vector>
#include<queue>
#define INF 99999999999
using namespace std;
int n, m;
vector<vector<pair<int, int> > >graph;
vector<int>d;

void dijkstra(int v){                               //Dijkstra алгоригъм от връх V
    priority_queue<pair<int, int> >q;
    d.assign(n+1, INF);                             //първоначално инициализиране на масива d - нито един връх не е достъпен, освен началния с разстояние 0
    d[v] = 0;
    q.push(make_pair(0, v));                        //в приоритетна опашка добавяме наредената двойка (разстояние, връх)

    while(!q.empty()){
        v = q.top().second;                         //извличаме поредния връх от приоритетната опашка (този с най-малко разстояние)
        q.pop();

        for(int i=0; i<graph[v].size(); i++){       //обхождаме всичките му съседи
            int vertex = graph[v][i].first,
                dist = graph[v][i].second;
            if(d[vertex] > d[v]+dist){              //ако през него намерим подобрение на разстоянието до даден връх, то актуализираме масива d и добавяме върха в опашката
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
