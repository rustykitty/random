"""
Python implementations of functions for iterables without using list comprehensions or stuff like that
"""

# from __future__ import annotations

from typing import (
    Any, Callable, Iterable, Iterator, Tuple, TypeVar
)

T = TypeVar('T')

class generator(Iterator):
    def __iter__(self): return self
    # def __next__(self): ... 

class filter(generator):

        def __init__(self, function: Callable[[T], bool], iterable: Iterable[T]):
            self.__function = function
            self.__iterator = iter(iterable)

        def __next__(self):
            while True:
                item = next(self.__iterator)
                if self.__function(item): return item
                else: continue

class map(generator):

    def __new__(cls, 
                function: Callable[[T], Any], 
                iterable: Iterable[T], 
                *iterables: Tuple[Iterable[T]]
                ):
        if len(iterables) == 0:
            return _map_single(function, iterable, *iterables)
        else:
            return _map_multiple(function, iterable, *iterables)

class _map_single(map):

    def __init__(self, function: Callable[[T], Any], iterable: Iterable[T]):
        self.function = function
        self.iterator = iter(iterable)

    def __next__(self):
        return self.function(next(self.iterator))

    def __new__(cls, *args):
        return object.__new__(cls)

class _map_multiple(map):

    def __init__(self, function: Callable[[T], Any], *iterables: Tuple[Iterable[T]]):
        self.function = function
        self.iterators = tuple(_map_single(iter, iterables))

    def __next__(self):
        t = tuple(_map_single(next, self.iterators))
        if len(t) != len(self.iterators): raise StopIteration
        return self.function(*t)

    def __new__(cls, *args):
        return object.__new__(cls)

# this is zip with strict=False
def zip(*iterables: Tuple[Iterable[Any]]):
    iterators = tuple(map(lambda it: iter(it), iterables))

    while True:
        t = tuple(map(next, iterators))
        if len(t) != len(iterators):
            return
        yield t

def reduce(function: Callable[[T], Any], iterable: Iterable[T], initial: T | None = None):
    iterator = iter(iterable)
    if initial is None:
        res = next(iterator)
    else:
        res = initial
    for item in iterator:
        res = function(res, item)
    return res

def accumulate(function: Callable[[T], Any], iterable: Iterable[T], initial: T | None = None):
    iterator = iter(iterable)
    if initial is None:
        res = next(iterator)
    else:
        res = initial
    yield res
    for item in iterator:
        res = function(res, item)
        yield res

def flatten(iterable: Iterable[Any]):
    for item in iterable:
        if isinstance(item, Iterable):
            yield from item
        else:
            yield item

print(list(filter(lambda x: x >= 0, range(-15, 15))))
print(list(map(lambda x: x ** 2, range(0, 10))))
print(list(zip(range(5), range(0, 10, 2))))
print(list(map(lambda x, y: (x,y), range(5), range(0, 10, 2))))