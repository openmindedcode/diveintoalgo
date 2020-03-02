#!/usr/bin/env python
# coding: utf-8

# In[16]:


import numpy as np

# 9.27
def sushi(budget):
    ret = cache[budget]
    if ret != -1:
        return ret
    ret = 0
    for dish in range(0,n):
        if (budget < price[dish]):
            continue
        ret = cache[budget] = max(ret, sushi(budget - price[dish]) + pref[dish])
    return ret

#problem1
n = 6
m = 10000 # budget
price = [2500, 3000, 4000, 5000, 10000, 15000]
pref = [7, 9, 10, 12, 20, 1]

cache = np.full(m + 1, -1)
print('problem1 ret:', sushi(m))

#problem2
n = 6
m = 543975612 # budget
price = [2500, 3000, 4000, 5000, 10000, 15000]
pref = [7, 9, 10, 12, 20, 1]

# error: maximum recursion depth exceeded in comparison
# cache = np.full(m + 1, -1)
# print('problem2 ret:', sushi(m))


# In[23]:


# 9.28
def sushi2():
    ret = 0
    for budget in range(1, m+1):
        c[budget] = 0
        for dish in range(0, n):
            if budget >= price[dish]:
                c[budget] = max(c[budget], c[budget - price[dish]] + pref[dish])
        ret = max(ret, c[budget])
    return ret

#problem1
n = 6
m = 10000 # budget
price = [2500, 3000, 4000, 5000, 10000, 15000]
pref = [7, 9, 10, 12, 20, 1]

c = np.full(m + 1, 0)
print('problem1 ret:', sushi2())

#problem2
n = 6
m = 543975612 # budget
price = [2500, 3000, 4000, 5000, 10000, 15000]
pref = [7, 9, 10, 12, 20, 1]

# so many time...
#c = np.full(m + 1, 0)
#print('problem2 ret:', sushi2())


# In[32]:


# 9.29
def precalc(price):
    new_price = []
    for i in range(0, len(price)):
        new_price.append((int)(price[i] / 100))
    return new_price

def sushi3():
    ret = 0
    c[0] = 0
    for budget in range(1, m+1):
        cand = 0
        for dish in range(0, n):
            if budget >= price[dish]:
                cand = max(cand, c[(budget - price[dish]) % 201] + pref[dish])
        c[budget % 201] = cand
        ret = max(ret, cand)
    return ret

#problem1
n = 6
m = (int)(10000 / 100) # budget
price = [2500, 3000, 4000, 5000, 10000, 15000]
pref = [7, 9, 10, 12, 20, 1]

c = np.full(m + 1, 0)
price = precalc(price)
print('problem1 ret:', sushi3())

#problem2
n = 6
m = (int)(543975612 / 100)# budget
price = [2500, 3000, 4000, 5000, 10000, 15000]
pref = [7, 9, 10, 12, 20, 1]

# error: maximum recursion depth exceeded in comparison
c = np.full(m + 1, 0)
price = precalc(price)
print('problem2 ret:', sushi3())

