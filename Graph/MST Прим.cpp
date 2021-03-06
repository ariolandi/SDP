/**
MST (Min Spanning Tree) - ��������� (� ��������� ���� ����� �� �������) ��������� �����
��������� �� ����
����������:
* �������� �� ���-������ ����� � ����
* �������� �� bottleneck
* ������������ �� ����� �� ����
���������: MST ���� �� �� ������� ���� ����� ������� ����!
��������: O(N log(M))
������������ �� ����������: https://www.cs.usfca.edu/~galles/visualization/Prim.html
*/

#include<iostream>
#define INF 99999999
#define MAXN 1024
using namespace std;
int a[MAXN][MAXN], n, m;
int tree[MAXN], p[MAXN], depth[MAXN];
bool used[MAXN];

void prim(int root){
    used[root] = 1;                                              //������� � �������
    depth[root] = 0;                                             //����������� �� ������ � 0

    for(int i=1; i<=n; i++){                                     //�� ����� ���� ����������� ������� ����� ���� � ������
        tree[i] = a[root][i];
        p[i] = root;                                             //� �������� �� ������� ������
    }

    p[root] = 0;                                                 //������� �� ������ � 0
    tree[root] = INF;                                            //������� �� ������ �� ���� �� �� ����������
    int maxDist, j = 0;

    for(int l=0; l<n-1; l++){                                    //n-1 ���� �� ����� ������
        maxDist = 0, j = -1;                                     //������������ ������� � 0 � � ��� ������������� (-1) ����
        for(int i=1; i<=n; i++){                                 //�� ����� ����
            if (tree[i] > maxDist && !used[i]){                  //��� ��������� �� ������ � ��-������ �� ������������ � ��� � ���������
                maxDist = tree[i];                               //����������� ���� ����� �� ����������
                j = i;                                           //� ����������� ��� � �����
            }
        }
        used[j] = 1;                                           //��������� ��������� ���� � �������
        for(int i=1; i<=n; i++){                               //�� ����� ����
            if (tree[i] < a[j][i] && !used[i]){                //��� ���������� ��-������ ����� �� ����� �� ������� ������� � ��� �� � ���������
                tree[i] = a[j][i];                             //���������� ������� �� ������������ �����
                p[i] = j;                                      //� ������� �� �������� ����� ����� ������������
                depth[i] = depth[j]+1;                         //� ����������� �� - ���� �� �������������� +1
            }
        }
    }
    for(int l=0; l<n/2; l++)                                  //n/2 ����
        for(int i=1; i<=n; i++)                               //������������ ����������� �� �������
            depth[i] = depth[p[i]]+1;
}


main()
{
    int x, y, z;
    cin>>n>>m;
    for(int i=0; i<m; i++){                         //������ ���� � ������� �� �������
        cin>>x>>y>>z;
        a[x][y]=z;
        a[y][x]=z;
    }


    int root;                                     //���������� ������� ���� (����� �� �������)
    cin>>root;
    prim(root);

    for(int i=0; i<=n; i++){
        cout<<i<<"-> ";
        for(int j=0; j<=n; j++){
            if(p[j]==i)cout<<j<<" ";
        }
        cout<<endl;
    }


    return 0;
}


