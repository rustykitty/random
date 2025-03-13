from __future__ import annotations

from typing import (
    Iterable,
    Any,
    Generic,
    TypeVar,
    Generator
)

from itertools import islice

T = TypeVar("T")

class LinkedList(Generic[T]):

    __slots__ = ("head", "tail", "length")

    class Node(Generic[T]):
        __slots__ = ("val", "prev", "next")

        def __init__(self, val: T = None, prev: LinkedList.Node = None, next: LinkedList.Node = None): 
            self.val = val
            self.prev = prev
            self.next = next

    def __init__(self, iterable: Iterable[T] = None):
        self.head = self.Node()
        self.tail = self.Node()
        self.head.next = self.tail
        self.tail.prev = self.head
        self.length: int = 0
        if iterable is not None:
            for item in iterable:
                self.append(item)
        
    def __iter__(self) -> Generator[T]:
        node: LinkedList.Node = self.head.next
        while node != self.tail:
            yield node.val
            node = node.next

    def __reversed__(self) -> Generator[T]:
        node: LinkedList.Node = self.tail.prev
        while node != self.head:
            yield node.val
            node = node.prev

    def __len__(self) -> int: return self.length

    def __bool__(self): return bool(self.length)

    def __contains__(self, item: T): return item in iter(self)

    def append(self, item: T):
        return self._insert_node(self.tail.prev, self.Node(item))

    def appendleft(self, item: T):
        return self._insert_node(self.head, self.Node(item))

    def _insert_node(self, pos: Node, node: Node):
        if pos == self.tail:
            raise ValueError("cannot _insert after tail")
        next = pos.next
        node.prev = pos
        node.next = next
        pos.next = node
        next.prev = node
        self.length += 1

    def clear(self):
        self.head.next = self.tail
        self.tail.prev = self.head
        self.length

    def copy(self):
        return LinkedList(self)
    
    def count(self, x):
        return sum(x == i for i in self)

    def extend(self, iterable: Iterable):
        for i in iterable:
            self.append(i)

    def extendleft(self, iterable: Iterable):
        for i in iterable:
            self.append(i)

    def index(self, item, start=0, stop=-1):
        it = islice(enumerate(self._node_iter()), start, stop)
        for p in it:
            i, node = p
            if node.val == item: return i
        raise ValueError(f"{item} is not in {self.__class__.__name__}")

    def insert(self, index: int, item: T):
        return self._insert_node(self._get_node_by_index(index), self.Node(item))

    def pop(self) -> T:
        if self.length == 0: raise IndexError(f"pop from empty {self.__class__.__name__}")
        return self._remove(self.tail.prev)
    
    def popleft(self) -> T:
        if self.length == 0: raise IndexError(f"popleft from empty {self.__class__.__name__}") 
        return self._remove(self.head.next)

    def remove(self, item: T):
        for node in self._node_iter():
            if node.val == item: 
                self._remove(node)
                return
        raise IndexError(f"{item} is not in {self.__class__.__name__}")

    def _remove(self, node: Node) -> T:
        if node == self.head:
            raise ValueError("cannot remove head")
        elif node == self.tail:
            raise ValueError("cannot remove tail")
        prev = node.prev
        next = node.next
        prev.next = next
        next.prev = prev
        self.length -= 1
        return node.val

    def reverse(self):
        for (i, j) in zip(self._node_iter(), self._node_reversed_iter()):
            if i.prev is j: break
            if i is j: break
            i.val, j.val = j.val, i.val

    def rotate(self, n=1):
        if not self: return
        for _ in range(n):
            self.appendleft(self.pop())

    def _get_node_by_index(self, index: int) -> Node:
        if not (-self.length <= index < self.length):
            raise IndexError(f"{self.__class__.__name__} index out of range")
        if index < 0:
            return next(self._node_reversed_iter, ~index, (~index) + 1)
        else:
            return next(self._node_iter, index, index + 1)
    
    def _node_iter(self) -> Generator[Node]:
        node: LinkedList.Node = self.head.next
        while node != self.tail:
            yield node
            node = node.next

    def _node_reversed_iter(self) -> Generator[Node]:
        node: LinkedList.Node = self.tail.prev
        while node != self.head:
            yield node
            node = node.prev
