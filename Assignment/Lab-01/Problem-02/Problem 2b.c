#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void removeMultiSpace(char phrase[]){

    char string[100];
    bool lastCharSpace = false;
    int size = strlen(phrase);
    int j = 0;

    for(int i = 0; i < size; i++){
        if(phrase[i] == ' '){
            if (!lastCharSpace){
                string[j] = phrase[i];
                j++;
            }            
            lastCharSpace = true;

        } else {
            string[j] = phrase[i];
            j++;
            lastCharSpace = false;

        }
    }
    string[j] = '\0';
    strcpy(phrase, string);
}

int main(){

    char phrase[100];
    printf("Enter a Phrase: ");
    fgets(phrase, sizeof(phrase), stdin);
    
    removeMultiSpace(phrase);
    printf("%s\n", phrase);
    return 0;
}