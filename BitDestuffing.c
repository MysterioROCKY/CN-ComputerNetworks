#include <stdio.h>

void bitDestuffing(int n, int arr[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            count++;
        } else {
            count = 0;
        }

        printf("%d", arr[i]);

        if (count == 5 && i != n - 1 && arr[i + 1] == 0) {
            count = 0; // Reset count
            i++; // Skip the next 0 bit
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of bits: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter the bits: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Output: ");
    bitDestuffing(n, arr);

    return 0;
}
