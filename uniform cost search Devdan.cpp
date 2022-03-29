#include<bits/stdc++.h>
using namespace std;

int main(){
int N;
int source;
int goal;
int flag = 0; //handling "goal not found" case
int flag1 = 0; //child is already in frontier or not

int count=0;

//graph adj list
cout<<"enter number of vertex\n";
cin>>N;
vector<pair<int,int> > adj[N+1]; //pair(node,cost)
int E,a,b,c;
cout<<"enter number of edges"<<endl;
cin>>E;
cout<<"enter node1 node2 and cost respectively"<<endl;
for(int i=1;i<=E;i++){
cin>>a>>b>>c;
adj[a].push_back({b,c});
adj[b].push_back({a,c});
}
cout<<"enter source node and goal node respectively\n";
cin>> source>>goal;



vector<int>visited(N+1,0); //initially not visited;
vector<pair<int,int> > frontier; //pair(cost,node)
vector<int>close;
//pq implementation
frontier.push_back({0,source});
visited[source]=1;


while(!frontier.empty()){
pair<int, int> front = frontier.back();
int a = -front.first; // cost
int b = front.second; // node


visited[b]=1;

//as we popping the lasst element we have to sort the array in descending order
frontier.pop_back();

//check if the front node is goal or not
if (b == goal) {
printf("goal found at node : %d",b);
//calculate cost
printf("\noptimal cost is: %d",a);
flag =1;
break;
}
//not goal
else{
//children of the front node
for (auto u: adj[b]){

int child_node = u.first;
int cost = u.second;
flag1=0; //child not in frontier

if(visited[child_node]==0){
	//the node is not visited

int new_cost = a+cost;

//check if the child node is in frontier list
for (int i=0;i<frontier.size();i++){
	
	if(child_node == frontier[i].second){
		flag1 =1; //child is in frontier
		if(-frontier[i].first > new_cost) {
			frontier[i].first =-new_cost;


		}
		
		break;
	}
}
if(flag1==0){//child is not in frontier
//push cost as negative so that we get a descending order arrangement
frontier.push_back({-new_cost,child_node});
sort(frontier.begin(),frontier.end());

}

}
}
}

}
//when frontier  list is empty but no goal state found
if(flag ==0)
printf("goal not found");
return 0;
}


/*OUTPUT 1 

enter number of vertex
6
enter number of edges
10
enter node1 node2 and cost respectively
1 2 9
1 3 4
2 3 2
2 4 7
4 5 4
3 5 6
2 5 3
3 4 1
4 6 8
5 6 2
enter source node and goal node respectively
1 6
goal found at node : 6
optimal cost is: 11
*/

/*OUTPUT 2

enter number of vertex
4
enter number of edges
4
enter node1 node2 and cost respectively
1 2 3
1 3 4
2 4 4
2 3 2
enter source node and goal node respectively
1 4
goal found at node : 4
optimal cost is: 7

*/