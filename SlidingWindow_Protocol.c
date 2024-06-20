#include <stdio.h>
#include <stdlib.h>

int main() {

    int n_frames, window_size;
    printf("Enter no. of frames to be transmitted: ");
    scanf("%d", &n_frames);
    printf("Enter window size: ");
    scanf("%d", &window_size);

    int corrupted[n_frames];
    int num_corrupted;
    printf("Enter the no. of corrupted frames: ");
    scanf("%d", &num_corrupted);
    printf("Enter the corrupted frame no.s: ");
    for (int i = 0; i < num_corrupted; i++) {
        scanf("%d", &corrupted[i]);
    }
    printf("\n");

    int count = 0;
    int counter[n_frames];  // to see if ack recieved or not(til window size time)

    for (int i = 0; i < n_frames; i++) {
        counter[i] = 0;
    }

    for (int i = 0; i < n_frames; i++) {

        printf("frames %d has been transmitted \n", i);

        for (int j = 0; j <= i; j++) {
            counter[j]++;
        }

        for (int j = 0; j < n_frames; j++) {
            if (counter[j] == 3) {
                if (corrupted[count] == j) {
                    count++;
                    printf("acknowledgement is not recieved for frame %d\n", j);
                    i = i - window_size;
                    for (int k = j; k < n_frames; k++) {
                        counter[k] = 0;
                    }
                }
                else {
                    printf("acknowledgemnt recieved for frame %d\n", j);
                }
            }
        }
    }

    for (int i = n_frames - window_size + 1; i < n_frames; i++) {
        printf("acknowledgement recieved for frame %d\n", i);
    }

    return 0;
}
