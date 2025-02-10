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

# def map(function, iterable, *iterables):
#     if len(iterables) == 0:
#         for item in iterable:
#             yield function(item)
#     else:
#         for items in zip(iterable, *iterables):
#             yield tuple(map(function, items))

class map(generator):
    def __new__(cls, function, iterable, *iterables):
        if len(iterables) == 0:
            return _map_single_iterable(function, iterable)
        else:
            return _map_multi_iterable(function, iterable, *iterables)


class _map_single_iterable(map):

    def __init__(self, function: Callable, iterable: Iterable):
        self.__function = function
        self.__iterator = iter(iterable)

    def __next__(self):
        return self.__function(next(self.__iterator))
            
    
    def __new__(cls, *args):
        return object.__new__(cls)

class _map_multi_iterable(map):

    def __init__(self, function: Callable, *iterables):
        self.__function = function
        self.__iterators = tuple(_map_single_iterable(iter, iterables))
        # print(self.__iterators)

    def __next__(self):
        vals = _map_single_iterable(next, self.__iterators)
        v = tuple(vals)
        # print(v)
        return _map_single_iterable(self.__function, v)

    def __new__(cls, *args):
        return object.__new__(cls)

# this is zip with strict=False
# def zip(*iterables):
#     iterators = list(map(lambda it: iter(it), iterables))
#     try:
#         while True:
#             result = ()
#             for it in iterators:
#                 result += (next(it), )
#             yield result
#     except StopIteration:
#         pass
class zip(generator):

    def __init__(self, *iterables):
        self.__iterators = tuple(_map_single_iterable(iter, iterables))
        print(self.__iterators)

    def __next__(self):
        if not all(self.__iterators):
            raise StopIteration()
        # print(tuple(_map_single_iterable(next, self.__iterators)))
        # return tuple(_map_single_iterable(next, self.__iterators))
        try:
            return tuple(next(it) for it in self.__iterators)
        except:
            raise StopIteration

def reduce(function, iterable, initial=None):
    iterator = iter(iterable)
    if initial is None:
        res = next(iterator)
    else:
        res = initial
    for item in iterator:
        res = function(res, item)
    return res

# def accumulate(function, iterable, initial=None):
#     iterator = iter(iterable)
#     if initial is None:
#         res = next(iterator)
#     else:
#         res = initial
#     yield res
#     for item in iterator:
#         res = function(res, item)
#         yield res

print(list(filter(lambda x: x >= 0, range(-15, 15))))
print(list(map(lambda x: x ** 2, range(0, 10))))
print(list(zip(range(5), range(0, 10, 2))))
print(list(map(lambda x, y: (x,y), range(5), range(0, 10, 2))))