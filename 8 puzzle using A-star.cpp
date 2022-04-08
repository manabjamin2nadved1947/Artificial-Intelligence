//8-puzzle problem using A* algorithm

//requirements
//open list
//closed list

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

5. how to get the path? using closed list



move e(i+1,j); move e(i-1,j); move e(i,j+1); move e(i,j-1);

move_e(int r, int c){
	//check if (r,c) is valid or not
	if((r>=0 && r<sqrt(n+1)) && (c>=0 && c< sqrt(n+1)) ){
		//check whether the state is in closed list or not;
		//if not calculate f-score; 
		//push the state in pq;
	}
}

*/


#include<bits/stdc++.h>

using namespace std;
typedef vector< vector <int> >vii;
typedef priority_queue < tuple<int, int,vii> >pq; //f-score, g-score, board_config


int N=3;
//vii open;
vector<vii> closed;

int h_score(vii a, vii b){
  int h=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      if(a[i][j]!=b[i][j])
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

void move(vii a,vii goal, int gs, pq &q, int x, int y,int r,int c){
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
        //push_back to q
        q.push({-f_score,g_score,temp});
        //cout<<"size"<<q.size()<<"\n";

    }
    
  }

}


int main(){
	vii init_board(N), goal(N);
	int input;
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
  q.push({-hs,0,init_board}); //for source, hs=fs and gs =0
  
  while(!q.empty()){
  	//cout<<"enter in q\n";
    int fs = -get<0>(q.top()); //cout<<"fs in main "<<fs<<endl;
    int gs = get<1>(q.top());
    vii current = get<2>(q.top());
    

    //testing 
    for(int i = 0;i< N;i++){
    for(int j=0;j<N;j++){
      
        cout<<current[i][j]<<" ";
    }
    cout<<endl;}
    
    //append current to closed list
    closed.push_back(current);
    //pop current
    q.pop();
    //cout<<"pop_size"<<q.size()<<endl;
    //check goal by h-score
    hs = fs-gs;
    	cout<<"..........fs "<<fs<<endl;
    	cout<<"..........gs "<<gs<<endl;
    	cout<<"..........hs "<<hs<<endl;
    	cout<<"****************************\n";
    if( hs == 0){
      //return path
      //cout<<"yo"<<endl;
      //return ;
    	
      cout<<"closed list size "<<closed.size()<<"\n";
      exit(0);
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
  move(current,goal,gs,q,r-1,c,r,c);
  move(current,goal,gs,q,r+1,c,r,c);
  move(current,goal,gs,q,r,c-1,r,c);
  move(current,goal,gs,q,r,c+1,r,c);
    
  }
	
}
/*OUTPUT

enter initial board config
1 2 3
8 0 4
7 6 5
enter goal board config
2 8 1
0 4 3
7 6 5
********moves to reach from initial to goal*******
1 2 3
8 0 4
7 6 5
..........fs 6
..........gs 0
..........hs 6
****************************
1 2 3
8 4 0
7 6 5
..........fs 6
..........gs 1
..........hs 5
****************************
1 2 0
8 4 3
7 6 5
..........fs 6
..........gs 2
..........hs 4
****************************
1 2 3
0 8 4
7 6 5
..........fs 6
..........gs 1
..........hs 5
****************************
1 0 2
8 4 3
7 6 5
..........fs 7
..........gs 3
..........hs 4
****************************
1 0 3
8 2 4
7 6 5
..........fs 7
..........gs 1
..........hs 6
****************************
0 1 2
8 4 3
7 6 5
..........fs 8
..........gs 4
..........hs 4
****************************
8 1 2
0 4 3
7 6 5
..........fs 8
..........gs 5
..........hs 3
****************************
1 3 0
8 2 4
7 6 5
..........fs 8
..........gs 2
..........hs 6
****************************
1 2 3
8 4 5
7 6 0
..........fs 8
..........gs 2
..........hs 6
****************************
0 2 3
1 8 4
7 6 5
..........fs 8
..........gs 2
..........hs 6
****************************
2 0 3
1 8 4
7 6 5
..........fs 8
..........gs 3
..........hs 5
****************************
2 8 3
1 0 4
7 6 5
..........fs 8
..........gs 4
..........hs 4
****************************
2 8 3
1 4 0
7 6 5
..........fs 8
..........gs 5
..........hs 3
****************************
2 8 0
1 4 3
7 6 5
..........fs 8
..........gs 6
..........hs 2
****************************
2 8 3
0 1 4
7 6 5
..........fs 8
..........gs 5
..........hs 3
****************************
0 1 3
8 2 4
7 6 5
..........fs 8
..........gs 2
..........hs 6
****************************
8 1 3
0 2 4
7 6 5
..........fs 8
..........gs 3
..........hs 5
****************************
1 2 3
8 6 4
7 0 5
..........fs 8
..........gs 1
..........hs 7
****************************
2 3 0
1 8 4
7 6 5
..........fs 9
..........gs 4
..........hs 5
****************************
1 4 2
8 0 3
7 6 5
..........fs 9
..........gs 4
..........hs 5
****************************
1 4 2
0 8 3
7 6 5
..........fs 9
..........gs 5
..........hs 4
****************************
1 3 4
8 2 0
7 6 5
..........fs 9
..........gs 3
..........hs 6
****************************
1 2 3
7 8 4
0 6 5
..........fs 9
..........gs 2
..........hs 7
****************************
2 0 8
1 4 3
7 6 5
..........fs 10
..........gs 7
..........hs 3
****************************
2 8 3
1 4 5
7 6 0
..........fs 10
..........gs 6
..........hs 4
****************************
2 8 3
1 6 4
7 0 5
..........fs 10
..........gs 5
..........hs 5
****************************
2 3 4
1 8 0
7 6 5
..........fs 10
..........gs 5
..........hs 5
****************************
8 1 3
2 0 4
7 6 5
..........fs 10
..........gs 4
..........hs 6
****************************
8 1 3
2 4 0
7 6 5
..........fs 10
..........gs 5
..........hs 5
****************************
8 1 0
2 4 3
7 6 5
..........fs 10
..........gs 6
..........hs 4
****************************
8 0 1
2 4 3
7 6 5
..........fs 10
..........gs 7
..........hs 3
****************************
0 8 1
2 4 3
7 6 5
..........fs 10
..........gs 8
..........hs 2
****************************
2 8 1
0 4 3
7 6 5
..........fs 9
..........gs 9
..........hs 0
****************************
closed list size 34

*/
