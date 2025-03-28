---
tags:
    - Dynamic Programming
---

# 70. Climbing Stairs

## Problem Description

[LeetCode Problem 70](https://leetcode.com/problems/climbing-stairs/description/): You
are climbing a staircase. It takes `n` steps to reach the top.

Each time you can either climb `1` or `2` steps. In how many distinct ways can you climb
to the top?

## Clarification

-

## Assumption

- $n >= 1$

## Solution

One can reach $n$th step in two **distinct** ways:

- Taking a step from $(n - 1)$th step
- Taking a step of 2 from $(n - 2)$th step. Note that take 1 step twice from $(n - 2)$th
step is covered by $(n - 1)$th step.

So the total number of distinct ways to reach $n$th step is the sum of ways of reaching
$(n − 1)$th step and ways of reaching $(n − 2)$th step. Let
$f(i)$ denotes the number of distinct ways to reach $i$th step, then we have
$f(i) = f(i − 1) + f(i − 2)$. This becomes a problem of finding $i$th number of the
Fibonacci series with base cases $f(1) = 1$ and $f(2) = 2$.
Check [509 Fibonacci Number](../lc0500-0599/lc0509-fibonacci-number.md) for detailed solutions.

## Test
