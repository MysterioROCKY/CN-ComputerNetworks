#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100

void crcGenerator(int data[], int data_size, int divisor[], int divisor_size, int crc[]) {
    int temp[MAX_SIZE], rem[MAX_SIZE];
    int i, j;

    // Append 0s to data
    for (i = 0; i < data_size + divisor_size - 1; i++) {
        if (i < data_size)
            temp[i] = data[i];
        else
            temp[i] = 0;
    }

    // Performing the division
    for (i = 0; i < data_size; i++) {
        memcpy(rem, temp + i, divisor_size * sizeof(int));
        if (rem[0] == 1) {
            for (j = 0; j < divisor_size; j++) {
                rem[j] = rem[j] ^ divisor[j];
            }
        }
        memcpy(temp + i, rem, divisor_size * sizeof(int));
    }

    // Copy remainder to CRC
    for (i = 0; i < divisor_size - 1; i++) {
        crc[i] = temp[data_size + i];
    }
}

int main() {
    int data[MAX_SIZE], divisor[MAX_SIZE], crc[MAX_SIZE];
    int data_size, divisor_size, i;
    char received_data[MAX_SIZE];
    int received[MAX_SIZE];

   
    printf("Input: Enter the number of bits in input data: ");
    scanf("%d", &data_size);
    printf("Input: Enter the number of bits in the polynomial generator (divisor): ");
    scanf("%d", &divisor_size);

    printf("Input: Enter the data: ");
    for (i = 0; i < data_size; i++) {
        scanf("%1d", &data[i]);
    }

    printf("Input: Enter the divisor: ");
    for (i = 0; i < divisor_size; i++) {
        scanf("%1d", &divisor[i]);
    }

    crcGenerator(data, data_size, divisor, divisor_size, crc);

    printf("Output: CRC value: ");
    for (i = 0; i < divisor_size - 1; i++) {
        printf("%d", crc[i]);
    }

    printf("\nOutput: Transmitted data: ");
    for (i = 0; i < data_size; i++) {
        printf("%d", data[i]);
    }
    for (i = 0; i < divisor_size - 1; i++) {
        printf("%d", crc[i]);
    }
    printf("\n");

    printf("Input: Enter the received data: ");
    scanf("%s", received_data);
    for (i = 0; i < strlen(received_data); i++) {
        received[i] = received_data[i] - '0';
    }

    crcGenerator(received, data_size + divisor_size - 1, divisor, divisor_size, crc);

    // Check if remainder is all zeros
    int error = 0;
    for (i = 0; i < divisor_size - 1; i++) {
        if (crc[i] != 0) {
            error = 1;
            break;
        }
    }
    if (error) {
        printf("Output: Errors detected\n");
    } else {
        printf("Output: No errors detected\n");
    }

    return 0;
}
