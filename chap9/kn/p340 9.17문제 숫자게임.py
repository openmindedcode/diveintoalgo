#!/usr/bin/env python
# coding: utf-8

# In[12]:


import numpy as np

# 게임은 현우 > 서우 순으로
# 점수 차이 (현우 - 서우) 값이 가장 큰 경우

EMPTY = -987654321;

def play(left, right):
    global sub
    if left > right:
        return 0
    
    ret = cache[left][right]
    if ret != EMPTY:
        return ret
    
    # 수를 하나 가져가는 경우
    ret = cache[left][right] = max(board[left] - play(left + 1, right),
                                   board[right] - play(left, right - 1))

    # 수를 2개 없애는 경우
    if right - left + 1 >= 2:
        ret = cache[left][right] = max(ret, -play(left + 2, right))
        ret = cache[left][right] = max(ret, -play(left, right - 2))
    
    return ret

cache = np.full((50,50), EMPTY)
board = [-1000, -1000, -3, -1000, -1000]
print(play(0, len(board) - 1)) # -1100

cache = np.full((50,50), EMPTY)
board = [100, -1000, -1000, 100, -1000, -1000]
print(play(0, len(board) - 1)) # 1100

cache = np.full((50,50), EMPTY)
board = [7, -5, 8, 5, 1, -4, -8, 6, 7, 9]
print(play(0, len(board) - 1)) # 7

