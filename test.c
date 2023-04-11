#include <stdio.h>
int* check(int);
int main() {
    int *ptr;
    int a = 1000;
    ptr = check(a);
    printf("Value returned is %d\n", *ptr);
    return 0;
}

int* check(int x) {
    if (x<= 1000){
        x = 0;
    }
    return &x;
}