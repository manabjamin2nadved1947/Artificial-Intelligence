import math
from queue import Queue
#input size
#size=4

#col=0



def safe(row, col,board):
    for i in range(col):
        #no two queen share the same row and two diagonal lines
        if (board[i]==row or abs(board[i]-row)==abs(i-col) ):
            return False
    return True

#position of each queens are as(row, col)
def print_board(c):
    for i in c:
        print(f"({i},{c.index(i)})",end=' ')

def bfs(size):
    q =  Queue()
    for i in range(size):
        q.put([i])
    board =[] #board[col]=row
    solutions =0

    while (not q.empty()) :
    
        c = q.get()
        #len(c)==size means we have a solution 
        if len(c)==size:
            #print_board(c)
            #print()
            solutions+=1
            continue
        #copy the current state on the board    
        board = c.copy()
    

    
        for i in range(size):
        
            #safe check for each row in next col
            if (safe(i, len(c),board)):
                #extend the board by placing the queen
                temp =[]
                temp.extend(board)
                #print(temp)
                temp.append(i)
                #enque the current state in the queue
                q.put(temp)
            
            
    print(f"no of solutions: {solutions}") 
    

bfs(size=int(input('enter size of the board: ')))

