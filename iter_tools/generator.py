from typing import Iterator

class generator(Iterator):
    def __iter__(self): return self
    def __next__(self): ... 