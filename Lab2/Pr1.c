#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


void max_triplet(int list[], int n, int* a, int* b, int* c, long long* maxprod) {
    if (n < 3) {
        printf("The array has less than 3 elements. Application will now stop.\n");
        *maxprod = LLONG_MIN;
        *a = *b = *c = 0;
        return;
    }

    long long prod1 = LLONG_MIN, prod2 = LLONG_MIN;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (list[i] > list[j]) {
                int temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    // Top three largest elements product
    prod1 = (long long)list[n - 1] * list[n - 2] * list[n - 3];

    // Two smallest elements and the largest element product
    prod2 = (long long)list[0] * list[1] * list[n - 1];

    if (prod1 > prod2) {
        *maxprod = prod1;
        *a = list[n - 3];
        *b = list[n - 2];
        *c = list[n - 1];
    } else {
        *maxprod = prod2;
        *a = list[0];
        *b = list[1];
        *c = list[n - 1];
    }
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n < 3) {
        printf("The array has less than 3 elements. Application will now stop.\n");
        return 0;
    }

    // Dynamic Memory Allocation
    int* list = (int*)malloc(n * sizeof(int));
    if (list == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }

    int a, b, c;
    long long maxprod;
    max_triplet(list, n, &a, &b, &c, &maxprod);

    if (maxprod != LLONG_MIN) {
        printf("The maximum triplet is (%d, %d, %d) with a product of %lld\n", a, b, c, maxprod);
    }
    free(list);

    return 0;
}