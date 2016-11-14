/*优化分析： 
由于该正方形除了相邻之间不能选之外没有其他约束条件
所以每一行的状态以及状态数其实是一样的，所以就不用1~n行每次都求该行的状态以及状态数
只要求一边即可,然后把状态以及状态数保存好并且对于状态i,用邻接矩阵储存和状态i共存的状态
然后对于第k行第i个状态,只需要采用邻接表枚举和i共存的状态来求dp[k][i]即可 
*/
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
#include <iomanip>
#define INF 99999999
typedef long long LL;
using namespace std;

const int MAX=17711+10;
int n,nowsize,size;
int dp[MAX],temp[MAX],ans[MAX],now[MAX];
int w[22][22],head[MAX];

struct Edge{
	int v,next;
	Edge(){}
	Edge(int V,int NEXT):v(V),next(NEXT){}
}edge[3000000];

void Init(){
	memset(dp,0,sizeof dp);
	memset(temp,0,sizeof temp);
	memset(head,-1,sizeof head);
	size=nowsize=0;
}

void InsertEdge(int u,int v){
	edge[size]=Edge(v,head[u]);
	head[u]=size++;
}

void dfs(int k,int p){
	if(k>=n){now[++nowsize]=p;return;}
	dfs(k+2,p|(1<<k));
	dfs(k+1,p);
}

int cal(int k,int p){
	int sum=0;
	for(int i=0;i<20;++i){
		if(p & (1<<i))sum+=w[k][i];
	}
	return sum;
}

void DP(){
	dfs(0,0);
	for(int i=1;i<=nowsize;++i){//此处是优化,采用邻接表储存状态 
		for(int j=i+1;j<=nowsize;++j){
			if(now[i] & now[j])continue;
			InsertEdge(i,j);
			InsertEdge(j,i);
		}
	}
	for(int k=1;k<=n;++k){
		for(int i=1;i<=nowsize;++i){
			ans[i]=cal(k,now[i]);
			for(int j=head[i];j != -1;j=edge[j].next){
				dp[i]=max(dp[i],temp[edge[j].v]+ans[i]);
			}
		}
		for(int i=1;i<=nowsize;++i)temp[i]=dp[i],dp[i]=0;
	}
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;++i){
			for(int j=0;j<n;++j)scanf("%d",&w[i][j]);
		}
		Init();
		DP();
		int sum=0;
		for(int i=1;i<=nowsize;++i)sum=max(sum,temp[i]);
		printf("%d\n",sum);
	}
	return 0;
}
/*未优化的：
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
#include <iomanip>
#define INF 99999999
typedef long long LL;
using namespace std;

const int MAX=17711+10;
int n,nowsize,lastsize;
int now[MAX],last[MAX];
int dp[MAX],temp[MAX],ans[MAX];
int w[22][22];

void dfs(int id,int k,int p,int sum){
	if(k>=n){now[++nowsize]=p;ans[nowsize]=sum;return;}
	dfs(id,k+2,p|(1<<k),sum+w[id][k]);
	dfs(id,k+1,p,sum);
}

void DP(){
	for(int k=1;k<=n;++k){
		nowsize=0;
		dfs(k,0,0,0);
		for(int i=1;i<=nowsize;++i)dp[i]=0;
		for(int i=1;i<=nowsize;++i){
			for(int j=1;j<=lastsize;++j){
				if(now[i] & last[j])continue;
				dp[i]=max(dp[i],temp[j]+ans[i]);
			}
		}
		for(int i=1;i<=nowsize;++i)temp[i]=dp[i];
		for(int i=1;i<=nowsize;++i)last[i]=now[i];
		lastsize=nowsize;
	}
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;++i){
			for(int j=0;j<n;++j)scanf("%d",&w[i][j]);
		}
		temp[1]=last[1]=0;
		lastsize=1;
		DP();
		int sum=0;
		for(int i=1;i<=lastsize;++i)sum=max(sum,temp[i]);
		printf("%d\n",sum);
	}
	return 0;
} 
*/ 