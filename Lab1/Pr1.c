#include <stdio.h>

int main(void) {
    char name[50];
    int birthYear;
    int currentYear=2025;

    printf("Hello world!\n");
    printf("Enter your name: ");
    scanf("%[^\n]%*c", name);
    printf("Enter your birth year: ");
    scanf("%d", &birthYear);
    int age = currentYear - birthYear;
    printf("Hello, %s! You are %d years old.\n", name, age);

    return 0;
}