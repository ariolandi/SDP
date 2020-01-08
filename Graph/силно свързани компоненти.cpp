/**
Определение:
Силно свързана компонента в ориентиран граф G(V, E) наричаме такова подмножество от върхове V', че
за всеки връх X от V' и всеки връх Y от V' важи, че ако има път от X до Y, то тогава и само токава
има път от Y до X.
*/

#include <iostream>
#include<vector>
#define MAXN 128
using namespace std;
int n, m;
bool A[MAXN][MAXN];
bool used[MAXN];
int postnum[MAXN], cnt=0;

void DFS(int v){                                    //DFS алгоритъм от връх V
    used[v] = true;
    for(int i=1; i<=n; i++){
        if (!used[i] && A[v][i] == 1)
            DFS(i);
    }

    postnum[v] = cnt;                               //поредния номер на връх V
    cnt++;
}

void backDFS(int v){                                //"обърнат" DFS алгоригъм от връх V
    cout<<v<<" ";
    cnt++;
    used[v] = true;
    for (int i=1; i<=n; i++){
        if(!used[i] && A[i][v] == 1)
            backDFS(i);
    }
}

void strongComponents(){                            //алгоритъм за намиране на силно свързаните компоненти в граф
    used.assign(n+1, 0);
    for(int i=0; i<n; i++){                          //прилагаме алгоритъмът DFS върху целия граф
        if(!used[i])
            DFS(i);
    }

    used.assign(n+1, 0);                            //зануляваме посетените върхове и брояча
    cnt=0;
    while(count < n-1){                             //докато не обиколим целия граф
        int max = -1, maxv = -1;
        for(int i=1; i<=n; i++){
            if(!used[i] && postnum[i] > max){       //намираме необходен връх с най-голяма номерация
                max = postnum[i];
                maxv = i;
            }
        }

        cout<<"{";
        backDFS(maxv);                              //от него започва силно свързана компонента
        cout<<"}"<<endl;
    }
}

int main()
{
    cin>>n>>m;
    int v, u;
    for(int i=0; i<m; i++){
        cin>>v>>u;
        A[v][u] = 1;
    }

    strongComponents();

    return 0;
}


