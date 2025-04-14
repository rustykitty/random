// Made this lil thing on April Fools

#include <stdio.h>
#include <stdlib.h>

#define FUNCTION 
#define MAIN main
#define ARGSLIST(...) (__VA_ARGS__)
#define POINTER *
#define ARRAY POINTER
#define SIZE(_size) [_size]
#define BEGIN {
#define END }
#define RETURN return
#define PUTS(_s) puts(_s)
#define PRINT(_s) PUTS(_s)
#define FGETS(...) fgets(__VA_ARGS__)
#define DEFINE
#define PRINTF(...) printf(__VA_ARGS__)

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
    DEFINE CHARACTER ARR SIZE(8);
    PUTS("What is the first 8 letters of your name?");
    FGETS(ARR, 8, stdin);
    PRINTF("Nice to meet you %s.", ARR);
    RETURN 0;
END FUNCTION