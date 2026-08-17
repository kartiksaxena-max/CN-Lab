#include <stdio.h>
#include <math.h>

#define MAX 100


int calculateParityBits(int n){
    int r = 0;
    while (pow(2, r) < (n + r + 1))
        r++;
    return r;
}

void inputData(int data[], int n){
    int i;
    printf("Enter %d-bit binary message:\n", n);
    for (i = n; i >= 1; i--)
        scanf("%d", &data[i]);
}


void generateHamming(int data[], int hamming[], int n, int r)
{
    int i, j = 1, k = 1;
    int total = n + r;

    for (i = 1; i <= total; i++){
        if (i == pow(2, k - 1)){
            hamming[i] = 0;
            k++;
        }
        else{
            hamming[i] = data[j];
            j++;
        }
    }
}


void calculateParity(int hamming[], int total, int r){
    int i, j;

    for (i = 0; i < r; i++){
        int parity = 0;
        int position = pow(2, i);

        for (j = 1; j <= total; j++){
            if (j & position)
                parity ^= hamming[j];
        }

        hamming[position] = parity;
    }
}

void displayCode(int code[], int total){
    int i;
    for (i = total; i >= 1; i--)
        printf("%d", code[i]);
    printf("\n");
}

void inputReceived(int received[], int total){
    int i;

    printf("\nEnter Received Code (%d bits): ", total);

    for (i = total; i >= 1; i--)
        scanf("%d", &received[i]);

    printf("\nReceived Code : ");
    displayCode(received, total);
}

int countChanges(int original[], int received[], int total)
{
    int i, count = 0;

    for (i = 1; i <= total; i++){
        if (original[i] != received[i])
            count++;
    }

    return count;
}

int calculateSyndrome(int received[], int total, int r){
    int i, j;
    int syndrome = 0;

    printf("\nSyndrome Bits:\n");

    for (i = 0; i < r; i++){
        int parity = 0;
        int position = pow(2, i);

        for (j = 1; j <= total; j++)
        {
            if (j & position)
                parity ^= received[j];
        }

        printf("S%d = %d\n", position, parity);

        if (parity)
            syndrome += position;
    }

    return syndrome;
}

void correctError(int received[], int total, int position){
    received[position] ^= 1;
}

int main()
{
    int n, r, total;
    int data[MAX], hamming[MAX], received[MAX];
    int syndrome;

    printf("Enter number of data bits: ");
    scanf("%d", &n);

    inputData(data, n);

    r = calculateParityBits(n);
    total = n + r;

    printf("\nNumber of parity bits = %d\n", r);

    generateHamming(data, hamming, n, r);
    calculateParity(hamming, total, r);

    printf("\nEncoded Message : ");
    displayCode(hamming, total);

    inputReceived(received, total);

    if (countChanges(hamming, received, total) > 1)
        printf("\nWarning: More than one bit has changed.\n");

    syndrome = calculateSyndrome(received, total, r);

    if (syndrome == 0)
    {
        printf("\nNo Error Detected.\n");
    }
    else
    {
        printf("\nError at Position = %d\n", syndrome);
        correctError(received, total, syndrome);

        printf("\nCorrected Code : ");
        displayCode(received, total);
    }

    return 0;
}