#include <stdio.h>

int main(void) {
    int n;
    int count = 0;
    printf("Enter number to count 1's in base 2: ");
    scanf("%d", &n);
    while (n != 0) {
        if (n % 2 == 1) {
            count++;
        }
        n = n / 2;
    }
    printf("%d", count);
}

