# Binary search
def binary_search(array, key):
  left, right = 0, len(array)-1
  while left <= right:
    mid = left + (right - left)//2;
    # print(mid)
    if key < array[mid]:
      right = mid - 1  
    elif key > array[mid]:
      left = mid + 1
    else:
      return mid
  return -1

class ThreeSumSort:
    @staticmethod
    def count(a):
        n   = len(a)
        a_sort = sorted(a)
        count = 0
        for i in range(n):
            for j in range(i+1, n):
                index = binary_search(a_sort[j+1:], -(a_sort[i] + a_sort[j]))
                if index >= 0:
                    count += 1
        return count;

    # Measure the exetuiont time for different sizes of input
import random
import time

n_list = []  # list of input size
tm_list = [] # list of elspased time of ThreeSum function for different input sizes
for i_run in range(2, 7, 2):
  n = i_run*10
  rand_input = random.sample(range(-20000, 20000), n)

  t0 = time.time()
  ans = ThreeSumSort.count(rand_input)
  te = time.time()
  elapsed_time = te - t0

  n_list.append(n)
  tm_list.append(elapsed_time)

  print('Input size: ', n)
  # print('Input: ', rand_input)
  print('Three sum count: ', ans)
  print('Elapsed time: ', elapsed_time)