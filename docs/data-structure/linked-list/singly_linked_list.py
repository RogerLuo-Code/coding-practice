"""Single Linked list implementation
Implement singly linked list from scratch.
"""


from typing import Any


class Node:
    def __init__(self, data: Any) -> None:
        self.data = data
        self.next = None

    def __repr__(self) -> Any:
        return self.data


class LinkedList:
    """Singly linked list
    """
    def __init__(self, nodes: list[Any] = None) -> None:
        self.head = None
        self.tail = None
        if nodes is not None:
            for elem in nodes:
                node = Node(data=elem)
                self.append(node)
            # node = Node(data=nodes.pop(0))
            # self.head = node
            # for elem in nodes:
            #     node.next = Node(data=elem)
            #     node = node.next

    def __iter__(self) -> Node:
        """Traverse the list
        You may define traverse() for this functionality. It is better to use built-in
        Python features.
        """
        node = self.head
        while node is not None:
            yield node
            node = node.next

    def __repr__(self) -> str:
        nodes = []
        for node in self:
            nodes.append(node.data)
        nodes.append("None")
        return " -> ".join(nodes)

    def __getitem__(self, key: int) -> None:
        if self.head is None:
            raise ValueError("List is empty")

        count = 0
        for node in self:
            if count == key:
                return node.data
            count += 1

        raise IndexError('Index exceeds the length of the list.')

    def __setitem__(self, key: int, new_data: Any) -> None:
        if self.head is None:
            raise ValueError("List is empty")

        count = 0
        for node in self:
            if count == key:
                node.data = new_data
                return
            count += 1

        raise IndexError('Index exceeds the length of the list.')

    def append_left(self, node: Node) -> None:
        node.next = self.head
        self.head = node

    def append(self, node: Node) -> None:
        if self.head is None or self.tail is None:
            self.head = node
            self.head.next = None
            self.tail = self.head
            # return
            # # Find the tail node
            # for current_node in self:
            #     pass
        else:
            self.tail.next = node
            self.tail = self.tail.next
            self.tail.next = None

    def insert_after(self, target_node_data: Any, new_node: Node) -> None:
        if self.head is None:
            raise ValueError("List is empty")

        for node in self:
            if node.data == target_node_data:
                new_node.next = node.next
                node.next = new_node
                return

        raise ValueError(f"Node with data {target_node_data} not found")

    def insert_before(self, target_node_data: Any, new_node: Node) -> None:
        if self.head is None:
            raise ValueError("List is empty")

        if self.head.data == target_node_data:
            return self.append_left(new_node)

        prev_node = self.head
        for node in self:
            if node.data == target_node_data:
                prev_node.next = new_node
                new_node.next = node
                return
            prev_node = node

        raise ValueError(f"Node with data {target_node_data} not found")

    def insert(self, i: int, new_node: Node) -> None:
        """Insert new node at position i

        Args:
            i (int): 0-based position
            new_node (Node): New node

        Raises:
            IndexError: index exceed the length
        """
        if self.head is None:
            raise IndexError("List is empty")

        count = 0
        prev_node = self.head
        for node in self:
            if count == i:
                prev_node.next = new_node
                new_node.next = node
                return
            count += 1
            prev_node = node

        raise IndexError(f"Index {i} exceeds the list length")

    def pop(self) -> None:
        if self.head is None:
            raise IndexError("List is empty")

        prev_node = self.head
        for node in self:
            if node.next is None:
                prev_node.next = None
                return
            prev_node = node

        raise IndexError("Not find end of list")

    def pop_left(self) -> None:
        if self.head is None:
            raise IndexError("List is empty")

        self.head = self.head.next

    def remove(self, target_node_data: Any) -> None:
        """Remove node that contains target data

        Args:
            target_node_data (Any): data of node that will be removed

        Raises:
            ValueError: Target node not found
        """
        if self.head is None:
            raise ValueError("List is empty")

        if self.head.data == target_node_data:
            self.head = self.head.next
            return

        previous_node = self.head
        for node in self:
            if node.data == target_node_data:
                previous_node.next = node.next
                node.next = None
                return
            previous_node = node

        raise ValueError(f"Node with data {target_node_data} not found")

    def reverse(self) -> None:
        prev = None

        node = self.head
        while node is not None:
            nxt = node.next
            node.next = prev
            prev = node
            node = nxt

        self.head = prev


if __name__ == "__main__":
    llist = LinkedList(["a", "b", "c", "d", "e"])
    print(llist)

    # Use __iter__ to traverse the list
    for node in llist:
        print(node)

    llist.append_left(Node("-a"))
    llist.append_left(Node("-b"))
    print(llist)

    llist.append(Node("f"))
    print(llist)

    llist.insert_after("c", Node("cc"))
    print(llist)

    # llist.insert_after("g", Node("h")) # Exception

    llist.insert_before("b", Node("aa"))
    print(llist)

    # llist.insert_before("n", Node("m")) # Exception

    llist.remove("a")
    print(llist)

    llist.pop()
    print(llist)

    llist.pop_left()
    print(llist)

    print(llist[3])
    # print(llist[100]) # Exception

    llist[3] = "3"
    print(llist)

    llist.reverse()
    print(llist)

    llist.reverse()
    print(llist)
