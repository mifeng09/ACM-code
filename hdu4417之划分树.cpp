#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<queue>
#include<algorithm>
#include<map>
#include<iomanip>
#define INF 99999999
using namespace std;

const int MAX=100001;
int s[MAX],tree[20][MAX],sum[20][MAX];
int n,m;

void BuildTree(int deep,int left,int right){
	if(left == right)return;
	int mid=(left+right)>>1,ln=left,rn=mid+1,same=mid-left+1;
	for(int i=left;i<=mid;++i)if(s[i]<s[mid])--same;
	for(int i=left;i<=right;++i){
		sum[deep][i]=sum[deep][i-1];//[1,i]划分到左子树的个数
		if(tree[deep][i] == s[mid]){
			if(same){
				--same;
				++sum[deep][i];
				tree[deep+1][ln++]=tree[deep][i];
			}else tree[deep+1][rn++]=tree[deep][i];
		}
		else if(tree[deep][i] < s[mid]){
				++sum[deep][i];
				tree[deep+1][ln++]=tree[deep][i]; 
		}else tree[deep+1][rn++]=tree[deep][i];
	}
	BuildTree(deep+1,left,mid);
	BuildTree(deep+1,mid+1,right);
}

int Query(int deep,int left,int right,int L,int R,int k){
	if(left == right)return tree[deep][left];
	int mid=(left+right)>>1,s,ss;//s表示划分到[left,L)的左子树个数,ss....[L,R]...
	s=sum[deep][L-1]-sum[deep][left-1];
	ss=sum[deep][R]-sum[deep][L-1];
	if(k<=ss)return Query(deep+1,left,mid,left+s,left+s+ss-1,k);
	else return Query(deep+1,mid+1,right,mid+1+L-left-s,mid+1+R-left-s-ss,k-ss);
}

int main(){
	int L,R,H,t,T=1;
	cin>>t;
	while(t--){
	    cin>>n>>m;
		for(int i=1;i<=n;++i){
			scanf("%d",&s[i]);
			tree[0][i]=s[i];
		}
		sort(s+1,s+1+n);
		BuildTree(0,1,n);
		cout<<"Case "<<T++<<':'<<endl;
		for(int i=0;i<m;++i){
			scanf("%d%d%d",&L,&R,&H);
			++L,++R;
			int num=0,left=1,right=R-L+1,mid,temp;
			while(left<=right){
				mid=(left+right)>>1;
				temp=Query(0,1,n,L,R,mid);
				if(temp == H)num=max(num,mid);
				else if(temp<H)num=max(num,mid);
				else num=min(mid,num);
				if(temp>H)right=mid-1;
				else left=mid+1;
			}
			printf("%d\n",num);
		}
	}
	return 0;
}