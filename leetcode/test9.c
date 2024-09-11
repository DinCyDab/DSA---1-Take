//Given an integer x, return true if x is a 
//palindrome
//, and false otherwise.
//
// 
//
//Example 1:
//
//Input: x = 121
//Output: true
//Explanation: 121 reads as 121 from left to right and from right to left.
//Example 2:
//
//Input: x = -121
//Output: false
//Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.
//Example 3:
//
//Input: x = 10
//Output: false
//Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
// 
//
//Constraints:
//
//-231 <= x <= 231 - 1
// 
//
//Follow up: Could you solve it without converting the integer to a string?

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool isPalindrome(long int x) {
	if(x < 0){
		return false;
	}
	if(x < INT_MIN || x > INT_MAX){
		return false;
	}
    int value_holder = 0;
    int temp = x;
    
    while(temp != 0){
    	int num = temp % 10;
    	value_holder = (value_holder * 10) + num;
    	temp /= 10;
	}
	
	return value_holder == x;
}

int main(){
	long int num = 2147483647;
	bool value = isPalindrome(num);
	printf("%d", value);
}
