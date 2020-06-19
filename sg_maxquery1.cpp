#include <iostream>
#include<climits>
using namespace std;
int count=0;


void query(int *tree,int ss,int se,int qs,int qe,int K,int idx){
	// no overlap
	if(qs>se || qe<ss){
		return ;
	}
	if(ss==se){
		if(tree[idx]>=K){
			count+=1;
			
		}
		return ;
	}
	int mid=(ss+se)/2;
	
	query(tree,ss,mid,qs,qe,K,2*idx);
	query(tree,mid+1,se,qs,qe,K,2*idx+1);
	return ;

}

void buildtree(int *tree,int arr[],int si,int ei,int idx){
if(si==ei){
	tree[idx]=arr[si];
	return ;
}
int mid=(si+ei)/2;
buildtree(tree,arr,si,mid,2*idx);
buildtree(tree,arr,mid+1,ei,2*idx+1);
tree[idx]=max(tree[2*idx],tree[2*idx+1]);
return ;
} 

int main(){
int n;
cin>>n;
int arr[n];
for(int i=0;i<n;i++){
	int x;
	cin>>x;
	arr[i]=x;
}
int *tree=new int[4*n+1];
buildtree(tree,arr,0,n-1,1);
int q;
cin>>q;
for(int i=1;i<=q;i++){
	int L,R,K;
	cin>>L>>R>>K;
	count=0;
	query(tree,0,n-1,L-1,R-1,K,1);
	cout<<count<<endl;

}
return 0;	
}
