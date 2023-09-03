---
tags:
    - Array
    - Sliding Window
    - Hash Table
---

# LC904. Fruit Into Baskets
## Problem Description
[LeetCode Problem 904](https://leetcode.com/problems/fruit-into-baskets/):
You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array `fruits` where `fruits[i]` is the **type** of fruit the `ith` tree produces.

You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:

- You only have **two** baskets, and each basket can only hold a **single type** of fruit. There is no limit on the amount of fruit each basket can hold.
- Starting from any tree of your choice, you must pick **exactly one fruit** from **every** tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
- Once you reach a tree with fruit that cannot fit in your baskets, you must stop.

Given the integer array `fruits`, return _the **maximum** number of fruits you can pick_.

## Clarification
- only can collect two types of fruit
- pick one fruit from every tree (continuously)

## Assumption

## Solution
The problem can be viewed as finding out the longest length of subarrays with at most 2 different types.

### Approach - Sliding Window + Hashmap
The problem can be solved with sliding window and maintain a hashmap `count` to count the number of element within the window (between two pointers). For sliding window, there are two different ways:

1. Expand and shrink window based on number of types (use `while` to check number of types)
2. Keeps the longest window. The window doesn't shrink and expands when finding larger size (use `if` to check number of types). Refer to [@lee215 solution](https://leetcode.com/problems/fruit-into-baskets/solutions/170740/java-c-python-sliding-window-for-k-elements/)

```python
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        left = 0
        count = {}
        max_size = 0

        for right, fruit in enumerate(fruits):
            count[fruit] = count.get(fruit, 0) + 1

            while len(count) > 2 :
                count[fruits[left]] -= 1
                if count[fruits[left]] == 0:
                    del count[fruits[left]]
                left += 1

            max_size = max(max_size, right - left + 1)

        return max_size
```

```python
class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        left = 0
        count = {}

        for right, fruit in enumerate(fruits):
            count[fruit] = count.get(fruit, 0) + 1

            if len(count) > 2 :
                count[fruits[left]] -= 1
                if count[fruits[left]] == 0:
                    del count[fruits[left]]
                left += 1

        return right - left + 1
```

`while` vs. `if`:

- In terms of time complexity, 
    - `while` method takes $O(2n)$ since in the worst case both left and right pointers move to the last element
    - `if` methods takes $O(n)$ since just the right pointer move to the last element
- In terms of space complexity, 
    - `while` method takes $O(1)$ space, since it only stores at most three types yet 
    - `if` method takes $O(n)$ space, since it may store more than two types which can be as high as $n/2$. For example, if the first half $n/2$ is the same type while the 2nd half has different types with $n/2$ types [1, 1, 1, 1, 1, 2, 3, 4, 5]. The hashmap with `if` method will n/2 type.

#### Complexity Analysis
* Time complexity: $O(n)$  
	Iterate through the whole array and therefore it is $O(n)$.  
* Space complexity: $O(1)$  
	Use hashmap to store two types (when using `while` loop). It could be $O(m)$ when using `if` statement.  


## Test