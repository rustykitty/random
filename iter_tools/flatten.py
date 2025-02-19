from typing import (
    Any, Iterable
)

from collections import deque

from generator import generator

# def flatten(iterable: Iterable[Any]):
#     for item in iterable:
#         if isinstance(item, Iterable):
#             yield from item
#         else:
#             yield item

class flatten(generator):
    def __init__(self, iterable: Iterable[Any]):
        self.iterator = iter(iterable)
        self.stack: deque[Iterable[Any]] = deque((self.iterator,))

    def __next__(self):
        if not self.stack: raise StopIteration
        try:
            n = next(self.stack[-1]) # advance TOS iterator
            while isinstance(n, Iterable):
                it = iter(n)
                self.stack.append(it)
                n = next(it)
        except StopIteration:
            self.stack.pop()
            if not self.stack: raise StopIteration
            while True:
                try:
                    n = next(self.stack[-1])
                except StopIteration:
                    self.stack.pop()
                else:
                    break
        return n

print(list(flatten([1, 2, 3, [4, 5, [6]], [7, 8], 9])))