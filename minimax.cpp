#include<bits/stdc++.h>

using namespace std;

vector<int> parent;
vector<int> height;
int max_height, bf;

class node{
public:
	int idx;
	int value=0;
	//bool al_be = false;
	int alpha = -999;
	int beta = 999;
};

node root;
vector<node> *l;
int max_value(node &x);
int min_value(node &x);
int minimax_decision(node &x);
int terminal_test(node &x);
void optimal_play(node &x, int depth);
//alpha beta
int maxval(node &x, int &, int &);
int minval(node &x, int &, int &);
int alpha_beta_decision(node &x, int &, int &);
int internal_nodes, total_nodes, leaf_nodes;

void build_tree(int max_height, int bf){
	//calculate internal nodes
	int k =1;
	int a = pow(bf,max_height)-1;
	int b =pow(bf,max_height+1)-1;
	internal_nodes = a/(bf-1);
	total_nodes = b/(bf-1);
	leaf_nodes = total_nodes - internal_nodes;
	//cout<<internal_nodes<<endl;
	//cout<<total_nodes<<endl;
	height.resize(total_nodes);
	parent.resize(total_nodes);
	
	root.idx=0; parent[root.idx]=-1; height[root.idx]=0;
	l = (vector<node>*)malloc(internal_nodes * sizeof(vector<node>));
	
	
	//for internal nodes
	for(int i=0;i<internal_nodes;i++){
		for(int j=0;j<bf;j++){
			node n;
			n.idx = k; k++;
			parent[n.idx]=i;
			height[n.idx]=height[parent[n.idx]]+1;
			
			l[i].push_back(n);
		}
		//cout<<i<<" "<<height[i]<<endl;
	}
	//for external nodes
	int h = height[internal_nodes-1];
	int i= internal_nodes-1;
	srand( (unsigned)time( NULL ) );
	while(height[i]==h){
	    for(int j=0;j<l[i].size();j++){
	       node n = l[i][j];
	       n.value = rand()%100;
	       l[i][j].value = n.value;
	       //cout<<n.idx<<" "<<n.value<<" "<<height[n.idx]<<" "<<parent[n.idx]<< endl;
	    }
	    
	    i--;
	}

	
	
}
void print_tree(){
    //print tree
    cout<<"root index= "<< root.idx<<" ;root value= "<<root.value<<" ;root at height= "<<height[root.idx]<<" ;parent= "<<parent[root.idx]<<endl;
	for(int i=0;i<internal_nodes;i++){
		for(int j=0;j<l[i].size();j++){
			node n = l[i][j];
			cout<<"node index= "<< n.idx<<" ;node value= "<<n.value<<" ;node at height= "<<height[n.idx]<<" ;parent= "<<parent[n.idx]<<endl;
		}
	}
}


int max_value(node &x){
	if(terminal_test(x)){
	    //cout<<"max term "<<x.value<<endl;
	    
	    return x.value;
	}
		
	int v = -999;
	for (int j =0;j<l[x.idx].size();j++){
		v = max(v, min_value(l[x.idx][j]));
	}
	x.value = v;
	
	return v;
}

int min_value(node &x){
	if(terminal_test(x)){
	    //cout<<"min term "<<x.value<<endl;
	    
		return x.value;
	}
		
	int v = 999;
	for (int j =0;j<l[x.idx].size();j++){
		v = min(v, max_value(l[x.idx][j]));
		
	}
	x.value=v;
	
	return v;
}

int terminal_test(node &x){
	if(max_height == height[x.idx])
		return 1;
	else return 0;
}

int minimax_decision(node &x){
	int v = max_value(x);
	return v;
}

//alpha -beta pruning

int minval(node &x, int &alpha, int &beta){
    x.alpha=alpha; x.beta = beta;
	if(terminal_test(x))
		return x.value;
	int v=999;
	for(int j =0; j<l[x.idx].size();j++){
		int child = maxval(l[x.idx][j],x.alpha,x.beta);
		x.beta = min(x.beta,child);
		v = min(v,child);
		if(x.alpha >= x.beta) {
		    cout<<"alpha value = "<<x.alpha<<" beta value = "<<x.beta<<" pruned at "<<x.idx<<endl;
		    //x.value=v;
		    return child;
		}
	}
    
	//return best child(min)
	x.value=v;
	return v;
}

int maxval(node &x, int &alpha, int &beta){
    x.alpha=alpha; x.beta = beta;
	if(terminal_test(x))
		return x.value;
	int v= -999;
	for(int j=0;j<l[x.idx].size();j++){
		int child = minval(l[x.idx][j],x.alpha, x.beta);
		x.alpha = max(x.alpha,child);
		v = max(v, child);
		if(x.alpha >= x.beta) {
		    cout<<"alpha  value  = "<<x.alpha<<" beta value = "<<x.beta<<" pruned at "<<x.idx<<endl;
		    //x.value=v;
		    return child;
		}
	}

	//return best child(max)
	x.value=v;
	return v;
}
int alpha_beta_decision(node &x, int &alpha, int &beta){
	int v = maxval(x,alpha,beta);
	return v;
}


void optimal_play(node &x, int depth){
	if(depth == max_height){
		//cout<<"leaf-> "<<x.idx<<endl;
		return;
	}
	else{
		for(int j=0;j<l[x.idx].size();j++){
			if(l[x.idx][j].value == root.value){
				if(height[l[x.idx][j].idx]%2==0)
					cout<<"MAX-> "<< l[x.idx][j].idx<<endl;
				else cout<<"MIN-> "<<l[x.idx][j].idx<<endl;
				optimal_play(l[x.idx][j], depth+1);
				return;
			}
		}
	}
}

