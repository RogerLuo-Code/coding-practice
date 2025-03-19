"""Circular Linked List
Implement circular linked list from scratch.
"""


from typing import Any


class Node:
    def __init__(self, data: Any) -> None:
        self.data = data
        self.next = None

    def __repr__(self) -> Any:
        return self.data


class CircularLinkedList:
    def __init__(self, nodes: list[Any] = None) -> None:
        self.tail = None
        if nodes is not None:
            for elem in nodes:
                node = Node(data=elem)
                self.append(node)

    def __iter__(self):
        """Traverse the list
        It can be replaced by a specific traverse function
        """
        if self.tail is None:
            yield None
        else:
            node = self.tail.next
            head = self.tail.next
            while node is not None and (node.next is not head):
                yield node
                node = node.next
            yield node  # tail node

    def __repr__(self) -> str:
        nodes = []
        for node in self:
            if node is not None:
                nodes.append(node.data)

        return " -> ".join(nodes)

    def append(self, node: Node) -> None:
        """Append new node to circular linked list
        There is no difference between append from head or tail since it is
        circular

        Args:
            node (Node): node to append
        """
        if self.tail is None:
            self.add_first_node(node)
        else:
            head = self.tail.next
            self.tail.next = node
            node.next = head
            self.tail = self.tail.next

    def add_first_node(self, node: Node) -> None:
        self.tail = node
        node.next = self.tail

    def pop_left(self) -> None:
        if self.tail is None:
            raise IndexError("List is empty")

        if self.tail.next is self.tail:
            self.tail = None
        else:
            head = self.tail.next
            self.tail.next = head.next

    def pop(self) -> None:
        if self.tail is None:
            raise IndexError("List is empty")

        prev_node = self.tail
        for node in self:
            if node is self.tail:
                prev_node.next = self.tail.next
                self.tail = prev_node
                return
            prev_node = node

    def remove(self, target_node_data: Any) -> None:
        """Remove node that contains target data

        Args:
            target_node_data (Any): data of node that will be removed

        Raises:
            ValueError: Target node not found
        """

        if self.tail is None:
            raise ValueError("List is empty")

        previous_node = self.tail
        for node in self:
            if node.data == target_node_data:
                previous_node.next = node.next
                node.next = None
                return
            previous_node = node

        raise ValueError(f"Node with data {target_node_data} not found")


if __name__ == "__main__":
    circular_llist = CircularLinkedList()
    print(circular_llist)

    circular_llist = CircularLinkedList(["a1", "a2", "a3", "a4", "a5"])
    print(circular_llist)

    circular_llist.append(Node("a"))
    print(circular_llist)
    circular_llist.append(Node("b"))
    print(circular_llist)
    circular_llist.append(Node("c"))
    print(circular_llist)
    circular_llist.append(Node("d"))
    print(circular_llist)
    # circular_llist.starting_node = circular_llist.head.next
    # print(circular_llist)
    # Use __iter__ to traverse the list
    for node in circular_llist:
        print(node)

    circular_llist.pop()
    print(circular_llist)

    circular_llist.pop_left()
    print(circular_llist)

    circular_llist.remove("b")
    print(circular_llist)

    circular_llist.append(Node("cc"))
    circular_llist.append(Node("ccc"))
    circular_llist.append(Node("cccc"))
    print(circular_llist)

    circular_llist.remove("ccc")
    print(circular_llist)
