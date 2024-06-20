#include <stdio.h>
#include <stdlib.h>

int main(){
    int n;
    printf("Enter the number of frames to be transmitted: ");
    scanf("%d", &n);
    int *data = (int *)malloc(n * sizeof(int));
    printf("Enter the data to send: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &data[i]);
    }
    int *ack = (int *)malloc(n * sizeof(int));
    printf("Enter the waiting time for an acknowledgement to data: ");
    for(int i = 0; i < n; i++){
        scanf("%d", &ack[i]);
    }
    printf("Frame_No\tData\tSent\tWaiting Time(sec)\tAcknowledged\tResent\n");
    int transmitted = 0;
    for(int i = 0; i < n; ){
        if(ack[i] == 0){
            printf("%d\t\t%d\tYes\t\t%d\t\t\tYes\t\t\tNo\n", i+1, data[i], ack[i]);
            i++;
        }else{
            if(ack[i] < 3){
                printf("%d\t\t%d\tYes\t\t", i+1, data[i]);
                for(int j = 0; j < ack[i] - 1; j++){
                    printf("%d, ", j+1);
                }
                printf("%d\t\tYes\t\t\tNo\n", ack[i]);
                i++;
            }else{
                printf("%d\t\t%d\tYes\t\t", i+1, data[i]);
                for(int j = 0; j < 2; j++){
                    printf("%d, ", j+1);
                }
                printf("3\t\tNo\t\t\tYes\n");
                ack[i] = 0; // Marking for retransmission
            }
        }
        transmitted++;
    }
    printf("\nTotal number of frames that need to be transmitted is %d\n", transmitted);
    free(data);
    free(ack);
    return 0;
}