//no of nodes pruned
void pruned_count(){
	int sum=0;
	//for root node
	//root can never be zero, because every time beta value is infinity for root;
	//for each internal node except root
	//search for n.value=zero
	for(int i=0;i<internal_nodes;i++){
		for(int j=0;j<l[i].size();j++){
			if(l[i][j].value==0){
				//check whether max level or min level
				if(height[l[i][j].idx]%2==0){
					//max level->check for alpha value
					for(int k =0;k<l[l[i][j].idx].size();k++){
						//search for contributor of alpha value
						if(l[i][j].alpha==l[l[i][j].idx][k].value){
						    sum += (bf-k-1);
						    //cout << sum <<" "<<l[i][j].idx<< endl;
						    break;
						}
							
						
						
					}
				}
				
				if(height[l[i][j].idx]%2!=0){
					//min level-> check for beta value
					for(int k =0;k<l[l[i][j].idx].size();k++){
						//search for contributor of beta value
						if(l[i][j].beta==l[l[i][j].idx][k].value){
						    sum +=(bf-k-1);
						    //cout<<sum<<" "<<l[i][j].idx<<endl;
						    break;
						}
							
							
						//break;
					}
				}
			}
		}
	}

	cout<<" number of pruned node in alpha beta "<<sum<<endl;
}

int main(){
	
	cout<<"enter max height(root at 0 level) and branching factor\n";
	cin>>max_height>>bf;
	build_tree(max_height,bf);
	print_tree();
    cout<<endl;
    int x = minimax_decision(root);
	cout<<"minimax value at the root(minimax) "<<x<<endl;
	build_tree(max_height,bf);
	//print_tree();
	cout<<"\n";
	int y = alpha_beta_decision(root,root.alpha,root.beta);
	cout<<"minimax value at the root (alpha beta)"<< y <<"; alpha = "<<root.alpha<<"; beta= "<<root.beta<<endl;
	
	cout<<"Optimal path is ****\n";
	cout<<"MAX-> root\n"; optimal_play(root,height[root.idx]);
	/*for(int i=0;i<internal_nodes;i++){
		for(int j=0;j<l[i].size();j++){
			node n = l[i][j];
			cout<<n.idx<<" "<<n.value<<" "<<height[n.idx]<<" "<<parent[n.idx]<<" "<<n.alpha<<" "<<n.beta<<endl;
		}
	}*/
	cout<<"****\n";
	pruned_count();
	return 0;
	
}

/*OUTPUT
enter max height(root at 0 level) and branching factor
2 3
root index= 0 ;root value= 0 ;root at height= 0 ;parent= -1
node index= 1 ;node value= 0 ;node at height= 1 ;parent= 0
node index= 2 ;node value= 0 ;node at height= 1 ;parent= 0
node index= 3 ;node value= 0 ;node at height= 1 ;parent= 0
node index= 4 ;node value= 95 ;node at height= 2 ;parent= 1
node index= 5 ;node value= 59 ;node at height= 2 ;parent= 1
node index= 6 ;node value= 56 ;node at height= 2 ;parent= 1
node index= 7 ;node value= 93 ;node at height= 2 ;parent= 2
node index= 8 ;node value= 12 ;node at height= 2 ;parent= 2
node index= 9 ;node value= 73 ;node at height= 2 ;parent= 2
node index= 10 ;node value= 21 ;node at height= 2 ;parent= 3
node index= 11 ;node value= 65 ;node at height= 2 ;parent= 3
node index= 12 ;node value= 3 ;node at height= 2 ;parent= 3

minimax value at the root(minimax) 56

alpha value pruned= 56 beta value pruned= 12 at 2
alpha value pruned= 56 beta value pruned= 21 at 3
minimax value at the root (alpha beta)56; alpha = 56; beta= 999
Optimal path is ****
MAX-> root
MIN-> 1
MAX-> 6
****
 number of pruned node in alpha beta 3
 */



/*OUTPUT
enter max height(root at 0 level) and branching factor
2 3
root index= 0 ;root value= 0 ;root at height= 0 ;parent= -1
node index= 1 ;node value= 0 ;node at height= 1 ;parent= 0
node index= 2 ;node value= 0 ;node at height= 1 ;parent= 0
node index= 3 ;node value= 0 ;node at height= 1 ;parent= 0
node index= 4 ;node value= 89 ;node at height= 2 ;parent= 1
node index= 5 ;node value= 83 ;node at height= 2 ;parent= 1
node index= 6 ;node value= 60 ;node at height= 2 ;parent= 1
node index= 7 ;node value= 34 ;node at height= 2 ;parent= 2
node index= 8 ;node value= 86 ;node at height= 2 ;parent= 2
node index= 9 ;node value= 21 ;node at height= 2 ;parent= 2
node index= 10 ;node value= 39 ;node at height= 2 ;parent= 3
node index= 11 ;node value= 10 ;node at height= 2 ;parent= 3
node index= 12 ;node value= 16 ;node at height= 2 ;parent= 3

minimax value at the root(minimax) 60

alpha value = 60 beta value = 34 pruned at 2
alpha value = 60 beta value = 39 pruned at 3
minimax value at the root (alpha beta)60; alpha = 60; beta= 999
Optimal path is ****
MAX-> root
MIN-> 1
MAX-> 6
****
 number of pruned node in alpha beta 4
 */

