#include <stdio.h>

const char* my_strchr(const char* str,char character) {
        while (*str != '\0') {
                if (*str == character) {
                        return str;
                }
                str++;
        }
        return NULL;
}

void main() {
        char str[100], c;
        printf("Enter the string: ");
        scanf("%s",str);
        getchar();
        printf("Enter the character: ");
        scanf("%c",&c);
        if (my_strchr(str,c) != NULL) {
                printf("The character %c is in the string %s.\n", c, str);
        }
        else {
                printf("The character %c is not in the string %s.\n", c, str);
        }

}