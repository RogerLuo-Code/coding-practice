"""Doubly Linked list implementation
Implement doubly linked list from scratch.
"""


from typing import Any


class Node:
    def __init__(self, data: Any) -> None:
        self.data = data
        self.next = None
        self.previous = None

    def __repr_(self) -> Any:
        return self.data


class DoublyLinkedList:
    def __init__(self, nodes: list[Any] = None) -> None:
        self.head = None
        self.tail = None
        self.is_traverse_from_head_to_tail = True
        if nodes is not None:
            for elem in nodes:
                node = Node(data=elem)
                self.append(node)

    def __iter__(self) -> Node:
        """Traverse the list from head

        Returns:
            Node: yield node
        """
        if self.is_traverse_from_head_to_tail:
            node = self.head
            while node is not None:
                yield node
                node = node.next
        else:
            node = self.tail
            while node is not None:
                yield node
                node = node.prev

    def __repr__(self) -> str:
        nodes = ["None"]
        self.is_traverse_from_head_to_tail = True
        for node in self:
            nodes.append(node.data)
        nodes.append("None")
        node_str = " -> ".join(nodes)

        nodes.clear()
        nodes.append("None")
        self.is_traverse_from_head_to_tail = False
        for node in self:
            nodes.append(node.data)
        self.is_traverse_from_head_to_tail = True # Change it to default value
        nodes.append("None")
        nodes.reverse()
        node_str_reverse = " <- ".join(nodes)

        return node_str + "\n" + node_str_reverse

    def append(self, node: Node) -> None:
        if self.head is None or self.tail is None:
            self.add_first_node(node)
        else:
            self.tail.next = node
            prev = self.tail
            self.tail = self.tail.next
            self.tail.prev = prev
            self.tail.next = None

    def append_left(self, node: Node) -> None:
        if self.head is None or self.tail is None:
            self.add_first_node(node)
        else:
            self.head.prev = node
            node.next = self.head
            self.head = self.head.prev
            self.head.prev = None

    def add_first_node(self, node: Node) -> None:
        self.head = node
        self.head.prev = None
        self.head.next = None
        self.tail = self.head

    def pop(self) -> None:
        if self.tail is None:
            raise IndexError("List is empty")

        self.tail = self.tail.prev
        if self.tail is not None:
            self.tail.next = None

    def pop_left(self) -> None:
        if self.head is None:
            raise IndexError("List is empty")

        self.head = self.head.next
        if self.head is not None:
            self.head.prev = None


if __name__ == "__main__":
    llist = DoublyLinkedList(["a", "b", "c", "d", "e"])
    print(llist)

    llist.append(Node("f"))
    print(llist)

    llist.append_left(Node("-a"))
    print(llist)

    llist.pop()
    print(llist)

    llist.pop_left()
    print(llist)

    llist2 = DoublyLinkedList()
    print(llist2)

    llist2.append(Node("x"))
    print(llist2)

    llist2.pop_left()
    llist2.pop_left()
    print(llist2)

    llist2.pop()
    llist2.pop()
    print(llist2)