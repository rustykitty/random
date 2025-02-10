from timeit import Timer

# characters in 
# "Python 3.12.7 (main, Oct  1 2024, 02:05:46) [Clang 15.0.0 (clang-1500.3.9.4)] on darwin", 
# put through a set
chars_list = ['6', 'n', 'h', 'm', '[', '-', '0', 'C', 'd', ' ', '3', '5', 't', 
              '1', 'c', '2', 'l', 'y', 'i', ':', ')', '.', '4', ',', 'w', 'g', 
              'a', ']', 'r', 'o', '(', '7', '9', 'O', 'P']

chars_tuple = tuple(chars_list)


alphanum = [chr(i) for i in range (32, 127)] # all printable ASCII characters

control = Timer(
    'random.choice(alphanum)', 'import random',
    globals=globals()
)
list_test = Timer(
    'random.choice(alphanum) in chars_list', 'import random',
    globals=globals()
)
tuple_test = Timer(
    'random.choice(alphanum) in chars_tuple', 'import random',
    globals=globals()
)
gen_test = Timer(
    'target = random.choice(alphanum); any(target == c for c in chars_tuple)', 'import random',
    globals=globals()
)

print(control.repeat(5, 1000000))
print(list_test.repeat(5, 1000000))
print(tuple_test.repeat(5, 1000000))
print(gen_test.repeat(5, 1000000))


