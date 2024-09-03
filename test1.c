#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkForRepitition(char* substring, char value){
    int size = strlen(substring);
    for(int i = 0; i < size; i++){
        if(substring[i] == value){
            return true;
        }
    }
    return false;
}

bool checkForLongerSubstring(char* current_substring, char* longest_substring){
    return strlen(current_substring) > strlen(longest_substring);
}

int lengthOfLongestSubstring(char* s) {
    int string_size = 100;
    char string[string_size];
    char longest_substring[string_size];
    int counter = 0;
    string_size = strlen(s);
    bool is_repeated;
    bool change_longest;
    string[0] = '\0';
    longest_substring[0] = '\0';
    for(int i = 0; i < string_size; i++){
        change_longest = false;
        is_repeated = checkForRepitition(string, s[i]);

        if(is_repeated == false){
            string[counter] = s[i];
            string[counter + 1] = '\0';
        }
        else{
            if(checkForLongerSubstring(string, longest_substring)){
                strcpy(longest_substring, string);
            }
            i--;
            string[0] = '\0';
            counter = -1;
        }
        counter++;
    }
    if(checkForLongerSubstring(string, longest_substring)){
        strcpy(longest_substring, string);
    }
    return strlen(longest_substring);
}

//size - 1
int main(){
    char string[] = "abcabcdef";
    int size = lengthOfLongestSubstring(string);
    printf("%d", size);
    return 0;
}