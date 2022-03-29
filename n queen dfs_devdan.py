

def safe( r,  c,board): 
    for i in range(c):
        #no two queen share the same row and two diagonal lines
        if(board[i]==r or abs(board[i]-r)==abs(i-c)):
            return False
       
    
    return True

#position of each queens are as(row, col)
def print_board(c):
    for i in c:
        print(f"({i},{c.index(i)})",end=' ')


def dfs(size):
    
    solutions =0
    board=[]


    row=0
    col=0

    while True:
        while row < size:
            #safe check for each row
            if (safe(row, col,board)):
                board.append(row)
                col+=1
                row=0
                break #if one safe row found continue to next col
            else:   
                row+=1
    
        #if could not find safe col or board is full
        if(col==size or row==size):
            #board is full
            if col==size:
                #print_board(board)
                #print()
                solutions+=1
            
            #board is empty
            if (len(board)==0):
                break
            prev_row = board.pop() #board is used as stack
            col-=1
            row = 1+prev_row

    print(f"no of solutions: {solutions}")      

dfs(size=int(input('enter size of the board: ')))
