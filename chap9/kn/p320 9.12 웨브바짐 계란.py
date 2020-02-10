#!/usr/bin/env python
# coding: utf-8

# In[26]:


#code 9.16
import numpy as np

def generate(price, taken):
    global count
    
    if len(price) == n:
        if price < e:
            if float(int(price) / m).is_integer():
                count += 1;
                # print(price, 'OK')
            # else:
                # print(price, 'NG')

        return
    
    for i in range (0, n):
        if not taken[i] and (i == 0 or digits[i-1] != digits[i] or taken[i-1]):
            taken[i] = True
            generate(price + digits[i], taken)
            taken[i] = False

print('problem1')
count = 0
e = "321"
m = 3
n = len(e)
digits = ''.join(sorted(e))
taken = np.full(15, False)
generate('', taken)
print(count)

print('problem2')
count = 0
e = "123"
m = 3
n = len(e)
digits = ''.join(sorted(e))
taken = np.full(15, False)
generate('', taken)
print(count)

print('problem3')
count = 0
e = "422"
m = 2
n = len(e)
digits = ''.join(sorted(e))
taken = np.full(15, False)
generate('', taken)
print(count)

print('problem4')
count = 0
e = "12738173912"
m = 7
n = len(e)
digits = ''.join(sorted(e))
taken = np.full(15, False)
generate('', taken)
print(count)


# In[40]:


#code 9.17
MOD = 1000000007

def price(index, taken, mod, less):
    if index == n:
        if less and mod == 0:
            return 1
        else:
            return 0
        
    ret = cache[taken][mod][less]

    if ret != -1:
        return ret
    
    ret = 0
    for next in range (0, n):
        if (taken & (1 << next)) == 0:
            if not less and (e[index] < digits[next]):
                continue
            
            if next > 0 and digits[next-1] == digits[next] and (taken & (1<<(next-1)) == 0):
                continue
                
            nextTaken = taken | (1 << next)
            nextMod = int((mod * 10 + int(digits[next])) % m)
            nextLess = int(less or e[index] > digits[next])
            ret += price(index+1, nextTaken, nextMod, nextLess)
            ret %= MOD
            cache[taken][mod][less] = ret

    return ret

cache = np.full((1<<14, 20, 2), -1)
e = "321"
m = 3
n = len(e)
digits = ''.join(sorted(e))
print('problem1', price(0, 0, 0, 0))

cache = np.full((1<<14, 20, 2), -1)
e = "123"
m = 3
n = len(e)
digits = ''.join(sorted(e))
print('problem2', price(0, 0, 0, 0))

cache = np.full((1<<14, 20, 2), -1)
e = "422"
m = 2
n = len(e)
digits = ''.join(sorted(e))
print('problem3', price(0, 0, 0, 0))

cache = np.full((1<<14, 20, 2), -1)
e = "12738173912"
m = 7
n = len(e)
digits = ''.join(sorted(e))
print('problem4', price(0, 0, 0, 0))

