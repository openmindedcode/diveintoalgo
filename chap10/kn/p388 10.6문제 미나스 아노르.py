import math
import numpy as np

# https://kr.mathworks.com/help/matlab/ref/acos.html
pi = 2.0 * math.acos(0)

global y, x, r, ranges

def init():
  return np.full(100, 0.0), np.full(100, 0.0), np.full(100, 0.0), []

def convertToRange():
    for i in range(0, n):
        loc = math.fmod(2 * pi + math.atan2(y[i], x[i]), 2 * pi)
        reach = 2.0 * math.asin(r[i] / 2.0 / 8.0)
        ranges.append((loc - reach, loc + reach))

    ranges.sort()

INF = 987654321

def solveLinear(begin, end):
  used = 0
  idx = 0

  while(begin < end):
    maxCover = -1
    while (idx < n and ranges[idx][0] <= begin):
      maxCover = max(maxCover, ranges[idx][1])
      idx += 1

    if maxCover <= begin:
      return INF
    begin = maxCover
    used += 1

  return used

def solveCircular():
  ranges.sort()

  ret = INF
  for i in range(0, n):
    (first, second) = ranges[i]
    if first <= 0 or second >= 2 * pi:
      begin = math.fmod(second, 2*pi)
      end = math.fmod(first + 2*pi, 2*pi)
      ret = min(ret, 1 + solveLinear(begin, end))

  if ret == INF:
    return 'IMPOSSIBLE'
  else:
    return ret

n = 10
y, x, r, ranges = init()
y[0], x[0], r[0] = 7.02066050, -3.83540431, 4.0
y[1], x[1], r[1] = -7.23257714, -3.41903904, 2.0
y[2], x[2], r[2] = 0.0, -8.0, 8.0
y[3], x[3], r[3] = -8.0, -0.0, 4.8
y[4], x[4], r[4] = -6.47213595, 4.70228202, 3.2
y[5], x[5], r[5] = -4.70228202, 6.47213595, 4.8
y[6], x[6], r[6] = 7.60845213, -2.48213595, 1.6
y[7], x[7], r[7] = -2.47213595, -7.60845213, 8.8
y[8], x[8], r[8] = 6.47213595, 4.70228202, 7.6
y[9], x[9], r[9] = -0.0, 8.0, 4.8

convertToRange()
print('problem1:', solveCircular())

n = 4
y, x, r, ranges = init()
y[0], x[0], r[0] = 8.0, 0.0, 8.0
y[1], x[1], r[1] = 0.0, -8.0, 8.0
y[2], x[2], r[2] = -8.0, -0.0, 8.0
y[3], x[3], r[3] = 1.25147572, 7.90150672, 5.4

convertToRange()
print('problem2:', solveCircular())

n = 1
y, x, r, ranges = init()
y[0], x[0], r[0] = 8.0, 0.0, 15.99

convertToRange()
print('problem3:', solveCircular())
