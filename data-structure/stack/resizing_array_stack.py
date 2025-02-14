"""Resizing Array Stack
Stack implementation with a resizing array.
"""

from typing import Any


class ResizingArrayStack:
    """Resizing Array Stack
    Represents a last-in-first-out (LIFO) stack. It support the usual `push` and
    `pop` operations, along with methods for peeking at the first item, testing if
    the stack is empty, and iterating through the item in LIFO order.

    The implementation uses Python list, which dynamically adjust array size. The `push`
    and `pop` operations take constant amortized time. The `peek`, `size`, and
    `is_empty` operations take constant time in the worst case.
    """

    def __init__(self) -> None:
        self.array = []

    # def __iter__(self) -> Any:
    #     """Iteration
    #     Iterate through the node data in LIFO order

    #     Returns:
    #         data: node data
    #     """
    #     for data in self.array:
    #         yield data

    def __repr__(self) -> str:
        """String representation of stack

        Returns:
            str: string representation of stack
        """
        return " ".join(self.array)

    def is_empty(self) -> bool:
        """Is this stack empty?

        Returns:
            bool: true if this stack is empty; false otherwise
        """
        return len(self.array) == 0

    def size(self) -> int:
        """Number of items

        Returns:
            int: number of items in this stack
        """
        return len(self.array)

    def peek(self) -> Any:
        if self.is_empty():
            raise ValueError("stack underflow")
        return self.array[-1]

    def push(self, data: Any) -> None:
        """Push data to the top of stack

        Args:
            data (Any): data to be added to this stack
        """
        self.array.append(data)

    def pop(self) -> Any:
        """Removes and returns the data from this stack that was recently added

        Returns:
            Any: the data on this stack that was recently added
        """
        if self.is_empty():
            raise ValueError("stack underflow")
        return self.array.pop()


if __name__ == "__main__":
    stack = ResizingArrayStack()
    print(stack)

    input_str = input("Enter data:")
    while input_str != "":
        if input_str != "-":
            stack.push(input_str)
        elif not stack.is_empty():
            print(stack.pop() + " ")
        input_str = input("")
    print(stack)