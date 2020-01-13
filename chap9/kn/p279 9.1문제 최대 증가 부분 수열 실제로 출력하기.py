#!/usr/bin/env python
# coding: utf-8

# In[3]:


import numpy as np
problem1 = [4, 7, 6, 9, 8, 10]

#code 8.12
n = len(problem1)
cache = np.full(n + 1, -1, dtype='i').tolist();
S = problem1

def lis3(start):
    ret = cache[start + 1]

    if ret != -1:
        return ret
    
    ret = cache[start + 1] = 1
    for next in range(start+1, n):
        if start == -1 or S[start] < S[next]:
            ret = cache[start + 1] = max(ret, lis3(next) + 1)

    return ret

lis3(-1) - 1


# In[14]:


import numpy as np

#code 9.1
# S[start] 에서 시작하는 증가 부분 수열 중 최대 길이를 반환한다.
def lis4(start):
    ret = cache[start + 1]
    
    if ret != -1:
        return ret
    
    ret = 1 # 항상 S[start] 는 있기 떄문에 최하 길이는 1
    bestNext = -1
    
    for next in range(start + 1, n): # for (next = start + 1; next < n; next++)
        if start == -1 or S[start] < S[next]: # start 가 -1 이거나 현재 원소가 다음 원소보다 작은 경우만 참
            cand = lis4(next) + 1
            if cand > ret:
                ret = cache[start + 1] = cand
                bestNext = next
    
    choices[start + 1] = bestNext # 어떤 요소(=인덱스) 를 선택해야 lis 를 만족하는지를 저장함
    return ret

def reconstruct(start, seq):
    if start != -1:
        seq.append(S[start]) # choices[start] 의 내용을 배열에 추가. start 는 다음 라인에 의해 next 로 업데이트 됨

    next = choices[start+1]

    if next != -1:
        reconstruct(next, seq)


# In[16]:


problem1 = [4, 7, 6, 9, 8, 10]
cache = np.full(n + 1, -1, dtype='i').tolist();
choices = np.full(n + 1, -1, dtype='i').tolist();
S = problem1
n = len(problem1)

out = []
lis4(-1) - 1
reconstruct(-1, out)
problem1, out, choices


# In[19]:


problem1 = [1, 3, 4, 2, 4]
cache = np.full(n + 1, -1, dtype='i').tolist();
choices = np.full(n + 1, -1, dtype='i').tolist();
S = problem1
n = len(problem1)

out = []
lis4(-1) - 1
reconstruct(-1, out)
problem1, out, choices


# In[20]:


problem1 = [5, 6, 7, 1, 2]
cache = np.full(n + 1, -1, dtype='i').tolist();
choices = np.full(n + 1, -1, dtype='i').tolist();
S = problem1
n = len(problem1)

out = []
lis4(-1) - 1
reconstruct(-1, out)
problem1, out, choices

