#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int reverse(long int x){
    if(x < INT_MIN || x > INT_MAX){
        return 0;
    }

    int isNegative = 0;
    if(x < 0){
        isNegative = 1;
        x *= -1;
    }

    long int value_holder = 0;
    long int temp;
    while(x != 0){
        temp = x % 10;
        
        value_holder = (value_holder * 10) + temp;
        
        x /= 10;
    }

    if(isNegative){
        value_holder *= -1;
    }

    if(value_holder < INT_MIN || value_holder > INT_MAX){
        return 0;
    }

    return value_holder;
}

int main(){
    long int num = 2147483648;
    num = reverse(num);
    printf("%d", num);
    return 0;
}