// Made this lil thing on April Fools

#include <stdio.h>

#define FUNCTION 
#define MAIN main
#define ARGSLIST(...) (__VA_ARGS__)
#define POINTER *
#define ARRAY POINTER
#define ARRAY_WITH_SIZE(_size) [_size]
#define BEGIN {
#define END }
#define RETURN return
#define PUTS(x) puts(x)

typedef int INTEGER;
typedef char CHARACTER;
typedef CHARACTER ARRAY STRING;

INTEGER FUNCTION MAIN 
ARGSLIST(
    INTEGER ARGC,
    STRING POINTER ARGV
)
BEGIN
    PUTS("Hello, world!");
    RETURN 0;
END FUNCTION