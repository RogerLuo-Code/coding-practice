---
tags:
    - Topological Sort
---

# LC269. Alien Dictionary

## Problem Description

[LeetCode Problem 269](https://leetcode.com/problems/alien-dictionary/description/):
There is a new alien language that uses the English alphabet. However, the order of the
letters is unknown to you.

You are given a list of strings `words` from the alien language's dictionary. Now it is
claimed that the strings in `words` are **sorted lexicographically** by the rules of
this new language.

If this claim is incorrect, and the given arrangement of string in `words` cannot
correspond to any order of letters, return `"".`

Otherwise, return a string of the unique letters in the new alien language sorted in
**lexicographically increasing order** by the new language's rules. If there are
multiple solutions, return _**any of them**_.

## Clarification

- The order is unknown.
- The order could be in correct in `words`
- When it is correct, return unique letters in order by the new rule
- Are letters in lower case or capital one?

## Assumption

-

## Solution

### Approach - Topological Sort

The problem can be viewed as a graph:

- Each character is a vertex.
- Order of letters (a in front of b) is a directed edge from a to b.

To solve the problem, we need to

1. Build the graph based on the order of words.
    - Compare adjacent words to find edges.
        - If two words differ at the first mismatched letter, add a directed edge from
        the letter in the first word to the letter in the second.
        - If a word is a prefix of another, the input is invalid (e.g., `["abc", "ab"]`.
        The correct order should be `["ab", "abc"]`).
    - Count the in-degree (number of incoming edges) for each nod.
2. Perform topological sort to find the order of letters.
    - Use a queue to perform a BFS for topological sorting:
        - Start with all nodes that have zero in-degree.
        - Remove edges from the graph as nodes are visited.
    - If the graph has a cycle, the topological sort will fail (not all nodes will be visited).

=== "Python"
    ```python
    from collections import defaultdict, deque


    class Solution:
        def alienOrder(self, words: List[str]) -> str:

            # (1)
            adj_list = defaultdict(set)
            in_degree = {char: 0 for word in words for char in word}

            # (2)
            for word1, word2 in zip(words, words[1:]):
                for char1, char2 in zip(word1, word2):
                    # Find the first difference and create an edge
                    if char1 != char2:
                        if char2 not in adj_list[char1]:
                            adj_list[char1].add(char2)
                            in_degree[char2] += 1
                        break
                else:
                    # (3)
                    if len(word2) < len(word1):
                        return ""

            # (4)
            ordered_chars = []
            zero_in_degree_chars = [char for char in in_degree if in_degree[char] == 0]
            zero_in_degree_queue = deque(zero_in_degree_chars)
            while zero_in_degree_queue:
                curr_char = zero_in_degree_queue.popleft()
                ordered_chars.append(curr_char)

                for next_char in adj_list[curr_char]:
                    in_degree[next_char] -= 1
                    if in_degree[next_char] == 0:
                        zero_in_degree_queue.append(next_char)

            if len(ordered_chars) == len(in_degree):
                return "".join(ordered_chars)
            else:
                return ""  # (5)
    ```

    1. Initialize adjacent list and in-degree dictionary.
    2. Build adjacent list and count in-degrees.
    3. Check for invalid input (prefix case), where second word isn't a prefix of first word.
    4. Perform topological sort.
    5. There is a cycle.

#### Complexity Analysis of Approach 1

- Time complexity: $O(C + V + E)$ where $C$ is the total number of letters in all words,
$V$ is the number of **unique** letters, and $E$ is the total number of edges.
    - Loop through all letters in all words to initialize in-degree dictionary takes
    $O(C)$, where $C$ is the total number of
    letters in all words.
    - Build adjacent list may go through all letters in the worst case, which takes $O(C)$.
    - Topological sort initialization iterate over the nodes (unique letters) in
    `in_degree`, which takes $O(V)$, where $V$ is the number of unique letters. Then
    enqueue all nodes with zero in-degree, which takes time less than $O(V)$. So the
    initialization takes $O(V)$.
    - Topological sort execution takes $O(V + E)$:
        - For queue operations, each node is dequeued and processed exactly once, which
        takes $O(V)$.
        - For neighboring explorations, the outgoing edges of each dequeued node are
        traversed to update the in-degrees of its neighbors. The total number of
        outgoing edges processed is $O(E)$, as each edge is processed exactly once.
    - So the total time complexity is $O(C) + O(C) + O(V) + O(V + E) = O(C + V + E)$
- Space complexity: $O(V + E)$  
    - In-degree dictionary tracks the in degree of all $V$ nodes, takes $O(V)$ space.
    The adjacent list stores all $V$ nodes and all $E$ edges, which takes $O(V + E)$ space.
    - The queue in the worst case may store all $V$ nodes, which takes $O(V)$ space.
    - The result list holds all $V$ nodes, taking $O(V)$ space.
    - So the total space complexity is $O(V) + O(V + E) + O(E) + O(V) = O(V + E)$.

## Test

- Single word (`words=["abc"]`): Order is the word’s characters (`"abc"`).
- No valid order due to cycles (`words=["z","x","z"]`).
- Completely independent characters (`words=["a","b","c"]`): Any order works (`"abc"`,
`"bac"`, etc.).