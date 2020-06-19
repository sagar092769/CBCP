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
void updateNode(int *tree,int si,int ei,int i,int inc,int idx){
	if(i>ei || i<si){
		return ;
	}
	if(si==ei){
		tree[idx]=inc;
		return ;
	}

	int mid=(si+ei)/2;
	updateNode(tree,si,mid,i,inc,2*idx);
	updateNode(tree,mid+1,ei,i,inc,2*idx+1);
	tree[idx]=min(tree[2*idx],tree[2*idx+1]);
	return ;
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

int main(){


int n,q;
cin>>n>>q;
int *tree=new int[4*n+1];

int arr[n];
for(int i=0;i<n;i++){
	cin>>arr[i];
}
buildtree(arr,tree,0,n-1,1);
while(q>0){
	int ip,l,r;
	cin>>ip>>l>>r;
	if(ip==1){
		cout<<query(tree,0,n-1,l-1,r-1,1)<<endl;
	}else{
		updateNode(tree,0,n-1,l-1,r,1);
	}

	q--;
}
return 0;
}