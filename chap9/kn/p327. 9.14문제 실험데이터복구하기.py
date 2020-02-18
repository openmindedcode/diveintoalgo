#!/usr/bin/env python
# coding: utf-8

# In[40]:


import numpy as np

MAX_N = 15

#code 9.18
def restore(last, used):
    if used == (1<<k) -1 :
        return 0
    
    ret = cache[last][used]
    if ret != -1 :
        return ret
    
    for next in range(0, k):
        if (used & (1 << next)) == 0:
            cand = overlap[last][next] + restore(next, used + (1 << next))
            ret = cache[last][used] = max(ret, cand);
    
    return ret

#code 9.19
def reconstruct(last, used):
    if used == (1<<k) - 1:
        return ""
    
    for next in range(0, k):
        if used & (1<<next):
            continue
        
        ifUsed = restore(next, used + (1<<next)) + overlap[last][next]
        
        if restore(last, used) == ifUsed:
            return (word[next][overlap[last][next]:] + reconstruct(next, used + (1<<next)))
        
    return "*******oops*******"

cache = np.full((MAX_N, 1<<MAX_N), -1)
overlap = np.full((MAX_N, MAX_N), 0)
word = ['geo', 'oji', 'jing']
overlap[0][0] = 3
overlap[0][1] = 1
overlap[0][2] = 1
overlap[1][0] = 1
overlap[1][1] = 3
overlap[1][2] = 2
overlap[2][0] = 1
overlap[2][1] = 2
overlap[2][2] = 4

k = len(word)
print('ret: ', reconstruct(0, 0))


cache = np.full((MAX_N, 1<<MAX_N), -1)
overlap = np.full((MAX_N, MAX_N), 0)
word = ['world', 'hello']
overlap[0][0] = 5
overlap[0][1] = 0
overlap[1][0] = 0
overlap[1][1] = 5

k = len(word)
print('ret: ', reconstruct(0, 0))


cache = np.full((MAX_N, 1<<MAX_N), -1)
overlap = np.full((MAX_N, MAX_N), 0)
word = ['abrac', 'cadabra', 'dabr']
overlap[0][0] = 5
overlap[0][1] = 4
overlap[0][2] = 3
overlap[1][0] = 4
overlap[1][1] = 7
overlap[1][2] = 4
overlap[2][0] = 3
overlap[2][1] = 4
overlap[2][2] = 4

k = len(word)
print('ret: ', reconstruct(0, 0))

