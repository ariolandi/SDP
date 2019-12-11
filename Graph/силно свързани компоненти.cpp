/**
�����������:
����� �������� ���������� � ���������� ���� G(V, E) �������� ������ ������������ �� ������� V', ��
�� ����� ���� X �� V' � ����� ���� Y �� V' ����, �� ��� ��� ��� �� X �� Y, �� ������ � ���� ������
��� ��� �� Y �� X.
*/

#include <iostream>
#include<vector>
#define MAXN 128
using namespace std;
int n, m;
bool A[MAXN][MAXN];
bool used[MAXN];
int postnum[MAXN], cnt=0;

void DFS(int v){                                    //DFS ��������� �� ���� V
    used[v] = true;
    for(int i=1; i<=n; i++){
        if (!used[i] && A[v][i] == 1)
            DFS(i);
    }

    postnum[v] = cnt;                               //�������� ����� �� ���� V
    cnt++;
}

void backDFS(int v){                                //"�������" DFS ��������� �� ���� V
    cout<<v<<" ";
    cnt++;
    used[v] = true;
    for (int i=1; i<=n; i++){
        if(!used[i] && A[i][v] == 1)
            backDFS(i);
    }
}

void strongComponents(){                            //��������� �� �������� �� ����� ���������� ���������� � ����
    used.assign(n+1, 0);
    for(int i=0; i<n; i++){                          //��������� ����������� DFS ����� ����� ����
        if(!used[i])
            DFS(i);
    }

    used.assign(n+1, 0);                            //���������� ���������� ������� � ������
    cnt=0;
    while(count < n-1){                             //������ �� �������� ����� ����
        int max = -1, maxv = -1;
        for(int i=1; i<=n; i++){
            if(!used[i] && postnum[i] > max){       //�������� ��������� ���� � ���-������ ���������
                max = postnum[i];
                maxv = i;
            }
        }

        cout<<"{";
        backDFS(maxv);                              //�� ���� ������� ����� �������� ����������
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


