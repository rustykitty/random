"""
wrappers for python I/O functions with stdio.h names

UNTESTED
"""

# https://cplusplus.com/reference/cstdio/

from os import (
    remove,
    rename
)

import os

from io import TextIOWrapper

import io

import sys
from typing import Tuple, Any, TypeAlias

import tempfile

import warnings

File: TypeAlias = TextIOWrapper

def tmpfile():
    return tempfile.TemporaryFile('wb+')

def tmpnam():
    return tempfile.mktemp()

def fclose(stream: File):
    return stream.close()

def fflush(stream: File):
    return stream.flush()

def fopen(filename: str, mode: str):
    return open(filename, mode)

def freopen(filename: str, mode: str, stream: File):
    return os.dup2(open(filename, mode).fileno(), stream.fileno())

def setbuf(stream: File, buffer: str):
    raise NotImplementedError

def setvbuf(stream: File, buffer: str, mode: int, size: int):
    raise NotImplementedError

def scanf(format: str): 
    raise NotImplementedError

def fscanf(stream: File, format: str):
    raise NotImplementedError

def sscanf(s: str, format: str):
    raise NotImplementedError

def sprintf(format: str, *args: Tuple[Any]) -> str:
    """
    returns formatted string, not amount of bytes"""
    return format % args

def printf(format: str, *args: Tuple[Any]):
    """C-style printf function"""
    return fprintf(sys.stdout, format, *args)

def fprintf(stream: File, format: str, *args: Tuple[Any]): 
    """C-style fprintf function, characters are not actually written if stream is None"""
    if stream is None: return len(snprintf(format, *args))
    return stream.write(format % args)

def fgetc(stream: File):
    return stream.read(1)

def fgets(stream: File):
    return stream.readline()

def fputc(character: str, stream: File):
    fputs(character, stream)
    return character

def fputs(str: str, stream: File):
    return stream.write(str)

getc = fgetc

def getchar():
    return fgetc(sys.stdin)

def gets():
    warnings.warn('gets() has been deprecated since C99 and was removed in C11', DeprecationWarning)
    res: str = sys.stdin.readline()
    if res[-1] == '\n': return res[:-1]
    return res

putc = fputc

def putchar(character: str):
    return fputc(character, sys.stdout)

def puts(str: str):
    sys.stdout.write(str)
    sys.stdout.write('\n')
    return 0

def ungetc(character: str, stream: File): 
    raise NotImplementedError

def fread(ptr: Any, size: int, count: int, stream: File):
    raise NotImplementedError

def fwrite(ptr: Any, size: int, count: int, stream: File):
    raise NotImplementedError

def fgetpos(stream: File):
    return stream.tell()

def fseek(stream: File, offset: int, origin: int):
    return stream.seek(offset, origin)

def fsetpos(stream: File, pos: int):
    return stream.seek(pos)

def rewind(stream: File):
    return stream.seek(0)