---
tags:
    - Binary Search
---

# LC1146. Snapshot Array
## Problem Description
[LeetCode Problem 1146](https://leetcode.com/problems/snapshot-array/): Implement a SnapshotArray that supports the following interface:

- `SnapshotArray(int length)` initializes an array-like data structure with the given length. **Initially, each element equals 0**.
- `void set(index, val)` sets the element at the given `index` to be equal to `val`.
- `int snap()` takes a snapshot of the array and returns the `snap_id`: the total number of times we called `snap()` minus `1`.
- `int get(index, snap_id)` returns the value at the given `index`, at the time we took the snapshot with the given `snap_id`

## Clarification
- initial value 0
- How large it will be? $5 \times 10^4$
- Index out of range detection?
- Snap Id doesn't exist?
- What does snapshot mean? Store the current array somewhere to retrieve later?

## Assumption

## Solution
### Approach - Binary Search
First, we need to define a data structure to store the snapshots. We use a list of lists. Each index has its own list of `[snap_id, val]` which will only be updated when `set` function is called with unique `snap_id` value. If there are multiple `set` calls with the same `snap_id`, the `val` is updated with the recent value.

Then, when `get` value for a given `index` and `snap_id`. We will get the list of `[snap_id, val]` for the given `index`. Since the `snap_id` is sorted with increasing and unique values, we can use binary search to find the target snap_id and retrieve the `val`.

=== "Python"
    ```python
    class SnapshotArray:

        def __init__(self, length: int):
            self.array_snapshot = [[[0, 0]] for _ in range(length)]
            self.snap_id = 0

        def set(self, index: int, val: int) -> None:
            if self.array_snapshot[index][-1][0] == self.snap_id:
                self.array_snapshot[index][-1][1] = val  # (1)
            else:
                self.array_snapshot[index].append([self.snap_id, val])

        def snap(self) -> int:
            self.snap_id += 1
            return self.snap_id - 1

        def get(self, index: int, snap_id: int) -> int:
            array = self.array_snapshot[index]

            idx_snap = -1
            left, right = 0, len(array) - 1
            while left <= right:
                mid = (left + right) // 2
                if snap_id >= array[mid][0]:
                    idx_snap = mid
                    left = mid + 1  # (2)
                else:
                    right = mid - 1

            if idx_snap == -1:
                return 0
            else:
                return self.array_snapshot[index][idx_snap][1]
    ```

    1. Override previous value if set called for the same snap id
    2. Since `idx_snap` stores the `mid`, the potential solution, we can use `+ 1`

#### Complexity Analysis
* Time complexity:  
    - Constructor: $O(n)$ due to initialization, where $n$ is the length array.  
    - Set, snap: $O(1)$  
    - Get: $O(\log n_{set})$ where $n_{set}$ is the number of `set` function calls. Since using binary search, it takes at most $\log n_{set}$ steps.
* Space complexity: $O(n_{set})$  
	The snapshot array size is increased with number of `set` function calls.

## Test