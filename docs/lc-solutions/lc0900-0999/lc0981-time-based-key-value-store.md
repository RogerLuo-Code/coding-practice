---
tags:
- Binary Search
---

# LC981. Time Based Key-Value Store
## Problem Description
[LeetCode Problem 981](https://leetcode.com/problems/time-based-key-value-store): Design a time-based key-value data structure that can store multiple values for the same key at different time stamps and retrieve the key's value at a certain timestamp.

Implement the `TimeMap` class:

- `TimeMap()` Initializes the object of the data structure.
- `void set(String key, String value, int timestamp)` Stores the key `key` with the value `value` at the given time `timestamp`.
- `String get(String key, int timestamp)` Returns a value such that `set` was called previously, with `timestamp_prev <= timestamp`. If there are multiple such values, it returns the value associated with the largest `timestamp_prev`. If there are no values, it returns `""`.

## Clarification
- 1 key to multiple values at different timestamps
- retrieve the key's value at a certain timestamp
- data type of timestamp, int?
- key and value contains both lower or upper case?

## Assumption
- timestamp is unique and increase with set function calls


## Solution
### Approach - Binary Search
Define a map data structure and map a list of `[value, timestamp]` to a key. Since `timestamp` is increased with `set` function calls, we can use binary search to find target `timestamp` quickly.  

=== "Python"
    ```python
    class TimeMap:

        def __init__(self):
            self.data = dict()

        def set(self, key: str, value: str, timestamp: int) -> None:
            if key not in self.data:
                self.data[key] = [[value, timestamp]]
            else:
                self.data[key].append([value, timestamp])

        def get(self, key: str, timestamp: int) -> str:
            if key not in self.data:
                return ""
            else:
                idx = self.find_recent_timestamp(key, timestamp)
                if idx == -1:
                    return ""
                else:
                    return self.data[key][idx][0]

        def find_recent_timestamp(self, key: str, timestamp: int) -> int:
            value = self.data[key]
            left, right = 0, len(value) - 1

            while left < right - 1:
                mid = (left + right) // 2
                if value[mid][1] == timestamp:
                    return mid
                elif timestamp < value[mid][1]:
                    right = mid - 1
                else:
                    left = mid

            if value[right][1] <= timestamp:
                return right
            elif value[left][1] <= timestamp:
                return left
            else:
                return -1
    ```

#### Complexity Analysis
* Time complexity: `set` is $O(1)$; `get` is $O(\log n_{set})$  
For `set` function, it adds the value to the end. So the time complexity is $O(1)$. For `get` function, it use binary search to find target timetamp and the search space is the number of `set` function calls for each key, $n_{set}$.
* Space complexity: $O(1)$  
Only use limited index variables.

## Test