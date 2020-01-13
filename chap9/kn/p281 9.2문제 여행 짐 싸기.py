#!/usr/bin/env python
# coding: utf-8

# In[11]:


import numpy as np

# 캐리어의 용량이 capacity 만큼 남았을 때, item 이후의 물건들을 싸서 얻을 수 있는 최대 절박도의 합을 반환
def pack(capacity, item):
    if item == n:
        return 0
    
    ret = cache[capacity][item]
    if ret != -1:
        return ret
    
    # name[item] 을 담지 않을 경우
    ret = cache[capacity][item] = pack(capacity, item + 1)
    if capacity >= volume[item]: # name[item] 을 가져갈 캐리어의 용량이 남은 경우 참
        # name[item]을 담을 경우와 담지 않을 경우 중 절박도가 큰 값을 취함
        ret = cache[capacity][item] = max(ret, pack(capacity - volume[item], item + 1) + need[item])

    return ret

# pack(capcaity, item) 이 선택한 물건들의 목록을 picked 에 저장한다.
def reconstruct(capacity, item, picked):
    if item == n:
        return
    
    # item 을 선택하지 않아도 최대 절박도를 얻을 수 있으므로, 해당 item 은 skip한다.
    if pack(capacity, item) == pack(capacity, item + 1):
        reconstruct(capacity, item + 1, picked)
    else:
        picked.append(name[item])
        reconstruct(capacity - volume[item], item + 1, picked)

# problem 1
n = 6
w = 10
name = ['laptop', 'camera', 'xbox', 'grinder', 'dumbell', 'encyclopedia']
volume = [4, 2, 6, 4, 2, 10]
need = [7, 10, 6, 7, 5, 4]

cache = np.full((w + 1, n + 1), -1)
picked = []
reconstruct(w, 0, picked)
print('problem1', pack(w, 0), picked)

# problem 2
n = 6
w = 17
name = ['laptop', 'camera', 'xbox', 'grinder', 'dumbell', 'encyclopedia']
volume = [4, 2, 6, 4, 2, 10]
need = [7, 10, 6, 7, 5, 4]

cache = np.full((w + 1, n + 1), -1)
picked = []
reconstruct(w, 0, picked)
print('problem2', pack(w, 0), picked)

