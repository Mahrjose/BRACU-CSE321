#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isPalindrome(char word[]){

    int size = strlen(word);
    
    char *startPtr = word;
    char *endPtr = word + (size - 1);
    
    while (startPtr < endPtr){
        if(*startPtr != *endPtr){
            return false;
        }
        startPtr++;
        endPtr--;
    }
    return true;
}

int main() {

    char word[25];
    printf("Enter word: ");
    scanf("%s", word);

    if(isPalindrome(word)){
        printf("Plaindrome\n");
    } else {
        printf("Not Palindrome\n");
    }

    return 0;
}