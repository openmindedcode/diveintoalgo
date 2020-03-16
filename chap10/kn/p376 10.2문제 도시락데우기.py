#!/usr/bin/env python
# coding: utf-8

# In[27]:



def heat():
    order = []
    
    for i in range(0, n):
        order.append([-e[i], i]); #problem1 - [[-2, 0], [-2, 1], [-2, 2]], problem2 - [[-1, 0], [-2, 1], [-1, 2]]
    
    ret = 0
    beginEat = 0
    order = sorted(order, key=lambda x:x[0]); #problem1 - [[-2, 0], [-2, 1], [-2, 2]], problem2 - [[-2, 1], [-1, 0], [-1, 2]]

    for i in range(0,n):
        box = order[i][1]
        beginEat += m[box];
        ret = max(ret, beginEat + e[box])
    
    return ret

n=3
m = [2, 2, 2]
e = [2, 2, 2]
print(heat())

n=3
m = [1, 2, 3]
e = [1, 2, 1]
print(heat())

