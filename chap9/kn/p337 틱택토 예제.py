#!/usr/bin/env python
# coding: utf-8

# In[18]:


import numpy as np
def isFinished(board, turn):
    if (board[0][0] == board[0][1] == board[0][2] == turn) or         (board[1][0] == board[1][1] == board[1][2] == turn) or         (board[2][0] == board[2][1] == board[2][2] == turn) or         (board[0][0] == board[1][0] == board[2][0] == turn) or         (board[0][1] == board[1][1] == board[2][2] == turn) or         (board[0][2] == board[1][2] == board[2][2] == turn) or         (board[0][0] == board[1][1] == board[2][2] == turn) or         (board[2][0] == board[1][1] == board[0][2] == turn):
        return True
    return False;

def bijection(board): #3^9 개의 경우의 수가 있을 수 있음. 각 경우에 해당하는 cache index를 반환
    ret = 0
    for y in range(0, 3):
        for x in range(0, 3):
            ret = ret * 3
            if board[y][x] == 'o': # o = 111
                ret += 1
            elif board[y][x] == 'x': # x = 120
                ret += 2

    return ret

def canWin(board, turn):
    if isFinished(board, chr(ord('o') + ord('x') - ord(turn))): # 상대turn 이 이긴 경우, 내가 졌으므로 -1 리턴
        return -1
    
    ret = cache[bijection(board)]
    if ret != -2:
        return ret
    
    minValue = 2
    for y in range(0, 3):
        for x in range(0, 3):
            if board[y][x] == '.':
                board[y][x] = turn
                minValue = min(minValue, canWin(board, chr(ord('o') + ord('x') - ord(turn))))
                board[y][x] = '.'
                
    if minValue == 2 or minValue == 0:
        ret = cache[bijection(board)] = 0
        return ret
    
    ret = cache[bijection(board)] = -minValue
    return ret

board = np.full((3,3), '.')
cache = np.full(19683, -2)
board[0][0] = 'o'
board[1][0] = 'o'
board[2][2] = 'x'
board[1][1] = 'x'
canWin(board, 'x')

