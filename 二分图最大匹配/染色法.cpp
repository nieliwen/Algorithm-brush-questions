#include<bits/stdc++.h>
using namespace std;
const int MAX_LEN=1000;
bool Graph[MAX_LEN][MAX_LEN];//图的邻接矩阵
int n;//n个顶点
int m;//m条边
int color[MAX_LEN];//记录颜色
bool flag=true;//记录状态,是否为二分图。

void bfs(int cur){
    queue<int> qlist;
    qlist.push(cur);
    color[cur]=1;
    while(!qlist.empty()){
        int u=qlist.front();
        qlist.pop();
        for(int i=1;i<=n;i++){
            if(Graph[u][i]){
                if(color[i]==0){
                    color[i]=-1*color[u];
                    qlist.push(i);
                }
                else if(color[i]==color[u]){
                    flag=false;
                    return ;
                }
            }
        }
    }
}
int main(){
    cin>>n>>m;
    memset(Graph,false,sizeof(Graph));
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        Graph[u][v]=true;
        Graph[v][u]=true;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout<<Graph[i][j]<<" ";
        }
        cout<<endl;
    }
    memset(color,0,sizeof(color));
    for(int i=1;i<=n;i++){
        if(color[i]==0) 
            if(flag) 
                bfs(i);
    }
    cout<<flag<<endl;
}