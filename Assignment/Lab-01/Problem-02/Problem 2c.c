#include <stdio.h>
#include <string.h>
#include <ctype.h>

void passwordChecker(char password[], char result[]){

    int lowerCaseCount = 0;
    int upperCaseCount = 0;
    int digitCount = 0;
    int specCharCount = 0;

    int size = strlen(password);
    for(int i = 0; i < size; i++){
        if(islower(password[i])){
            lowerCaseCount++;
        }
        else if(isupper(password[i])){
            upperCaseCount++;
        }
        else if(isdigit(password[i])){
            digitCount++;
        }
        else if(password[i] == '_' || password[i] == '$' || password[i] == '#' || password[i] == '@'){
            specCharCount++;
        }
    }

    if(lowerCaseCount == 0) {
        strcat(result, "Lowercase character missing");
    }
    if(upperCaseCount == 0) {
        if (strlen(result) > 0) {
            strcat(result, ", ");
        }
        strcat(result, "Uppercase character missing");
    }
    if(digitCount == 0) {
        if (strlen(result) > 0) {
            strcat(result, ", ");
        }
        strcat(result, "Digit missing");
    }
    if(specCharCount == 0) {
        if (strlen(result) > 0) {
            strcat(result, ", ");
        }
        strcat(result, "Special character missing");
    }

    if(strlen(result) == 0) {
        strcat(result, "OK");
    }
}

int main(){

    char password[25];
    printf("Enter your Password: ");
    scanf("%s", password);

    char result[100] = "";
    passwordChecker(password, result);
    printf("%s\n", result);
    return 0;
}