import sys

from argparse import ArgumentParser

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument('-t', '--times', nargs='?', default=-1)
    parser.add_argument('string', default='')

    ns = parser.parse_args(sys.argv[1:])

    cnt = 0

    while ns != cnt:
        print(ns.string, end=' ')
        cnt += 1
