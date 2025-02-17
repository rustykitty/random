"""
Python implementations of functions for iterables without using list comprehensions or stuff like that
"""

from typing import (
    Any, Callable, Iterable, Iterator
)

class generator(Iterator):
    def __iter__(self): return self
    # def __next__(self): ... 

class filter(generator):

        def __init__(self, function: Callable[[Any], Any], iterable: Iterable):
            self.__function = function
            self.__iterator = iter(iterable)

        def __next__(self):
            while True:
                item = next(self.__iterator)
                if self.__function(item): return item
                else: continue

def map(function, iterable, *iterables):
    if len(iterables) == 0:
        for item in iterable:
            try: 
                yield function(item)
            except StopIteration: 
                return
    else:
        iterators = map(iter, iterables)
        yield function(*map(next, iterators))

# this is zip with strict=False
def zip(*iterables):
    iterators = tuple(map(lambda it: iter(it), iterables))

    while True:
        m = map(next, iterators)
        print(m)
        t = tuple(m)
        assert t != ()
        yield t

def reduce(function, iterable, initial=None):
    iterator = iter(iterable)
    if initial is None:
        res = next(iterator)
    else:
        res = initial
    for item in iterator:
        res = function(res, item)
    return res

def accumulate(function, iterable, initial=None):
    iterator = iter(iterable)
    if initial is None:
        res = next(iterator)
    else:
        res = initial
    yield res
    for item in iterator:
        res = function(res, item)
        yield res

def flatten(iterable):
    for item in iterable:
        if isinstance(item, Iterable):
            yield from item
        else:
            yield item

print(list(filter(lambda x: x >= 0, range(-15, 15))))
print(list(map(lambda x: x ** 2, range(0, 10))))
print(list(zip(range(5), range(0, 10, 2))))
print(list(map(lambda x, y: (x,y), range(5), range(0, 10, 2))))