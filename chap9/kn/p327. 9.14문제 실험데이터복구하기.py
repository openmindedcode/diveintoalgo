#!/usr/bin/env python
# coding: utf-8

# In[41]:


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
            return (words[next][overlap[last][next]:] + reconstruct(next, used + (1<<next)))
        
    return "*******oops*******"

def getOverlap(s1, s2):
    minLen = min(len(s1), len(s2))
    for length in reversed(range(0, minLen + 1)):
        if s1[len(s1)-length:] == s2[0:length]:
            return length
    return 0

def prework(words):
    global k
    global overlap
    global cache

    k = len(words) # 문자열 개수
    overlap = np.full((k,  k), 0)
    cache = np.full((k, 1 << k), -1)
    
    '''
    words[j]가 words[i] 에 포함되는 경우, words[j] 를 빈 문자열로 치환해 무시해버림
    한 문자열이 다른 문자열에 포함되는 경우에 포함되는 문자열은 고려할 필요 없음.
    '''
    for i in range(0, k):
        for j in range(0, k):
            if (i != j) and (words[j] in words[i]):
                words[j] = ''

    '''
    overlay[i][j] == words[i] 과 words[j] 간에 겹치는 최대 문자 수
    ex) [0] zabcd, [1] cdez 이면,
    overlay[0][1] = zab'cd'ez 에서 'cd' 의 길이 2
    overlay[1][0] = cde'z'abcd 에서 'z' 의 길이 1
    '''
    for i in range(0, k):
        for j in range(0, k):
            overlap[i][j] = getOverlap(words[i], words[j])

    '''
    restore 는 words[last] 를 제외한 다른 words[i] 문자열을 순서대로 배열했을 때 겹치는 길이의 합 중 가장 긴 것을 반환
    '''
    ret = 0
    maxLast = 0
    for last in range(0, k):
        if ret < restore(last, 1 << last):
            maxLast = last
            ret = restore(last, 1 << last)

    return (k, overlap, cache, maxLast)

words = ['geo', 'oji', 'jing']
(k, overlap, cache, last) = prework(words)
print('ret: ', words[last] + reconstruct(last, 1<<last)) # 겹치는 길이의 합이 가장 긴 것(=문자열이 가장 짧음)을 맨 앞에 두고, 문자열을 만듬

words = ['world', 'hello']
(k, overlap, cache, last) = prework(words)
print('ret: ', words[last] + reconstruct(last, 1<<last))

words = ['abrac', 'cadabra', 'dabr']
(k, overlap, cache, last) = prework(words)
print('ret: ', words[last] + reconstruct(last, 1<<last))

