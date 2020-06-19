#include <iostream>
#include<climits>
using namespace std;

int lazy[10000]={0};


void updatelazy(int *tree,int ss,int se,int l,int r,int inc,int idx){
	
	if(lazy[idx]!=0){
		tree[idx]+=lazy[idx];
		//condition for leaf node
		if(ss!=se){
			lazy[2*idx]+=lazy[idx];
			lazy[2*idx+1]+=lazy[idx];
		}
		lazy[idx]=0;
	}
	//no overlap
	if(r<ss || l>se){
		return ;
	}
	//complete overlap
	if(ss>=l && se<=r){
		tree[idx]+=inc;
		if(ss!=se){
			lazy[2*idx]+=inc;
			lazy[2*idx+1]+=inc;
		}
		return ;
	}
	// partial overlap
	int mid=(ss+se)/2;
	updatelazy(tree,ss,mid,l,r,inc,2*idx);
	updatelazy(tree,mid+1,se,l,r,inc,2*idx+1);
	tree[idx]=min(tree[2*idx],tree[2*idx+1]);
	return ;
}

int lazyquery(int *tree,int ss,int se,int qs,int qe,int idx){
	if(lazy[idx]!=0){
		tree[idx]+=lazy[idx];
		if(ss!=se){
			lazy[2*idx]+=lazy[idx];
			lazy[2*idx+1]=lazy[idx];
		}
		lazy[idx]=0;
	}
	//no overlap
	if(qe<ss || qs>se){
		return INT_MAX;
	}
	if(ss==se){
		return tree[idx];
	}
	int mid=(ss+se)/2;
	int left=lazyquery(tree,ss,mid,qs,qe,2*idx);
	int right=lazyquery(tree,mid+1,se,qs,qe,2*idx+1);
	return min(left,right);
}


void buildtree(int *tree,int arr[],int si,int ei,int idx){

	if(si==ei){
		tree[idx]=arr[si];
		return ;
	}
	int mid=(si+ei)/2;
	buildtree(tree,arr,si,mid,2*idx);
	buildtree(tree,arr,mid+1,ei,2*idx+1);
	tree[idx]=min(tree[2*idx],tree[2*idx+1]);
	return ;
}

int main(){

	int arr[]={1,3,2,-5,6,4};
	int n=sizeof(arr)/sizeof(int);
	int *tree=new int[4*n+1];
	buildtree(tree,arr,0,n-1,1);
	for(int i=1;i<=13;i++){
		cout<<tree[i]<<" ";
	}
	cout<<endl;
	updatelazy(tree,0,n-1,0,2,10,1);
	for(int i=1;i<=13;i++){
		cout<<tree[i]<<" ";
	}
	cout<<endl;
	cout<<lazyquery(tree,0,n-1,0,4,1)<<endl;

}