#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int n, m;
vector<vector<int> >graph;
vector<bool>used;
vector<int>parent;

void printPathTo(int v){                            //функция за принтиране на пътя от началния връх до връх V
    if(parent[v] == v){                             //ако някой връх е родител сам на себе си, то той е началния
        cout<<v<<" ";
        return;
    }
    printPathTo(parent[v]);                         //рекурсивно принтираме предшествениците и накрая - самия връх
    cout<<v<<" ";
}

void BFS(int v){                                     //BFS алгоритъм с начален връх V
    queue<int> q;                                    //опашка за следене на поредността на обхождане

    used[v] = true;                                  //отбелязваме върха за обхожден
    q.push(v);                                       //и го добавяме в опашката
    parent[v] = v;                                   //началният връх е родител сам на себе си

    while(!q.empty()){                               //докато опашката не е празна
        v = q.front();                               //извличаме поредния връх
        q.pop();
        cout<<v<<" ";

        for(int i=0; i<graph[v].size(); i++){       //проверяваме всеки от съседите му дали е вече обходен
            if(!used[graph[v][i]]){                 //ако не е, то го отбелязваме като такъв и добавяме в опашката и отбелязваме предшественика му
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
