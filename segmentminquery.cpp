#include <iostream>
#include <climits>
using namespace std;

	int query(int *tree,int ss,int se,int qs,int qe,int idx){
		//complete overlap
		if(qs<=ss && se<=qe){
			return tree[idx];
		}
		if(qe<ss || qs>se){
			return INT_MAX;
		}
		int mid=(ss+se)/2;
		int left=query(tree,ss,mid,qs,qe,2*idx);
		int right=query(tree,mid+1,se,qs,qe,2*idx+1);
		return min(left,right);

	}

void buildtree(int arr[],int *tree,int si,int ei,int idx){

	if(si==ei){
		tree[idx]=arr[si];
		return ;
	}
	int mid=(si+ei)/2;
	buildtree(arr,tree,si,mid,2*idx);
	buildtree(arr,tree,mid+1,ei,2*idx+1);
	tree[idx]=min(tree[2*idx],tree[2*idx+1]);
	return ;

}
void updateNode(int *tree,int si,int ei,int i,int inc,int idx){
	if(i>ei || i<si){
		return ;
	}
	if(si==ei){
		tree[idx]+=inc;
		return ;
	}

	int mid=(si+ei)/2;
	updateNode(tree,si,mid,i,inc,2*idx);
	updateNode(tree,mid+1,ei,i,inc,2*idx+1);
	tree[idx]=min(tree[2*idx],tree[2*idx+1]);
	return ;
}
void updateRange(int *tree,int si,int ei,int l,int r,int inc,int idx){
	if(l>ei || r<si){
		return ;
	}
	if(si==ei){
		tree[idx]+=inc;
		return ;
	}

	int mid=(si+ei)/2;
	updateRange(tree,si,mid,l,r,inc,2*idx);
	updateRange(tree,mid+1,ei,l,r,inc,2*idx+1);
	tree[idx]=min(tree[2*idx],tree[2*idx+1]);
	return ;
}

int main(){


	int arr[]={1,3,2,-5,6,4};
	int n=sizeof(arr)/sizeof(int);
	int *tree=new int[n*4+1];
	buildtree(arr,tree,0,n-1,1);
	for(int i=1;i<=13;i++){
		cout<<tree[i]<<" ";
	}
	cout<<endl;
	cout<<query(tree,0,n-1,4,5,1)<<endl;
	updateNode(tree,0,5,4,10,1);
	cout<<query(tree,0,n-1,4,4,1)<<endl;
	cout<<query(tree,0,n-1,5,5,1)<<endl;
	updateRange(tree,0,n-1,3,5,10,1);
	cout<<query(tree,0,n-1,4,4,1)<<endl;
	cout<<query(tree,0,n-1,5,5,1)<<endl;
	cout<<query(tree,0,n-1,0,5,1)<<endl;
	return 0;
}