#!/usr/bin/env python
# coding: utf-8

# In[2]:


def concat(lengths):
    pq = []
    for i in range(0, len(lengths)):
        pq.append(lengths[i])
    ret = 0
    while len(pq) > 1:
        pq.sort(reverse=True)
        min1 = pq.pop()
        min2 = pq.pop()
        pq.append(min1+min2)
        ret += min1 + min2
        
    return ret


print(concat([2, 2, 4]))
print(concat([3, 1, 3, 4, 1]))
print(concat([1, 1, 1, 1, 1, 1, 1, 2]))
        

