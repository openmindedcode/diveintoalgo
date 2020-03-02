#!/usr/bin/env python
# coding: utf-8

# In[9]:


import numpy as np

moves = []
def cell(y, x):
    return 1 << (y*5+x)

def precalc() :
    for y in range(0,4):
        for x in range(0,4):
            cells = []
            for dy in range(0, 2):
                for dx in range(0, 2):
                    cells.append(cell(y + dy, x + dx))
            square = cells[0] + cells[1] + cells[2] + cells[3]
            for i in range(0,4):
                moves.append(square - cells[i])
    
    for i in range(0,5):
        for j in range(0,4):
            moves.append(cell(i, j) + cell(i, j+1))
            moves.append(cell(j, i) + cell(j+1, i))

def play (board):
    ret = cache[board]
    if ret != -1:
        return ret
    
    ret = 0
    
    for i in range(0, len(moves)):
        if moves[i] & board == 0:
            if not play(board | moves[i]):
                ret = cache[board] = 1
                break

    return ret

precalc()

input1 = [
    ['.', '.', '.', '.', '.'],
    ['.', '#', '#', '.', '.'],
    ['#', '#', '.', '.', '#'],
    ['#', '.', '#', '#', '#'],
    ['.', '.', '#', '.', '.']
]

board = 0
for y in range(0, len(input1)):
    for x in range(0, len(input1[y])):
        if input1[y][x] == '#':
            board += cell(y, x)

cache = np.full(1<<25, -1)
print(play(board))


input1 = [
    ['.', '.', '.', '.', '.'],
    ['.', '.', '.', '.', '.'],
    ['.', '.', '.', '.', '.'],
    ['.', '.', '.', '.', '.'],
    ['.', '.', '.', '.', '.']
]

board = 0
for y in range(0, len(input1)):
    for x in range(0, len(input1[y])):
        if input1[y][x] == '#':
            board += cell(y, x)

cache = np.full(1<<25, -1)
print(play(board))


input1 = [
    ['#', '.', '.', '#', '#'],
    ['#', '#', '.', '#', '#'],
    ['#', '#', '.', '#', '#'],
    ['#', '.', '.', '.', '#'],
    ['#', '#', '.', '#', '#']
]

board = 0
for y in range(0, len(input1)):
    for x in range(0, len(input1[y])):
        if input1[y][x] == '#':
            board += cell(y, x)

cache = np.full(1<<25, -1)
print(play(board))

