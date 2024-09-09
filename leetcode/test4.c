#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to find the longest palindromic substring centered at left and right
int expandAroundCenter(const char* s, int left, int right, int n) {
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1; // Return the length of the palindrome
}

//We need to know the starting point
//The max length of the palindrome
//Check for the odd length of the palindrome
//Check for the even length of the palindrome
//Check which palindrome is longer
//Check if the current length of the palindrome is longer than the saved max palindrome
//if it is true then put the current palindrome inside the max length and change the starting point using i - (len - 1) / 2
//Return the result of the longest palindrome

char* longestPalindrome(const char* s) {
    int n = strlen(s);
    if (n == 0) return "";

    int start = 0, maxLength = 1;

    for (int i = 0; i < n; i++) {
        // Odd length palindrome
        int len1 = expandAroundCenter(s, i, i, n);
        // Even length palindrome
        int len2 = expandAroundCenter(s, i, i + 1, n);

        int len = (len1 > len2) ? len1 : len2;

        if (len > maxLength) {
            maxLength = len;
            start = i - (len - 1) / 2;
        }
    }

    char* result = (char*)malloc((maxLength + 1) * sizeof(char));
    strncpy(result, s + start, maxLength);
    result[maxLength] = '\0'; // Null-terminate the result string
    return result;
}

int main() {
    char string[] = "abba";
    char* palindrome = longestPalindrome(string);
    printf("%s\n", palindrome);
    free(palindrome); // Free the allocated memory
    return 0;
}
