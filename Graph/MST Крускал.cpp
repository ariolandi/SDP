#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std;
vector<pair<int, pair<int, int> > >v;
int n, m, cost;
int p[1024];
vector<pair<int, int> >res;

int find_set(int a){                                                    //намира в кое множество се намира даден връх
    if(p[a]==a)return a;
    else return find_set(p[a]);
}

void union_sets(int a, int b){                                          //обединява две множества
    a=find_set(a);
    b=find_set(b);
    p[b]=a;
}

void kruskal(){
    int a, b, l;
    for(int i=0; i<m; i++){
        a=v[i].second.first;                                            //извличаме двата върха и дължината на реброто
        b=v[i].second.second;
        l=v[i].first;
        if(find_set(a)!=find_set(b)){                                   //ако не са в едно множество
            cost+=l;                                                    //добавяме дължината на реброто в общата цена
            union_sets(a, b);                                           //обединяваме множествата
            res.push_back(make_pair(a, b));                             //и добавяме реброто в минималното покриващо дърво
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
        p[x]=x;                                                         //създаваме си нови множества
        p[y]=y;
    }
    sort(v.begin(), v.end());                                           //сортираме графа
    //reverse(v.begin(), v.end());

    kruskal();                                                          //викаме крускал

    cout<<cost<<endl;
    for(int i=0; i<res.size(); i++) cout<<res[i].first<<res[i].second<<endl;


    return 0;
}

/*
Крайният резултат от този алгоритъм е списък на ребрата, определящи дървото.
Сложността на алгоритъма е O(m*log(m) + n*log(n)).
*/
