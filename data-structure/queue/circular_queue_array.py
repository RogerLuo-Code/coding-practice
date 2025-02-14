class MyCircularQueue:

    def __init__(self, k: int):
        self.data = [None] * k
        self.head = -1
        self.tail = -1
        self.size = k
        
    def enQueue(self, value: int) -> bool:
        if self.isFull():
            return False
        
        if self.isEmpty():
            self.head = 0
        
        self.tail = (self.tail + 1) % self.size
        self.data[self.tail] = value
        return True
        
    def deQueue(self) -> bool:
        if self.isEmpty():
            return False
        elif self.head == self.tail:
            self.data[self.head] = None
            self.head = -1
            self.tail = -1
            return True
        else:
            self.data[self.head] = None
            self.head = (self.head + 1) % self.size
            return True

    def Front(self) -> int:
        if self.isEmpty():
            return - 1
        else:
            return self.data[self.head]
        
    def Rear(self) -> int:
        if self.isEmpty():
            return -1
        else:
            return self.data[self.tail]

    def isEmpty(self) -> bool:
        return self.head == -1 or self.tail == -1
        
    def isFull(self) -> bool:
        return (self.tail + 1) % self.size == self.head
        


# Your MyCircularQueue object will be instantiated and called as such:
# obj = MyCircularQueue(k)
# param_1 = obj.enQueue(value)
# param_2 = obj.deQueue()
# param_3 = obj.Front()
# param_4 = obj.Rear()
# param_5 = obj.isEmpty()
# param_6 = obj.isFull()