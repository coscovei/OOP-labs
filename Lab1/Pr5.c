#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    int n = 0;
    char s[100];
    printf("Enter the displacement: ");
    scanf("%d", &n);
    getchar();
    printf("Enter the string to be deciphered: ");
    fgets(s, 100, stdin);

    for (int i = 0; i <= strlen(s); i++) {
        if (isalpha(s[i]) != 0) {
            s[i] = s[i] - n;
            if (s[i] < 97 && islower(s[i]+n) != 0) {
                s[i] = s[i] + 26;
            }
            if (s[i] < 65) {
                s[i] = s[i] + 26;
            }
        }
    }
    printf("%s", s);

}