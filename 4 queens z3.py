#2021SMCS001

from z3 import *

Q = [ Int(f'Queen {i+1}')for i in range(4) ]

#print(Q)
val = [ And(1 <= Q[i], Q[i] <= 4) for i in range(4) ]

#print(val)
column = [ Distinct(Q) ]

def abs(a):
    #absolute value in z3
    return If(a >= 0, a, -a)

diagonal = [ If(i == j,True,Q[i] - Q[j] != abs(i - j)) for i in range(4) for j in range(i) ]
#print(diagonal)

print("Here comes one arrangement")
solve(val + column + diagonal)