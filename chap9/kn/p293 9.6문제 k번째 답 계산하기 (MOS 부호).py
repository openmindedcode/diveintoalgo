#!/usr/bin/env python
# coding: utf-8

# In[4]:


#code 9.6

# n개의 긴 신호(-) 와 m개의 짧은 신호(o) 를 사전순으로 출력하는 함수
def generate(n, m, s):
    if n == 0 and m == 0:
        print(s)
        return;

    if n > 0:
        generate(n-1, m, s+'-')
    if m > 0:
        generate(n, m-1, s+'o')
        
generate (2,2,'')


# In[11]:


#code 9.7 skip 번째 mos 부호 출력

def generate2(n, m, s):
    global skip # 전역변수 선언하지 않으면 skip -= 1 에서 local 변수 referenced before assignment 에러 발생

    if skip < 0:
        return
    
    if n == 0 and m == 0:
        if skip == 0:
            print(s)
        
        skip -= 1
        return

    if n > 0:
        generate2(n-1, m, s+'-')
    if m > 0:
        generate2(n, m-1, s+'o')
        
skip = 2
generate2 (2,2,'')


# In[16]:


#code 9.8 k-1개 건너뛰고 첫 번째 신호를 출력하는 프로그램
import numpy as np

M = 1000000000 + 100
bino = np.full((201,201), 0)

def calcBino():
    for i in range (0, 201):
        bino[i][0] = bino[i][i] = 1
        for j in range (1, 201):
            bino[i][j] = min(M, bino[i-1][j-1] + bino[i-1][j])
            
def generate3(n, m, s):
    global skip
    
    if skip < 0:
        return
    
    if n == 0 and m == 0:
        if skip == 0:
            print(s)
        
        skip -= 1
        return
    
    if bino[n+m][n] <= skip:
        skip -= bino[n+m][n]
        return
    
    if n > 0:
        generate2(n-1, m, s+'-')
    if m > 0:
        generate2(n, m-1, s+'o')
        
    
skip = 2
calcBino()
generate3(2, 2, '')


# In[19]:


#code 9.9 k번째 신호를 계산하는 알고리즘
import numpy as np

M = 1000000000 + 100
bino = np.full((201,201), 0)

def calcBino():
    for i in range (0, 201):
        bino[i][0] = bino[i][i] = 1
        for j in range (1, 201):
            bino[i][j] = min(M, bino[i-1][j-1] + bino[i-1][j])
            
def kth(n, m, skip):
    if n == 0:
        return 'o' * m
    
    if skip < bino[n+m-1][n-1]:
        return '-' + kth(n-1, m, skip)
    return 'o' + kth(n, m-1, skip - bino[n+m-1][n-1])

calcBino()
kth(2, 2, 2)


# In[46]:


MAX = 2000000000 + 1

def lis(start):
    ret = cacheLen[start + 1]
    if ret != -1:
        return ret
    ret = 1
    for next in range(start+1, n):
        if start == -1 or S[start] < S[next]:
            ret = cacheLen[start + 1] = max(ret, lis(next) + 1)
            
    return ret

def count(start):
    if lis(start) == 1:
        return 1
    
    ret = cacheCnt[start+1]
    if ret != -1:
        return ret
    
    ret = 0
    for next in range(start+1, n):
        if (start == -1 or S[start] < S[next]) and lis(start) == lis(next) + 1:
            ret = cacheCnt[start+1] = min(MAX, ret + count(next))
            
    return ret

#code 8.12
def lis3(start):
    ret = cache[start + 1]

    if ret != -1:
        return ret
    
    ret = cache[start + 1] = 1
    for next in range(start+1, n):
        if start == -1 or S[start] < S[next]:
            ret = cache[start + 1] = max(ret, lis3(next) + 1)

    return ret

# code 9.11
def reconstruct(start, skip, lis):
    if start != -1:
        lis.append(S[start])
    
    followers = []
    for next in range(start + 1, n):
        if (start == -1 or S[start] < S[next]) and lis3(start) == lis3(next) + 1:
            followers.append([S[next], next])
            
    followers.sort()
    
    for i in range(0, len(followers)):
        idx = followers[i][1]
        cnt = count(idx)
        if cnt <= skip:
            skip -= cnt
        else:
            reconstruct(idx, skip, lis)
            break;
            
    return lis

S = [5, 1, 6, 4, 3, 2, 8, 7]
n = len(S)
k = 6
cacheLen = np.full(501, -1)
cacheCnt = np.full(501, -1)
cache = np.full(n + 1, -1)
print(lis(0), count(-1), reconstruct(-1, k - 1, []))


S = [2, 1, 4, 3, 6, 5, 8, 7]
n = len(S)
k = 4
cacheLen = np.full(501, -1)
cacheCnt = np.full(501, -1)
cache = np.full(n + 1, -1)
print(lis(0), count(-1), reconstruct(-1, k - 1, []))


S = [5, 6, 7, 8, 1, 2, 3, 4]
n = len(S)
k = 2
cacheLen = np.full(501, -1)
cacheCnt = np.full(501, -1)
cache = np.full(n + 1, -1)
print(lis(0), count(-1), reconstruct(-1, k - 1, []))

