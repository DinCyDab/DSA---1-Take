#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void isLonger(char* current_string, char* longestPalindrome){
    if(strlen(current_string) >= strlen(longestPalindrome)){
        strcpy(longestPalindrome, current_string);
    }
}

bool checkForPalindrome(char* current_string){
    int size = strlen(current_string) / 2;
    int j = strlen(current_string) - 1;
    for(int i = 0; i < size; i++, j--){
        if(current_string[i] != current_string[j]){
            return false;
        }
    }
    return true;
}

char* longestPalindrome(char* s) {
    char current_string[strlen(s) + 1];
    char* longest_palindrome = (char*)malloc(sizeof(char) * strlen(s) + 1);
    bool palindrome;
    int k = 0;

    current_string[0] = '\0';
    longest_palindrome[0] = '\0';

    for(int i = 0; i < strlen(s); i++){
        k = 0;
        current_string[k] = '\0';
        for(int j = i; j < strlen(s); j++){
            current_string[k] = s[j];
            current_string[k + 1] = '\0';

            palindrome = checkForPalindrome(current_string);
            if(palindrome){
                isLonger(current_string, longest_palindrome);
            }
            k++;
        }
    }
    return longest_palindrome;
}

int main(){
    char string[] = "geeks";
    printf("%s", longestPalindrome(string));
    return 0;
}