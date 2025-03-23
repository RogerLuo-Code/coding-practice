# Linked List

## Main Concepts

A linked list is a collection of nodes and each node contains at least two fields:

- `Data` contains the value
- `Next` contains the reference to the next node
- `Prev` contains the reference to the previous node (used for doubly linked list)

The first node is usually called the **head** and used as the starting point of any
iteration through the list. The last must have its next reference pointing to `None` or
`Null` to determine the end of the list.

![linked list](https://files.realpython.com/media/Group_14.27f7c4c6ec02.png)

## Different Types of Linked List

- Singly linked list
![singly linked list](https://files.realpython.com/media/Group_14.27f7c4c6ec02.png)
- Doubly linked list
![doubly linked list](https://files.realpython.com/media/Group_21.7139fd0c8abb.png)
- Circular linked list: the last node points back to the head of the list to form a
circle instead of pointing to None
![circular linked list](https://files.realpython.com/media/Group_22.cee69a15dbe3.png)

## Practical Applications

- Implement queues, stacks, or graphs
- Used for more complex tasks, such as lifecycle management for an operation system application

## List Vs. Linked List

### Memory

- Arrays or lists use a contiguous memory block to store references to data
- Linked lists don't use contiguous memory and store references as part of their own elements

### Performance

- For Python lists:
    - Insert elements at the **end** of a list is $O(1)$
    - Insert at the beginning of the list, the average time complexity is $O(n)$
- Linked lists:
    - Insert or remove elements at the beginning or end of a list, the time complexity
    is $O(1)$

So for

- queue: linked list is better than normal list
- stack: linked list is similar to normal list since insert and remove at the end of the
list

### Access Elements

For retrieval:

- Lists: $O(1)$ time to find element via index
- Linked list: $O(n)$, since traverse the whole list to find the element

For searching for a specific element, both lists and linked lists take $O(n)$ time

## Implementations

- [Singly linked list](singly_linked_list.py)
- [Doubly linked list](doubly_linked_list.py)
- [Circular linked list](circular_linked_list.py)

## References

- [Real python linked list](https://realpython.com/linked-lists-python/)
