#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *a = (char*)malloc(5 * sizeof(char));
    char *b = (char*)malloc(5 * sizeof(char));
    char *c = (char*)malloc(10 * sizeof(char));
    int i, j;
    for (int i = 0 ; i < 5; i++){
        c[i] = a[i];
    }
    for (int j = 0 ; j < 5; j++){
        c[j+5] = b[j];
    }

    free(a);
    free(b);
    free(c);

    return 0;
}