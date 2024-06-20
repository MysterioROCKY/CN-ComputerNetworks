#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter the number of bits: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    printf("Enter the bits: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int* res = (int*)malloc((2 * n) * sizeof(int));
    int count = 0;
    int res_index = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            count++;
            res[res_index++] = arr[i];
        } else {
            count = 0;
            res[res_index++] = arr[i];
        }

        if (count == 5) {
            res[res_index++] = 0;
            count = 0;
        }
    }

    printf("Resulting bit sequence: ");
    for (int i = 0; i < res_index; i++) {
        printf("%d", res[i]);
    }
    printf("\n");

    free(arr);
    free(res);

    return 0;
}
