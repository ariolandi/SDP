/**
MST (Min Spanning Tree) - минимално (с минимално общо тегло на ребрата) покриващо дърво
Алгоритъм на Крускал
Приложения:
* намиране на най-леките ребра в граф
* намиране на bottleneck
* минимизиране на тегло на граф
Забележка: MST може да се приложи само върху свързан граф!
Сложност: O((N log(N)) + (N log(M)))
Визуализация на алгоритъма: https://www.cs.usfca.edu/~galles/visualization/Kruskal.html
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#define MAXN 1024
using namespace std;
int n, m, cost;
int p[MAXN];
vector<pair<int, int> >mst;
vector<pair<int, pair<int, int> > >v;

int find_set(int a){                                                    //намира в кое множество се намира даден връх
    if(p[a] == a)return a;
    else return p[a] = find_set(p[a]);
}

void union_sets(int a, int b){                                          //обединява две множества
    a = find_set(a);
    b = find_set(b);
    p[b] = a;
}

void kruskal(){                                                         //алгоригъм на Крускал
    int a, b, l;
    for(int i=0; i<m; i++){
        a = v[i].second.first;                                          //извличаме двата върха и дължината на реброто
        b = v[i].second.second;
        l = v[i].first;
        if(find_set(a) != find_set(b)){                                 //ако не са в едно множество
            cost += l;                                                  //добавяме дължината на реброто в общата цена
            union_sets(a, b);                                           //обединяваме множествата
            mst.push_back(make_pair(a, b));                             //и добавяме реброто в минималното покриващо дърво
        }
    }
}



int main ()
{
    cin>>n>>m;

    int x, y, z;
    for(int i=0; i<m; i++){
        cin>>x>>y>>z;
        v.push_back(make_pair(z, make_pair(x, y)));                     //създаваме си граф със списък на ребрата
        p[x] = x;                                                       //създаваме си нови множества за всички върхове
        p[y] = y;
    }
    sort(v.begin(), v.end());                                           //сортираме графа по теглото на ребрата в нарастващ ред

    kruskal();

    cout<<cost<<endl;
    for(int i=0; i<res.size(); i++)
        cout<<mst[i].first<<mst[i].second<<endl;


    return 0;
}

