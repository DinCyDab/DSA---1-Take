#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convertIntoSingle(char* s, char *(array)[], int numRows){
    int k = 0;
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < strlen(s); j++){
            if(array[i][j] != '\0'){
                s[k] = array[i][j];
                k++;
            }
        }
    }
}

char* convert(char* s, int numRows) {
    if(numRows <= 1){
        return s;
    }
    char** array = calloc(numRows, sizeof(char*));
    for(int i = 0; i < numRows; i++){
        array[i] = calloc(strlen(s), sizeof(char));
    }

    // for(int i = 0; i < numRows; i++){
    //     for(int j = 0; j < strlen(s); j++){
    //         array[i][j] = '\0';
    //     }
    // }

    int i = 0;
    int j = 0;
    int k = 0;

    for(int i = 0; i < strlen(s);){
        while(j < numRows - 1 && i < strlen(s)){
            array[j][k] = s[i];
            j++;
            i++;
        }

        do{
            array[j][k] = s[i];
            j--;
            k++;
            i++;
        }while(j >= 1 && i < strlen(s));

        while(j >= 0 && i < strlen(s)){
            array[j][k] = s[i];
            i++;
            j--;
        }
        j = 1;
    }

    convertIntoSingle(s, array, numRows);

    return s;
}

int main(){
    char string[] = "PAYPALISHIRING";
    int numRows = 1;
    printf("Enter number of Rows:");
    scanf("%d", &numRows);
    printf("%s", convert(string, numRows));
    // convert(string, numRows);
    return 0;
}