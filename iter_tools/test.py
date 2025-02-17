def my_zip(*iterables):
    iterators = tuple(map(iter, iterables))
    while True:
        yield tuple(map(next, iterators))

def my_listcomp_zip(*iterables):
    iterators = tuple(iter(it) for it in iterables)
    while True:
        try:
            yield tuple(next(it) for it in iterators)
        except:
            print("exception caught!")
            return

print(list(my_listcomp_zip(range(5), range(0, 10, 2))))
print(list(my_zip(range(5), range(0, 10, 2))))