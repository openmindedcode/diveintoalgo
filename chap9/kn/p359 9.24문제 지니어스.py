#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
 
def getProb1():
	c = np.full((5,50), 0.0)
	c[0][0] = 1.0
 
	for time in range(1, k + 1):
		for song in range(0, n):
			prob = 0
			for last in range(0, n):
				prob += c[(time - length[last] + 5) % 5][last] * T[last][song]
			c[time % 5][song] = prob
 
	ret = np.full(m, 0.0)
 
	for song in range(0, n):
		for start in range(k - length[song] + 1, k + 1):
			ret[song] += c[start % 5][song]
	
	return ret
 
n, k, m = 3, 6, 3
length = [4, 4, 2]
T = [[0.18, 0.40, 0.42],
	[0.15, 0.46, 0.39],
	[0.58, 0.23, 0.19]]
	
print(getProb1().tolist())
 
n, k, m = 4, 10, 4
length = [1, 3, 2, 4]
T = [[0.26, 0.07, 0.49, 0.18],
	[0.21, 0.33, 0.15, 0.31],
	[0.41, 0.20, 0.38, 0.01],
	[0.28, 0.31, 0.18, 0.23]]
	
print(getProb1().tolist())
 
n, k, m = 4, 1000, 4
length = [4, 3, 4, 4]
T = [[0.08, 0.47, 0.12, 0.33],
	[0.10, 0.02, 0.39, 0.49],
	[0.08, 0.33, 0.35, 0.24],
	[0.14, 0.19, 0.58, 0.09]]
		
print(getProb1().tolist())


# In[ ]:




