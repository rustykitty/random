from __future__ import annotations

from typing import (
    Iterable,
    Any,
    Generic,
    TypeVar
)

T = TypeVar("T")

class LinkedList(Generic[T]):
    class Node(Generic[T]):
        __slots__ = ("val", "prev", "next")

        def __init__(self, val: T = None, prev: LinkedList.Node = None, next: LinkedList.Node = None): 
            self.val = val
            self.prev = prev
            self.next = next

        def link(self, other: LinkedList.Node):
            self.next = other.prev
            self.prev = other.next

    def __init__(self, iterable: Iterable[T] = None):
        self.head = self.Node()
        self.tail = self.Node()
        self.head.next = self.tail
        self.tail.prev = self.head
        self.length: int = 0
        if iterable is not None:
            for item in iterable:
                self.append(item)
        
    def __iter__(self):
        node: LinkedList.Node = self.head.next
        while node != self.tail:
            yield node.val
            node = node.next

    def __reversed__(self):
        node: LinkedList.Node = self.tail.prev
        while node != self.head:
            yield node.val
            node = node.prev

    def __len__(self): return self.length

    def append(self, item: T):
        prev = self.tail.prev
        node = self.Node(item, prev, self.tail)
        prev.next = node
        self.tail.prev = node
        self.length += 1

    def appendleft(self, item: T):
        next = self.head.next
        node = self.Node(item, self.head, next)
        next.prev = node
        self.head.next = node
        self.length += 1