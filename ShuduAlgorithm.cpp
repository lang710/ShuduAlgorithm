#include <iostream>
using namespace std;

void transpose(int graph[9][9]) {
    for (int i = 0; i < 8; i++)
        for (int j = i + 1; j < 9; j++)
            swap(graph[i][j], graph[j][i]);
}

bool finish(int graph[9][9]){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(graph[i][j]==0)
                return false;
    return true;
}

bool end(int graph[9][9],int graph1[9][9]){
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            if(graph[i][j]!=graph1[i][j])
                return false;
    return true;
}

void brute(int graph[9][9]){
    int visit[10];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++){
            if(graph[i][j]==0) {
                for (int k = 1; k < 10; k++)
                    visit[k] = 0;

                for(int m=0;m<9;m++)
                    if(graph[i][m]>0)
                        visit[graph[i][m]]=1;
                for(int m=0;m<9;m++)
                    if(graph[m][j]>0)
                        visit[graph[m][j]]=1;
                int m,n;
                for(m=(i/3)*3;m<(i/3)*3+3;m++)
                    for(n=(j/3)*3;n<(j/3)*3+3;n++)
                        if(graph[m][n]>0)
                            visit[graph[m][n]]=1;

                m=0;
                for(int k=1;k<10;k++){
                    m+=visit[k];
                    if(visit[k]==0)
                        n=k;
                }
                if(m==8)
                    graph[i][j]=n;
            }
        }
}

void candidateBrute(int graph[9][9]){

    int i,j,m,n,k,neighbor;
    int block1,block2,block3;
    bool jump;
    int unique,ux,uy;
    int tmp;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(graph[i][j]>0){
                block1=3*(i/3)+j/3;      //block(0,8)
                block2=3*(block1/3)+(block1+1)%3;
                block3=3*(block1/3)+(block1+2)%3;
                for(neighbor=0;neighbor<2;neighbor++) {
                    if(neighbor==0)
                        tmp=block2;
                    else
                        tmp=block3;
                    jump = false;
                    for (m = 3 * (tmp / 3); m < 3 * (tmp / 3) + 3; m++)
                        for (n = 3 * (tmp % 3); n < 3 * (tmp % 3) + 3; n++)
                            if (graph[m][n] == graph[i][j]) {
                                jump = true;
                                break;
                            }
                    if (!jump) {
                        unique = 0;
                        for (m = 3 * (tmp / 3); m < 3 * (tmp / 3) + 3 && unique <= 1; m++)
                            for (n = 3 * (tmp % 3); n < 3 * (tmp % 3) + 3 && unique <= 1; n++) {
                                jump = false;
                                if (m != i) {
                                    if (graph[m][n] == 0) {
                                        for (k = 0; k < 9; k++)
                                            if (graph[m][k] == graph[i][j]) {
                                                jump = true;
                                                break;
                                            }
                                        if (!jump)
                                            for (k = 0; k < 9; k++)
                                                if (graph[k][n] == graph[i][j]) {
                                                    jump = true;
                                                    break;
                                                }
                                        if (!jump) {
                                            unique++;
                                            if (unique <= 1)
                                                ux = m, uy = n;
                                        }
                                    }
                                }
                            }
                        if(unique==1)
                            graph[ux][uy]=graph[i][j];
                    }
                }
            }
        }
    }
}

void find(int graph[9][9]){
    int t_graph[9][9];
    while(true) {
        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                t_graph[i][j]=graph[i][j];

        candidateBrute(graph);
        transpose(graph);
        candidateBrute(graph);
        transpose(graph);
        brute(graph);
        if(finish(graph))
            break;
        if(end(graph,t_graph)) {
            break;
        }
    }
}

int main(){
    int graph[9][9];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            cin>>graph[i][j];

    find(graph);
    cout<<endl;
    for(int i=0;i<9;i++) {
        for (int j = 0; j < 9; j++)
            cout << graph[i][j]<<' ';
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

/*
input:九宫格-中等
1 3 0 8 0 0 6 0 0
0 0 2 0 0 7 0 0 0
0 0 0 1 2 0 0 7 9
2 8 0 0 0 0 0 0 0
0 9 0 0 3 0 0 1 0
0 0 0 0 0 0 0 2 3
5 7 0 0 8 3 0 0 0
0 0 0 4 0 0 9 0 0
0 0 9 0 0 2 0 6 7

output:
1 3 7 8 4 9 6 5 2
9 5 2 3 6 7 1 8 4
4 6 8 1 2 5 3 7 9
2 8 3 7 5 1 4 9 6
6 9 5 2 3 4 7 1 8
7 1 4 6 9 8 5 2 3
5 7 6 9 8 3 2 4 1
8 2 1 4 7 6 9 3 5
3 4 9 5 1 2 8 6 7

intput:九宫格-中等
0 5 0 4 0 0 0 7 0
8 0 0 0 0 5 1 0 0
0 0 9 8 3 0 0 5 0
1 0 8 0 0 0 0 0 0
2 4 0 0 0 0 0 6 1
0 0 0 0 0 0 3 0 2
0 1 0 0 7 8 6 0 0
0 0 6 3 0 0 0 0 7
0 9 0 0 0 4 0 8 0

output:
3 5 1 4 6 2 9 7 8
8 2 4 7 9 5 1 3 6
6 7 9 8 3 1 2 5 4
1 3 8 2 4 6 7 9 5
2 4 7 9 5 3 8 6 1
9 6 5 1 8 7 3 4 2
4 1 3 5 7 8 6 2 9
5 8 6 3 2 9 4 1 7
7 9 2 6 1 4 5 8 3
 */
