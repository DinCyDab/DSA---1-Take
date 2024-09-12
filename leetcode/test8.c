#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myAtoi(char* s) {
    int i = 0;
    int num = 0;
    int isNegative = 0;
    
    for(i = 0; i < strlen(s) && !isdigit(s[i] || isspace(s[i])); i++){
    	if(s[i] == '-'){
    		isNegative = 1;
    		break;
		}
	}
    
    for(i = 0; i < strlen(s) && (isdigit(s[i]) || isspace(s[i]) || s[i] == '-' || s[i] == '+'); i++){
    	if(isspace(s[i])){
    		continue;
		}
		if(s[i] == '-'){
			continue;
		}
		if(s[i] == '+'){
			continue;
		}
    	num = (num * 10) + (s[i] - '0');
	}
	if(isNegative){
		num *= -1;
	}
	return num;
}

int main(){
	char string[] = " - 2124a3";
	int num = myAtoi(string);
	printf("%d", num);	
	return 0;
}
