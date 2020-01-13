#!/usr/bin/env python
# coding: utf-8

# In[23]:


import numpy as np

# code 9.4
# P(R|Q) = 원문이 Q일 때 분류기가 R을 반환할 확률
# P(Q) = 원문이 출현할 확률
# f(Q) = P(R|Q) * P(Q) 의 최대값을 구하는 함수
# Q[segment - 1] 이후를 채워서 얻을 수 있는 최대 g() 곱의 로그 값을 반환함
def recognize(segment, previousMatch):
    if segment == n:
        return 0
    
    ret = cache[segment][previousMatch]
    if ret != 1.0:
        return ret

    ret = cache[segment][previousMatch] = -0.0000000000000000000001
    choose = choice[segment][previousMatch]
    
    # R[segment] 에 대응하는 단어를 찾음
    for thisMatch in range(0, m):
        # g(thisMatch) = T(previousMatch, thisMatch) * M(thisMatch, R[segment])
        cand = T[previousMatch][thisMatch] + M[thisMatch][R[segment]] + recognize(segment + 1, thisMatch)
        
        if ret < cand:
            ret = cache[segment][previousMatch] = cand
            choose = choice[segment][previousMatch] = thisMatch
    
    return ret

# code 9.5
# 입력받은 단어들의 목록 corpus 에서 광학 문자 인식 문제의 답 계산
def reconstruct(segment, previousMatch):
    choose = choice[segment][previousMatch]
    ret = corpus[choose]
    if segment < n - 1:
        ret = ret + " " + reconstruct(segment + 1, choose)
    return ret

total_m = 5 # 단어의 수
total_q = 3 # 처리해야 할 문장의 수
total_m_str_arr = 'I am a boy buy'.split() # 원문에 출현할 수 있는 m개의 단어 - 공백으로 구분
B = [1.0, 0.0, 0.0, 0.0, 0.0] # 각 단어가 문장의 처음에 출현할 확률

# T = m x m 크기의 행렬로, T[i, j] 는 i 번 단어의 다음 단어가 j번 단어일 확률. 각 행의 합은 항상 1
T = [
        [0.1, 0.6, 0.1, 0.1, 0.1],
        [0.1, 0.1, 0.6, 0.1, 0.1],
        [0.1, 0.1, 0.1, 0.6, 0.1],
        [0.2, 0.2, 0.2, 0.2, 0.2],
        [0.2, 0.2, 0.2, 0.2, 0.2]
    ]

# M = m x m 크기의 행렬로, M[i, j] 는 i 번 단어가 적힌 조각을 j번 단어로 분류할 확률. 각 행의 합은 항상 1
M = [
        [0.8, 0.1, 0.0, 0.1, 0.0],
        [0.1, 0.7, 0.0, 0.2, 0.0],
        [0.0, 0.1, 0.8, 0.0, 0.1],
        [0.0, 0.0, 0.0, 0.5, 0.5],
        [0.0, 0.0, 0.0, 0.5, 0.5]
    ]

q1 = '4 I am a buy'.split()
q2 = '4 I I a boy'.split()
q3 = '4 I am am boy'.split()


# In[24]:


# q1
m = total_m # 단어의 수
n = int(q1[0]) # 분류기로 인식한 단어 수
R = [] # 분류기로 인식한 문장인데, 각 단어를 전체 입력 가능 단어의 index 화
for i in range(0, n):
    R.append(total_m_str_arr.index(q1[i + 1])) # index 찾아 번호를 R 에 추가
choice = np.full((total_m + 2, total_m + 2), -1)
cache = np.full((total_m + 2, total_m + 2), 1.0)
corpus = total_m_str_arr # 입력 가능한 모든 단어

R, recognize(0, 0)
reconstruct(0, 0)


# In[25]:


# q2
m = total_m
n = int(q2[0])
R = []
for i in range(0, n):
    R.append(total_m_str_arr.index(q2[i + 1]))
choice = np.full((total_m + 2, total_m + 2), -1)
cache = np.full((total_m + 2, total_m + 2), 1.0)
corpus = total_m_str_arr

R, recognize(0, 0)
reconstruct(0, 0)


# In[26]:


# q3
m = total_m
n = int(q3[0])
R = []
for i in range(0, n):
    R.append(total_m_str_arr.index(q3[i + 1]))
choice = np.full((total_m + 2, total_m + 2), -1)
cache = np.full((total_m + 2, total_m + 2), 1.0)
corpus = total_m_str_arr

R, recognize(0, 0)
reconstruct(0, 0)

