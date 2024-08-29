"""Linked Queue
A generic queue, implemented using a singly linked list
"""

from typing import Any


class Node:
    def __init__(self, data: Any) -> None:
        self.data = data
        self.next = None

    def __repr__(self) -> Any:
        return self.data


class LinkedQueue:
    """Linked Queue
    Represents a first-in-first-out (FIFO) queue. It support the usual `enqueue` and
    `dequeue` operations, along with methods for peeking at the first item, testing if
    the queue is empty, and iterating through the item in FIFO order.

    The implementation uses a singly linked list. The `enqueue`, `dequeue`, `peek`,
    `size`, and `is_empty` operations take constant time in the worst case.
    """

    def __init__(self) -> None:
        self.first = None
        self.last = None
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
        """String representation of queue

        Returns:
            str: string representation of queue
        """
        data_list = []
        for data in self:
            data_list.append(data)
        return " ".join(data_list)

    def is_empty(self) -> bool:
        """Is this queue empty?

        Returns:
            bool: true if this queue is empty; false otherwise
        """
        return self.first is None

    def size(self) -> int:
        """Number of items

        Returns:
            int: number of items in this queue
        """
        return self.n

    def peek(self) -> Any:
        if self.is_empty():
            raise ValueError("Queue underflow")
        return self.first.data

    def enqueue(self, data: Any) -> None:
        """Add data to this queue

        Args:
            data (Any): data to be added to this queue
        """
        old_last = self.last
        self.last = Node(data=data)
        if self.is_empty():
            self.first = self.last
        else:
            old_last.next = self.last
        self.n += 1

    def dequeue(self) -> Any:
        """Removes and returns the data from this queue that was least recently added

        Returns:
            Any: the data on this queue that was least recently added
        """
        if self.is_empty():
            raise ValueError("Queue underflow")

        data = self.first.data
        self.first = self.first.next
        self.n -= 1

        # To avoid loitering
        if self.is_empty():
            self.last = None

        return data


if __name__ == "__main__":
    queue = LinkedQueue()
    print(queue)

    input_str = input("Enter data:")
    while input_str != "":
        if input_str != "-":
            queue.enqueue(input_str)
        elif not queue.is_empty():
            print(queue.dequeue() + " ")
        input_str = input("")
    print(queue)