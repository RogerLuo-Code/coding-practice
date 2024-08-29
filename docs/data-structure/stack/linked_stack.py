"""Linked Stack
A generic stack, implemented using a linked list
"""

from typing import Any


class Node:
    def __init__(self, data: Any) -> None:
        self.data = data
        self.next = None

    def __repr__(self) -> Any:
        return self.data


class LinkedStack:
    """Linked Stack
    Represents a last-in-first-out (LIFO) stack. It support the usual `push` and
    `pop` operations, along with methods for peeking at the first item, testing if
    the stack is empty, and iterating through the item in LIFO order.

    The implementation uses a singly linked list. The `push`, `pop`, `peek`,
    `size`, and `is_empty` operations take constant time in the worst case.
    """

    def __init__(self) -> None:
        self.first = None
        self.n = 0

    def __iter__(self) -> Any:
        """Iteration
        Iterate through the node data in FIFO order

        Returns:
            data: node data
        """
        current = self.first
        while current is not None:
            yield current.data
            current = current.next

    def __repr__(self) -> str:
        """String representation of stack

        Returns:
            str: string representation of stack
        """
        data_list = []
        for data in self:
            data_list.append(data)
        return " ".join(data_list)

    def is_empty(self) -> bool:
        """Is this stack empty?

        Returns:
            bool: true if this stack is empty; false otherwise
        """
        return self.first is None

    def size(self) -> int:
        """Number of items

        Returns:
            int: number of items in this stack
        """
        return self.n

    def peek(self) -> Any:
        if self.is_empty():
            raise ValueError("stack underflow")
        return self.first.data

    def push(self, data: Any) -> None:
        """Push data to the top of stack

        Args:
            data (Any): data to be added to this stack
        """
        old_first = self.first
        self.first = Node(data=data)
        self.first.next = old_first
        self.n += 1

    def pop(self) -> Any:
        """Removes and returns the data from this stack that was recently added

        Returns:
            Any: the data on this stack that was recently added
        """
        if self.is_empty():
            raise ValueError("stack underflow")

        data = self.first.data
        self.first = self.first.next
        self.n -= 1

        return data


if __name__ == "__main__":
    stack = LinkedStack()
    print(stack)

    input_str = input("Enter data:")
    while input_str != "":
        if input_str != "-":
            stack.push(input_str)
        elif not stack.is_empty():
            print(stack.pop() + " ")
        input_str = input("")
    print(stack)