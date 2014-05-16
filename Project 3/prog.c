#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int count(char s[]);



void check(char* s, int expected) {
    printf("%10s ... ",s);
    int res = count(s);
    if (res == expected) {
        printf("'%c' pass",expected);
    } else {
        printf("expected '%c' but found '%c'",expected,res);
    }
    printf("\n");
}
        
int main(int argc, char* argv[]) {
    alarm(10);

    check("xyzabc",'a');
    check("x",'x');
    check("abcx",'x');
    check("abc",'a');
    check("",'a');
    check("111",'1');
    check("a1",'1');
    check("+1a1aa",'a');
    check("+++++",'a');
    check("++",'+');
    check(0,'+');

    return 0;
}
