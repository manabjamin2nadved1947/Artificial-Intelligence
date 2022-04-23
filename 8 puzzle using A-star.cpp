//8-puzzle problem using A* algorithm

// INPUT: initial and goal of 8-puzzle
//OUTPUT: optimal number of moves to reach initial to goal state and total number of moves

//f-score = g-score + h-score
//g-score = number of nodes traversed from source to current
//h-score = number of misplaced tiles (including the empty tile) 

// algorithm:
/*
1. enter the initial board config on the open list
2. while open list is not empty
	3. pop the node with minimum f-score ,call it a and check whether it is goal or not
		3.a. if goal return it and all chosen path
		3.b. else go to step 4.
	4. calculate all its(a's) children's f-score = g-score + h-score
	5. put them in the open-list
	6. push a into the closed list
*/

/*
Implementation details:

1.board config: 2d array [vector]

2.can we use priority queue? YEs; it takes tuple((board_config),f-score,g-score)
sorted on f-score

3. how to calculate g-score and h-score? h-score can be calaculated in O(n^2);
g-score == g-score of parent +1;

4. move the empty spaces in valid position

5. how to get the path? using parent vector which takes pair(parent_id , move_pos)



move e(i+1,j); move e(i-1,j); move e(i,j+1); move e(i,j-1);

*/


#include<bits/stdc++.h>

using namespace std;
typedef vector< vector <int> >vii;
typedef priority_queue < tuple<int, int,int, vii> >pq; //f-score, g-score, id, board_config
//typedef vector<int> vi;

int N=3;
//vii open;
vector<vii> closed;
vector< pair<int,char> > parent; 
int child_id=0;
int h_score(vii a, vii b){
  int h=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(a[i][j]!=b[i][j] && a[i][j]!=0)
        h++;
    }
  }
  return h;
}



bool check(vii a, vii b){
    for(int i = 0;i< N;i++){
    for(int j=0;j<N;j++){
      if(a[i][j]!=b[i][j])
        return false;
    }
  }
  return true;
}

void move(vii a,vii goal, int gs,int id, pq &q, int x, int y,int r,int c,char move){
  //int r,c;
  //search for empty-pos
  /*for(int i = 0;i< N;i++){
    for(int j=0;j<N;j++){
      if(a[i][j]==0)
        r=i, c=j, break;
    }
  }*/
 
 bool ch; 
  //move up index
  //int x = r-1, y=c;
  //check validity
  if((x>=0 && x<N) && (y>=0 && y<N) ){
    //prepare the state by swapping empty state and all
    vii temp(a);
    swap(temp[r][c],temp[x][y]);
    
    //testing
    /*for(int i = 0;i< N;i++){
    for(int j=0;j<N;j++){
      
        cout<<temp[i][j]<<" ";
    }
    cout<<endl;}*/


    //check whether the state is in closed list or not O(n^3)
    for(int i=0;i<closed.size();i++){
    	if(check(closed[i],temp)){
             ch = true;
             break;
         }
    }
         
     //cout<<ch<<" \n";       
    //if not in closed
    if(ch == false){
        //calculate f-score 
        int g_score = gs+1;
        int hs = h_score(temp,goal);
        int f_score = g_score+hs;
        child_id++ ;
        auto itpos = parent.begin()+child_id;
        parent.insert(itpos,{id,move});
        //push_back to q
        q.push({-f_score,g_score,child_id,temp});
        //cout<<"size"<<q.size()<<"\n";

    }
    
  }

}


int main(){
	vii init_board(N), goal(N);
	int input,id;
  	pq q;
  //init_board input
  	cout<<"enter initial board config\n";
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      //int input;
      cin>>input;
      init_board[i].push_back(input);
    }
  }
  //goal input
  cout<<"enter goal board config\n";
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      //int input;
      cin>>input;
      goal[i].push_back(input);
    }
  }
  cout<<"********moves to reach from initial to goal*******\n";

  int hs = h_score(init_board,goal);
  auto itpos = parent.begin();
  parent.insert(itpos,{0,'_'});
  //cout<<"yo";
  q.push({-hs,0,0,init_board}); //for source, hs=fs id=0 and  gs =0
  //cout<<"yo";
  while(!q.empty()){
  	//cout<<"enter in q\n";
    int fs = -get<0>(q.top()); //cout<<"fs in main "<<fs<<endl;
    int gs = get<1>(q.top());
    id = get<2>(q.top());
    vii current = get<3>(q.top());
    

    //testing 
    
    /*for(int i = 0;i< N;i++){
    for(int j=0;j<N;j++){
      
        cout<<current[i][j]<<" ";
    }
    cout<<endl;}*/
    
    //append current to closed list
    closed.push_back(current);
    //pop current
    q.pop();
    //cout<<"pop_size"<<q.size()<<endl;
    //check goal by h-score
    hs = fs-gs;
    	//cout<<"..........fs "<<fs<<endl;
    	//cout<<"..........gs "<<gs<<endl;
    	//cout<<"..........hs "<<hs<<endl;
    	//cout<<"****************************\n";
    if( hs == 0){
      //return path
      //cout<<"yo"<<endl;
      //return ;
    	
      //cout<<"closed list size "<<closed.size()<<"\n";
      //exit(0);
      break;
    }
    
    //if not goal
    
    //search for empty-pos
    int r,c;
    for(int i = 0;i< N;i++){
    for(int j=0;j<N;j++){
      if(current[i][j]==0){
          r=i; c=j; break;
      }
        
    }
  }
  
  //move up
  //cout<<"yo";
  move(current,goal,gs,id,q,r-1,c,r,c,'U');
  move(current,goal,gs,id,q,r+1,c,r,c,'D');
  move(current,goal,gs,id,q,r,c-1,r,c,'L');
  move(current,goal,gs,id,q,r,c+1,r,c,'R');
  
  }
  //print the parent vector
  /*for(int i=0;i<parent.size();i++){
    //cout<<"yo";
    cout<<parent[i]<<endl;
  }*/
  int i=id;
  vector<char> moves;
  while(parent[i].first!=i){
    //cout<<parent[i].second<<endl;
    moves.push_back(parent[i].second);
    i=parent[i].first;
  }
  for(int i=moves.size()-1;i>=0;i--)
    cout<<moves[i]<<endl;
  cout<<"total number of moves "<<moves.size()<<endl;
}
/*OUTPUT

enter initial board config
8 3 5
4 1 6
2 7 0
enter goal board config
1 2 3
8 0 4
7 6 5
********moves to reach from initial to goal*******
U
U
L
D
L
D
R
R
U
L
L
U
R
D
total number of moves 14

*/
