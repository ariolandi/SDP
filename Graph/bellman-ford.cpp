/**
��������� �� ������-���� �� ���-��� ��� � ���� �� ����� ���� �� ������ ��������.
��������: O(N^3)
������������: https://visualgo.net/en/sssp
*/

#include<iostream>
#define INF 9999999
#define MAXN 1024
using namespace std;
int n, m, graph[MAXN][MAXN], dp[MAXN];

int main()
{
    cin>>n>>m;

    for(int i=1; i<=n; i++){                        //������������ ������������� �� �����
        for(int j=1; j<=n; j++)
            graph[i][j] = INF;
        graph[i][i] = 0;
    }

    int v, u, w;
    for(int i=0; i<m; i++){
        cin>>v>>u>>w;
        graph[v][u] = w;
        graph[u][v] = w;
    }

    cin>>v;
    for(int i=1; i<=n; i++){                     //������������ ������������� �� ������ �� ����������
        dp[i] = graph[v][i];
    }

    for(int k=0; k<n-2; k++){                   //��������� ���������� N-2 ����
        for(int i=1; i<=n; i++){                //����������� ���� ��� n�-������ ��� �� ���� I ���� ���� J � ��� ����� ����������, ������������� ������
            for(int j=1; j<=n; j++){
                if(dp[i] > dp[j]+graph[j][i])
                    dp[i] = dp[j]+graph[j][i];
            }
        }
    }

    for(int i=1; i<=n; i++){
        cout<<(dp[i]!=INF?dp[i]:-1)<<" ";
    }
    cout<<endl;


    return 0;
}
