/************匈牙利算法**************/
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
#define MAX_N 512
vector<int>Adj[MAX_N];
int n,m,ans;
void AddEdge(int u,int v){
    Adj[u].push_back(v);
    Adj[v].push_back(u);
}
/**********读入数据，建图*************/
void Init(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int si,k;
        scanf("%d",&si);
        for(int j=1;j<=si;j++){
            scanf("%d",&k);
            k+=n;
            AddEdge(i,k);
        }
    }
}
/************深搜找增广路************/
bool Vis[MAX_N+1];
int Match[MAX_N+1];
bool Dfs(int u){
    for(int i=0;i<Adj[u].size();i++){
        int v=Adj[u][i];
        if(Vis[v])  
            continue;
        Vis[v]=true;
        if(!Match[v]||Dfs(Match[v])){
            Match[v]=u;
            Match[u]=v;
            return true;
        }
    }
    return false;
}
/*********匈牙利算法主函数**********/
void Solve(){
    for(int i=1;i<=n;i++){
        memset(Vis,false,sizeof Vis);
        if(!Match[i])
            if(Dfs(i))
                ans++;
    }
}
int main(){
    Init();
    Solve();
    printf("%d\n",ans);
}